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
    auto endPos = Skip2(fullExpression, fromPos, '/');
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
    auto endPos = Skip2(fullExpression, fromPos, '"');
    mLocation = fullExpression.substr(fromPos, endPos - fromPos);
    return endPos + 1;
}

std::shared_ptr<Expression> QuoteLocationParser::onExit()
{
	return std::make_shared<DotLocationPath>(mLocation);
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
	endPos = Skip2(fullExpression, fromPos, '.');
    mLocation = fullExpression.substr(fromPos, endPos - fromPos);
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
	size_t endPos = fromPos;
	endPos = Skip2(fullExpression, fromPos, ']');
    mIndex = fullExpression.substr(fromPos, endPos - fromPos);
	return endPos;
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
	endPos = Skip2(fullExpression, fromPos, '}');
	mPredicate = fullExpression.substr(fromPos, endPos - fromPos);
	return endPos;
}

std::shared_ptr<Expression> PredicateParser::onExit()
{
	return nullptr;
}
//==========================Compiler======================================

Compiler::Compiler()
{
	auto pInitState = std::make_shared<InitParser>();
	auto pDotState = std::make_shared<DotParser>();
	auto pRegexLocationState = std::make_shared<RegexLocationParser>();
	auto pQuoteLocationState = std::make_shared<QuoteLocationParser>();
	auto pGenericLocationState = std::make_shared<GenericLocationParser>();
	auto pTwoDotLocationState = std::make_shared<TwoDotLocationParser>();
	auto pPositionalState = std::make_shared<PositionalParser>();
	auto pPredicateState = std::make_shared<PredicateParser>();

	auto DotEvent = '.';
	auto SlashEvent = '/';
	auto QuoteEvent = '"';
	auto OtherEvent = '\n';
	auto OpenBrace = '{';
	auto CloseBrace = '}';
	auto OpenBracket = '[';
	auto CloseBracket = ']';
	auto OpenParenthesis = '(';
	auto CloseParenthesis = ')';

	addTransaction(pInitState,    DotEvent,  pDotState);
	addTransaction(pDotState,     SlashEvent,pRegexLocationState);
    addTransaction(pDotState,     QuoteEvent,pQuoteLocationState);
	addTransaction(pDotState,     DotEvent,  pTwoDotLocationState);
	addTransaction(pDotState,     OtherEvent,pGenericLocationState);
	//addTransaction()



	mCurrentState = pInitState;
	mCurrentSubState = mTransactions[mCurrentState->getCode()];
}

void Compiler::addTransaction(State fromState, Event event, State toState)
{
    auto pSubTransaction = mTransactions[fromState->getCode()];
    (*pSubTransaction)[event] = toState;
}

std::shared_ptr<Expression> Compiler::processEvent(Event event)
{
	auto itDestState = mCurrentSubState->find(event);
	if(mCurrentSubState->end() == itDestState)
	{
		itDestState = mCurrentSubState->find('\n');
	}

	if(mCurrentSubState->end() == itDestState)
	{
		throw std::logic_error("syntax error");
	}

	auto pExpression = mCurrentState->onExit();
	mCurrentState = itDestState->second;
	mCurrentState->onEntry();

	return pExpression;
}

std::shared_ptr<Expression> Compiler::compile(const std::string& strExpression)
{
	std::shared_ptr<Expression> pRetExpression;
	std::shared_ptr<Expression> pLastExpression;
	size_t pos = 0;
	try
	{
		for(; pos < strExpression.length(); ++pos)
		{
			pos = mCurrentState->parse(strExpression, pos);
			auto pExpression = processEvent(strExpression.at(pos));
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
	}

	return pRetExpression;
}
}
