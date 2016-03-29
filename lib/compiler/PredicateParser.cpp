#include "compiler/PredicateParser.h"

namespace jspath
{
bool operator< (const OpInfo& lhs, const OpInfo& rhs)
{
    const
}

void PredicateParser::onEntry()
{}

size_t PredicateParser::parse(const std::string& fullExpression, size_t fromPos, size_t endPos)
{
    assert(0 != fromPos);
    size_t toPos = fromPos;
    toPos = skip2(fullExpression, fromPos, '}', endPos);
    mPredicate = fullExpression.substr(fromPos, toPos - fromPos);
    return toPos;
}


std::shared_ptr<Expression> PredicateParser::onExit()
{
    return mResult;
}
}

