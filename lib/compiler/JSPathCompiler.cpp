#include "compiler/JSPathCompiler.h"
#include "compiler/Utils.h"
#include "location/RegexLocationPath.h"
#include "location/WildcardLocationPath.h"
#include "location/DotLocationPath.h"
#include "location/2DotLocationPath.h"
#include "positional/Positional.h"
namespace jspath
{

SubExpressionParser::~SubExpressionParser()
{}

void SubExpressionParser::onEntry()
{}


//=======================RegexLocationParser================================
void RegexLocationParser::onEntry()
{
    mRegexText.clear();
}

size_t RegexLocationParser::parse(const std::string& fullExpression, size_t fromPos)
{
    ++fromPos;
    auto endPos = skip2(fullExpression, fromPos, '/');
    mRegexText = fullExpression.substr(fromPos, endPos - fromPos);
    return endPos + 1;
}

std::shared_ptr<Expression> RegexLocationParser::onExit()
{
    return std::make_shared<RegexLocationPath>(mRegexText);

}

//============================QuoteLocationParser======================================
void QuoteLocationParser::onEntry()
{}

size_t QuoteLocationParser::parse(const std::string& fullExpression, size_t fromPos)
{
    ++fromPos;
    auto endPos = skip2(fullExpression, fromPos, '"');
    mLocation = fullExpression.substr(fromPos, endPos - fromPos);
    mIsWildcard = std::string::npos != mLocation.find('*');
    return endPos + 1;
}

std::shared_ptr<Expression> QuoteLocationParser::onExit()
{
    if(mIsWildcard)
    {
        return std::make_shared<WildcardLocationPath>(mLocation);
    }
    else
    {
        return std::make_shared<DotLocationPath>(mLocation);
    }
}

//========================GenericLocationParser===================================
void GenericLocationParser::onEntry()
{
    mIsWildcard = false;
}

size_t GenericLocationParser::parse(const std::string& fullExpression, size_t fromPos)
{
    assert(0 != fromPos);
    size_t endPos = fromPos;
    endPos = skip2Any(fullExpression, fromPos, ".{[", fullExpression.length());
    mLocation = fullExpression.substr(fromPos, endPos - fromPos);
    mIsWildcard = std::string::npos != mLocation.find('*');
    return endPos;
}

std::shared_ptr<Expression> GenericLocationParser::onExit()
{
    if(mIsWildcard)
    {
        return std::make_shared<WildcardLocationPath>(mLocation);
    }
    else
    {
        return std::make_shared<DotLocationPath>(mLocation);
    }
}

//=========================TwoDotLocationParser=======================
std::shared_ptr<Expression> TwoDotLocationParser::onExit()
{
    return std::make_shared<TwoDotLocationPath>();
}


//==========================PositionalParser==============================
void PositionalParser::onEntry()
{}

size_t PositionalParser::parse(const std::string& fullExpression, size_t fromPos)
{
    assert(0 != fromPos);
    ++fromPos;
    size_t endPos = fromPos;
    endPos = skip2(fullExpression, fromPos, ']');
    mIndex = fullExpression.substr(fromPos, endPos - fromPos);
    return endPos + 1;
}

std::shared_ptr<Expression> PositionalParser::onExit()
{
    auto index = IndexRange(mIndex);
    return std::make_shared<Positional>(index);
}
//==========================PredicateParser================================

void PredicateParser::onEntry()
{}

size_t PredicateParser::parse(const std::string& fullExpression, size_t fromPos)
{
    assert(0 != fromPos);
    size_t endPos = fromPos;
    endPos = skip2(fullExpression, fromPos, '}');
    mPredicate = fullExpression.substr(fromPos, endPos - fromPos);
    return endPos;
}

std::shared_ptr<Expression> PredicateParser::onExit()
{
    return nullptr;
}
//=============================ExceptionParser===========================
size_t ExceptionParser::parse(const std::string& fullExpression, size_t fromPos)
{
    throw std::logic_error("syntax error ");
}

//==========================Compiler======================================

Compiler::Compiler()
{
    auto pAnyState = nullptr;
    auto pInitState = std::make_shared<InitParser>();
    auto pDotState = std::make_shared<DotParser>();
    auto pRegexLocationState = std::make_shared<RegexLocationParser>();
    auto pQuoteLocationState = std::make_shared<QuoteLocationParser>();
    auto pGenericLocationState = std::make_shared<GenericLocationParser>();
    auto pTwoDotLocationState = std::make_shared<TwoDotLocationParser>();
    auto pPositionalState = std::make_shared<PositionalParser>();
    auto pPredicateState = std::make_shared<PredicateParser>();
    auto pExceptionState = std::make_shared<ExceptionParser>();



    //------------+---------------+-----------+-------------------
    addTransaction(pInitState,    DotEvent,   pDotState);

    //------------+---------------+-----------+-------------------
    addTransaction(pDotState,     SlashEvent, pRegexLocationState);
    addTransaction(pDotState,     QuoteEvent, pQuoteLocationState);
    addTransaction(pDotState,     DotEvent,   pTwoDotLocationState);
    addTransaction(pDotState,     OpenBracket,pPositionalState);
    addTransaction(pDotState,     OtherEvent, pGenericLocationState);

    addTransaction(pAnyState,     DotEvent,   pDotState);
    addTransaction(pAnyState,     EOFEvent,   pInitState);
    addTransaction(pAnyState,     OpenBracket,pPositionalState);
    //addTransaction()



    mCurrentState = pInitState;
    mCurrentSubState = mTransactions[mCurrentState->getCode()];
    mAnySubState = mTransactions[SubExpressionParser::Any];
}

void Compiler::addTransaction(State fromState, Event event, State toState)
{
    auto& pSubTransaction = mTransactions[nullptr == fromState ? SubExpressionParser::Any : fromState->getCode()];
    if(nullptr == pSubTransaction)
    {
        pSubTransaction = std::make_shared<SubTransaction::element_type>();
    }
    (*pSubTransaction)[event] = toState;
}

std::shared_ptr<Expression> Compiler::processEvent(Event event)
{
    SubTransaction::element_type::iterator itDestState;
    if(nullptr != mCurrentSubState)
    {
        itDestState = mCurrentSubState->find(event);
        if(mCurrentSubState->end() == itDestState)
        {
            itDestState = mCurrentSubState->find(OtherEvent);
        }
    }

    if(nullptr == mCurrentSubState || (mCurrentSubState->end() == itDestState))
    {
        itDestState = mAnySubState->find(event);
    }

    if(mAnySubState->end() == itDestState || (nullptr != mCurrentState && (mCurrentSubState->end() == itDestState)))
    {
        throw std::logic_error("syntax error");
    }

    auto pExpression = mCurrentState->onExit();
    mCurrentState = itDestState->second;
    mCurrentState->onEntry();
    mCurrentSubState = mTransactions[mCurrentState->getCode()];
    return pExpression;
}

std::shared_ptr<Expression> Compiler::compile(const std::string& strExpression)
{
    std::shared_ptr<Expression> pRetExpression;
    std::shared_ptr<Expression> pLastExpression;
    size_t pos = 0;
    try
    {
        for(; pos < strExpression.length(); )
        {
            pos = mCurrentState->parse(strExpression, pos);
            Event event = EOFEvent;
            if(pos < strExpression.length())
            {
                event = strExpression.at(pos);
            }

            auto pExpression = processEvent(event);
            if(nullptr != pExpression)
            {
                if(nullptr == pRetExpression)
                {
                    pRetExpression = pLastExpression = pExpression;
                }
                else
                {
                    pLastExpression->setSuccessor(pExpression);
                    pLastExpression = pExpression;
                }
            }
        }
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << " at column " << pos << std::endl;
        return nullptr;
    }

    return pRetExpression;
}
}
