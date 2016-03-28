#include "compiler/JSPathCompiler.h"
#include "compiler/Utils.h"
#include "location/RegexLocationPath.h"
#include "location/WildcardLocationPath.h"
#include "location/DotLocationPath.h"
#include "location/2DotLocationPath.h"
#include "location/MultiLocationPath.h"
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

size_t RegexLocationParser::parse(const std::string& fullExpression, size_t fromPos, size_t endPos)
{
    ++fromPos;
    auto toPos = skip2(fullExpression, fromPos, '/');
    mRegexText = fullExpression.substr(fromPos, toPos - fromPos);
    return toPos + 1;
}

std::shared_ptr<Expression> RegexLocationParser::onExit()
{
    return std::make_shared<RegexLocationPath>(mRegexText);

}

//============================QuoteLocationParser======================================
void QuoteLocationParser::onEntry()
{}

size_t QuoteLocationParser::parse(const std::string& fullExpression, size_t fromPos, size_t endPos)
{
    ++fromPos;
    auto toPos = skip2(fullExpression, fromPos, '"');
    mLocation = fullExpression.substr(fromPos, toPos - fromPos);
    mIsWildcard = std::string::npos != mLocation.find('*');
    return toPos + 1;
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

size_t GenericLocationParser::parse(const std::string& fullExpression, size_t fromPos, size_t endPos)
{
    assert(0 != fromPos);
    size_t toPos = skip2Any(fullExpression, fromPos, ".{[", endPos);
    mLocation = fullExpression.substr(fromPos, toPos - fromPos);
    mIsWildcard = std::string::npos != mLocation.find('*');
    return toPos;
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

size_t PositionalParser::parse(const std::string& fullExpression, size_t fromPos, size_t endPos)
{
    assert(0 != fromPos);
    ++fromPos;
    size_t toPos = fromPos;
    toPos = skip2(fullExpression, fromPos, ']');
    mIndex = fullExpression.substr(fromPos, toPos - fromPos);
    return toPos + 1;
}

std::shared_ptr<Expression> PositionalParser::onExit()
{
    auto index = IndexRange(mIndex);
    return std::make_shared<Positional>(index);
}

//==========================MultiLocationParser============================
MultiLocationParser::MultiLocationParser()
    :mFullExpression(nullptr)
{}

void MultiLocationParser::onEntry()
{
    mFullExpression = nullptr;
    mSubExpressionIndices.clear();
}

size_t MultiLocationParser::parse(const std::string& fullExpression, size_t fromPos, size_t endPos)
{
    mFullExpression = &fullExpression;
    mSubExpressionIndices.push_back(fromPos);
    ++fromPos;


    bool finish = false;
    std::stack<char> unmatch;
    for(; fromPos < endPos && !finish; ++fromPos)
    {
        char c = fullExpression.at(fromPos);
        switch (c)
        {
        case '(':
        case '[':
        case '{':
            unmatch.push(c);
            break;
        case ')':
            {
                if(unmatch.empty())
                {
                    finish = true;
                }
                else if('(' != unmatch.top())
                {
                    throw std::logic_error("')' unmatch");
                }
                else
                {
                    unmatch.pop();
                }
            }//')'
        case ']':
            {
                if(unmatch.empty() || '[' != unmatch.top())
                {
                    throw std::logic_error("']' unmatch");
                }
                else
                {
                    unmatch.pop();
                }
            }//']'
        case '}':
            {
                if(unmatch.empty() || '{' != unmatch.top())
                {
                    throw std::logic_error("']' unmatch");
                }
                else
                {
                    unmatch.pop();
                }
            }//'}'
            break;
        case '"':
            {
                auto toPos = skipString(fullExpression, fromPos + 1);
                if(std::string::npos == toPos)
                {
                    throw std::logic_error("'\"' not found");
                }
                fromPos = toPos;
            }
            break;
        case '|':
            if(unmatch.empty())
            {
                mSubExpressionIndices.push_back(fromPos);
            }
            break;
        default:
            break;
        };
    }

    if(!finish)
    {
        throw std::logic_error("can not found match ')' for multi location after scan to end");
    }

    mSubExpressionIndices.push_back(fromPos - 1);
    return fromPos;
}

std::shared_ptr<Expression> MultiLocationParser::onExit()
{
    auto pMultiLocation = std::make_shared<MultiLocationPath>();
    for(size_t i = 1; i < mSubExpressionIndices.size(); ++i)
    {
        auto fromPos = mSubExpressionIndices[i - 1] + 1;
        Compiler subCompiler;
        auto pSubLocation = subCompiler.compile(*mFullExpression, fromPos, mSubExpressionIndices[i - 1]);
        if(nullptr != pSubLocation)
        {
            pMultiLocation->addChild(pSubLocation);
        }
    }

    return pMultiLocation;
}

//==========================PredicateParser================================

void PredicateParser::onEntry()
{}

size_t PredicateParser::parse(const std::string& fullExpression, size_t fromPos, size_t endPos)
{
    assert(0 != fromPos);
    size_t toPos = fromPos;
    toPos = skip2(fullExpression, fromPos, '}');
    mPredicate = fullExpression.substr(fromPos, toPos - fromPos);
    return toPos;
}

std::shared_ptr<Expression> PredicateParser::onExit()
{
    return nullptr;
}
//=============================ExceptionParser===========================
size_t ExceptionParser::parse(const std::string& fullExpression, size_t fromPos, size_t endPos)
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
    auto pMultiLocationState = std::make_shared<MultiLocationParser>();

    //------------+---------------+------------------+-------------------
    addTransaction(pInitState,    DotEvent,          pDotState);

    //------------+---------------+------------------+-------------------
    addTransaction(pDotState,     SlashEvent,        pRegexLocationState);
    addTransaction(pDotState,     QuoteEvent,        pQuoteLocationState);
    addTransaction(pDotState,     DotEvent,          pTwoDotLocationState);
    addTransaction(pDotState,     OpenBracket,       pPositionalState);
    addTransaction(pDotState,     OtherEvent,        pGenericLocationState);
    addTransaction(pDotState,     OpenParenthesis,   pMultiLocationState);

    //------------+---------------+------------------+-------------------
    addTransaction(pAnyState,     DotEvent,          pDotState);
    addTransaction(pAnyState,     EOFEvent,          pInitState);
    addTransaction(pAnyState,     OpenBracket,       pPositionalState);
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

std::shared_ptr<Expression> Compiler::compile(const std::string& strExpression, size_t& pos, size_t endPos)
{
    std::shared_ptr<Expression> pRetExpression;
    std::shared_ptr<Expression> pLastExpression;

    if(std::string::npos == endPos)
    {
        endPos = strExpression.length();
    }

    while(pos < endPos)
    {
        pos = mCurrentState->parse(strExpression, pos, endPos);
        Event event = EOFEvent;
        if(pos < endPos)
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

    return pRetExpression;
}
}
