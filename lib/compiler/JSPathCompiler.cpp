#include "compiler/JSPathCompiler.h"
#include "compiler/PredicateParser.h"
#include "compiler/Utils.h"
#include "location/RegexLocationPath.h"
#include "location/WildcardLocationPath.h"
#include "location/DotLocationPath.h"
#include "location/2DotLocationPath.h"
#include "location/MultiLocationPath.h"
#include "location/RootLocationPath.h"
#include "positional/Positional.h"
namespace jspath
{

SubExpressionParser::~SubExpressionParser()
{}

void SubExpressionParser::onEntry()
{}

//========================SpaceParser=============================
void SpaceParser::parse(const std::string& fullExpression, size_t& fromPos, size_t endPos)
{
    fromPos = skipSpace(fullExpression, fromPos, endPos);
}

//=======================RegexLocationParser================================
void RegexLocationParser::onEntry()
{
    mRegexText.clear();
}

void RegexLocationParser::parse(const std::string& fullExpression, size_t& fromPos, size_t endPos)
{
    ++fromPos;
    auto toPos = skip2(fullExpression, fromPos, '/', endPos);
    mRegexText = fullExpression.substr(fromPos, toPos - fromPos);
    fromPos = toPos + 1;
}

std::shared_ptr<Expression> RegexLocationParser::onExit()
{
    return std::make_shared<RegexLocationPath>(mRegexText);

}

//============================QuoteLocationParser======================================
void QuoteLocationParser::onEntry()
{}

void QuoteLocationParser::parse(const std::string& fullExpression, size_t& fromPos, size_t endPos)
{
    ++fromPos;
    auto toPos = skip2(fullExpression, fromPos, '"', endPos);
    mLocation = fullExpression.substr(fromPos, toPos - fromPos);
    mIsWildcard = std::string::npos != mLocation.find('*');
    fromPos = toPos + 1;
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

void GenericLocationParser::parse(const std::string& fullExpression, size_t& fromPos, size_t endPos)
{
    assert(0 != fromPos);
    size_t toPos = skip2Any(fullExpression, fromPos, ".{[(", endPos);
    mLocation = fullExpression.substr(fromPos, toPos - fromPos);
    mIsWildcard = std::string::npos != mLocation.find('*');
    fromPos = toPos;
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

void PositionalParser::parse(const std::string& fullExpression, size_t& fromPos, size_t endPos)
{
    assert(0 != fromPos);
    ++fromPos;
    size_t toPos = fromPos;
    toPos = skip2(fullExpression, fromPos, ']', endPos);
    mIndex = fullExpression.substr(fromPos, toPos - fromPos);
    fromPos = toPos + 1;
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

void MultiLocationParser::parse(const std::string& fullExpression, size_t& fromPos, size_t endPos)
{
    mFullExpression = &fullExpression;
    mSubExpressionIndices.push_back(fromPos);
    ++fromPos;


    bool finish = false;
    std::stack<char> unmatched;
    unmatched.push('(');
    for(; fromPos < endPos && !finish; ++fromPos)
    {
        char c = fullExpression.at(fromPos);
        if(!matchRange(unmatched, fullExpression, fromPos, endPos) && '|' == c)
        {
            if(1 == unmatched.size())
            {
                mSubExpressionIndices.push_back(fromPos);
            }
        }
        else if(unmatched.empty())
        {
            finish = true;
        }
    }

    if(!finish)
    {
        throw std::logic_error("can not found match ')' for multi location after scan to end");
    }

    mSubExpressionIndices.push_back(fromPos - 1);
}

std::shared_ptr<Expression> MultiLocationParser::onExit()
{
    auto pMultiLocation = std::make_shared<MultiLocationPath>();
    for(size_t i = 1; i < mSubExpressionIndices.size(); ++i)
    {
        auto fromPos = mSubExpressionIndices[i - 1] + 1;
        Compiler subCompiler;
        auto pSubLocation = subCompiler.compile(*mFullExpression, fromPos, mSubExpressionIndices[i]);
        if(nullptr != pSubLocation)
        {
            pMultiLocation->addChild(pSubLocation);
        }
    }

    return pMultiLocation;
}


//=============================ExceptionParser===========================
void ExceptionParser::parse(const std::string& fullExpression, size_t& fromPos, size_t endPos)
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
    auto pSpaceState = std::make_shared<SpaceParser>();

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
    addTransaction(pAnyState,     OpenParenthesis,   pMultiLocationState);
    addTransaction(pAnyState,     DotEvent,          pDotState);
    addTransaction(pAnyState,     EOFEvent,          pInitState);
    addTransaction(pAnyState,     OpenBracket,       pPositionalState);
    addTransaction(pAnyState,     ' ',               pSpaceState);
    addTransaction(pAnyState,     '\t',              pSpaceState);
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

    pRetExpression = pLastExpression = std::make_shared<RootLocationPath>();
    if(std::string::npos == endPos)
    {
        endPos = strExpression.length();
    }

    pos = skipSpace(strExpression, pos, endPos);
    if('^' == strExpression.at(pos))
    {
        pLastExpression->setAbsolute(true);
    }

    while(pos < endPos)
    {
        mCurrentState->parse(strExpression, pos, endPos);
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
        pos = skipSpace(strExpression, pos, endPos);
    }

    return pRetExpression;
}
}
