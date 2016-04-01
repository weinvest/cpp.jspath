#include "compiler/PredicateParser.h"
#include "Context.h"
#include "compiler/Utils.h"
#include "predicate/LogicOperator.h"
#include "predicate/ArthemeticOperator.h"
#include "predicate/StringOperator.h"
#include "predicate/Operand.h"
#include "predicate/Comparator.h"
namespace jspath
{
bool operator< (const OpInfo& lhs, const OpInfo& rhs)
{
    if(std::abs(lhs.op - rhs.op) <= 16)
    {
        return false;
    }
    else
    {
        return lhs.op < rhs.op;
    }
}

void PredicateParser::onEntry()
{}

void PredicateParser::parseEqual(const std::string& fullExpression, size_t& fromPos)
{
    if('=' == fullExpression[fromPos + 1])
    {
        if('=' == fullExpression[fromPos + 2])
        {
            mOperators.emplace_back(OpInfo{OpInfo::StrictlyEqual, fromPos, fromPos + 3, mOperators.size()});
            fromPos += 2;
        }
        else
        {
            mOperators.emplace_back(OpInfo{OpInfo::Equal, fromPos, fromPos + 2, mOperators.size()});
            fromPos += 1;
        }
    }
    else
    {
        throw std::logic_error("syntax error");
    }
}

void PredicateParser::parseNonEqual(const std::string& fullExpression, size_t& fromPos)
{
    if('=' == fullExpression.at(fromPos + 1))
    {
        if('=' == fullExpression.at(fromPos + 2))
        {
            mOperators.emplace_back(OpInfo{OpInfo::StrictlyNonEqual, fromPos, fromPos + 3, mOperators.size()});
            fromPos += 2;
        }
        else
        {
            mOperators.emplace_back(OpInfo{OpInfo::NonEqual, fromPos, fromPos + 2, mOperators.size()});
            fromPos += 1;
        }
    }
    else
    {
        mOperators.emplace_back(OpInfo{OpInfo::Not, fromPos, fromPos + 1, mOperators.size()});
    }
}

void PredicateParser::parseGreat(const std::string& fullExpression, size_t& fromPos)
{
    if('=' == fullExpression.at(fromPos + 1))
    {
        mOperators.emplace_back(OpInfo{OpInfo::GreatEqual, fromPos, fromPos + 2, mOperators.size()});
    }
    else
    {
        mOperators.emplace_back(OpInfo{OpInfo::GreatThan, fromPos, fromPos + 1, mOperators.size()});
    }
}

void PredicateParser::parseLess(const std::string& fullExpression, size_t& fromPos)
{
    if('=' == fullExpression.at(fromPos + 1))
    {
        mOperators.emplace_back(OpInfo{OpInfo::LessEqual, fromPos, fromPos + 2, mOperators.size()});
    }
    else
    {
        mOperators.emplace_back(OpInfo{OpInfo::LessThan, fromPos, fromPos + 1, mOperators.size()});
    }
}

void PredicateParser::parseStartsWith(const std::string& fullExpression, size_t& fromPos)
{
    if('=' == fullExpression[fromPos + 1])
    {
        if('=' == fullExpression[fromPos + 2])
        {
            mOperators.emplace_back(OpInfo{OpInfo::StartsWith, fromPos, fromPos + 3, mOperators.size()});
            fromPos += 2;
        }
        else
        {
            mOperators.emplace_back(OpInfo{OpInfo::iStartsWith, fromPos, fromPos + 2, mOperators.size()});
            fromPos += 1;
        }
    }
    else
    {
        throw std::logic_error("syntax error");
    }
}

void PredicateParser::parseEndsWith(const std::string& fullExpression, size_t& fromPos)
{
    if('=' == fullExpression[fromPos + 1])
    {
        if('=' == fullExpression[fromPos + 2])
        {
            mOperators.emplace_back(OpInfo{OpInfo::EndsWith, fromPos, fromPos + 3, mOperators.size()});
            fromPos += 2;
        }
        else
        {
            mOperators.emplace_back(OpInfo{OpInfo::iEndsWith, fromPos, fromPos + 2, mOperators.size()});
            fromPos += 1;
        }
    }
    else
    {
        throw std::logic_error("syntax error");
    }
}

void PredicateParser::parseContains(const std::string& fullExpression, size_t& fromPos)
{
    if('=' == fullExpression.at(fromPos + 1))
    {
        if('=' == fullExpression.at(fromPos + 2))
        {
            mOperators.emplace_back(OpInfo{OpInfo::Contains, fromPos, fromPos + 3, mOperators.size()});
            fromPos += 2;
        }
        else
        {
            mOperators.emplace_back(OpInfo{OpInfo::iContains, fromPos, fromPos + 2, mOperators.size()});
            fromPos += 1;
        }
    }
    else
    {
        mOperators.emplace_back(OpInfo{OpInfo::Mul, fromPos, fromPos + 1, mOperators.size()});
    }
}

void PredicateParser::parseMatch(const std::string& fullExpression, size_t& fromPos)
{
    if('=' == fullExpression.at(fromPos + 1))
    {
        if('=' == fullExpression.at(fromPos + 2))
        {
            mOperators.emplace_back(OpInfo{OpInfo::Match, fromPos, fromPos + 3, mOperators.size()});
            fromPos += 2;
        }
        else
        {
            mOperators.emplace_back(OpInfo{OpInfo::iMatch, fromPos, fromPos + 2, mOperators.size()});
            fromPos += 1;
        }
    }
    else if('!' == fullExpression.at(fromPos + 1))
    {
        if('=' == fullExpression.at(fromPos + 2))
        {
            mOperators.emplace_back(OpInfo{OpInfo::NotMatch, fromPos, fromPos + 3, mOperators.size()});
            fromPos += 2;
        }
        else
        {
            mOperators.emplace_back(OpInfo{OpInfo::iNotMatch, fromPos, fromPos + 1, mOperators.size()});
            fromPos += 1;
        }
    }
    else
    {
        throw std::logic_error("syntax error");
    }
}

void PredicateParser::parseAnd(const std::string& fullExpression, size_t& fromPos)
{
    if('&' == fullExpression[fromPos + 1])
    {
        mOperators.emplace_back(OpInfo{OpInfo::And, fromPos, fromPos + 2, mOperators.size()});
        fromPos += 1;
    }
    else
    {
        throw std::logic_error("syntax error");
    }
}

void PredicateParser::parseOr(const std::string& fullExpression, size_t& fromPos)
{
    if('|' == fullExpression[fromPos + 1])
    {
        mOperators.emplace_back(OpInfo{OpInfo::Or, fromPos, fromPos + 2, mOperators.size()});
        fromPos += 1;
    }
    else
    {
        throw std::logic_error("syntax error");
    }
}

void PredicateParser::parseSub(const std::string& fullExpression, size_t& fromPos)
{}

void PredicateParser::parse(const std::string& fullExpression, size_t& fromPos, size_t endPos)
{
    assert(0 != fromPos);
    std::stack<char> unmatched;
    unmatched.push('{');
    for(; fromPos < endPos; ++fromPos)
    {
        char c = fullExpression.at(fromPos);
        if(!matchRange(unmatched, fullExpression, fromPos, endPos) && 1 == unmatched.size())
        {

            switch(c)
            {
            case '=':
                parseEqual(fullExpression, fromPos);
                break;
            case '!':
                parseNonEqual(fullExpression, fromPos);
                break;
            case '>':
                parseGreat(fullExpression, fromPos);
                break;
            case '<':
                parseLess(fullExpression, fromPos);
                break;
            case '^':
                parseStartsWith(fullExpression, fromPos);
                break;
            case '$':
                parseEndsWith(fullExpression, fromPos);
                break;
            case '*':
                parseContains(fullExpression, fromPos);
                break;
            case '~':
                parseMatch(fullExpression, fromPos);
                break;
            case '&':
                parseAnd(fullExpression, fromPos);
                break;
            case '|':
                parseOr(fullExpression, fromPos);
                break;
            case '+':
                mOperators.emplace_back(OpInfo{OpInfo::Add, fromPos, fromPos + 1, mOperators.size()});
                break;
            case '-':
                mOperators.emplace_back(OpInfo{OpInfo::Sub, fromPos, fromPos + 1, mOperators.size()});
                break;
            case '/':
                mOperators.emplace_back(OpInfo{OpInfo::Div, fromPos, fromPos + 1, mOperators.size()});
                break;
            case '%':
                mOperators.emplace_back(OpInfo{OpInfo::Mod, fromPos, fromPos + 1, mOperators.size()});
                break;
            default:
                break;
            }
        }
    }//foreach char

    mResult = createSyntaxTree(fullExpression, 0, mOperators.size());
}

std::shared_ptr<Expression> PredicateParser::createSyntaxTree(const std::string& fullExpression, size_t idxOpFrom, size_t idxOpTo)
{
    if(idxOpFrom == idxOpTo)
    {

    }
    else
    {
        auto idxLowerest = idxOpFrom;
        for(auto idxCur = idxLowerest + 1; idxCur < idxOpTo; ++idxCur)
        {
            if(mOperators[idxLowerest] < mOperators[idxCur])
            {
                idxLowerest = idxCur;
            }
        }

        if(mOperators[idxLowerest].isUnary())
        {

        }
        else
        {
            auto pLeft = createSyntaxTree(fullExpression, idxOpFrom, idxLowerest -1);
            auto pRight = createSyntaxTree(fullExpression, idxLowerest + 1, idxOpTo);
            auto pExpression =  createBinary(mOperators[idxLowerest], pLeft, pRight);
            return pExpression;
        }
    }
}

std::shared_ptr<Operand> PredicateParser::createArthemeticOp(const OpInfo& opInfo)
{
    switch (opInfo.op)
    {
    case OpInfo::Add: return std::make_shared<Add>();
    case OpInfo::Sub: return std::make_shared<Sub>();
    case OpInfo::Mul: return std::make_shared<Multiply>();
    case OpInfo::Div: return std::make_shared<Divide>();
    case OpInfo::Mod: return std::make_shared<Module>();
    case OpInfo::Minus: return std::make_shared<Add>();
    default:
        return nullptr;
    }
}

std::shared_ptr<Predicate> PredicateParser::createCompOp(const OpInfo& opInfo)
{
    switch (opInfo.op)
    {
    case OpInfo::Equal: return std::make_shared<Equal>();
    case OpInfo::StrictlyEqual: std::make_shared<StrictlyEqual>();
    case OpInfo::NonEqual: return std::make_shared<NonEqual>();
    case OpInfo::StrictlyNonEqual: return std::make_shared<StrictlyNonEqual>();
    case OpInfo::GreatThan: return std::make_shared<GreatThan>();
    case OpInfo::GreatEqual: return std::make_shared<GreatEqual>();
    case OpInfo::LessThan: return std::make_shared<LessThan>();
    case OpInfo::LessEqual: return std::make_shared<LessEqual>();

    //=========================================string comparison operators=================================
    case OpInfo::StartsWith: return std::make_shared<StartsWith>();
    case OpInfo::iStartsWith: return std::make_shared<InsensitiveStartsWith>();
    case OpInfo::EndsWith: return std::make_shared<EndsWith>();
    case OpInfo::iEndsWith: return std::make_shared<InsensitiveEndsWith>();
    case OpInfo::Contains: return std::make_shared<Contains>();
    case OpInfo::iContains: return std::make_shared<InsensitiveContains>();
    case OpInfo::Match: return std::make_shared<Match>();
    case OpInfo::iMatch: return std::make_shared<InsensitiveMatch>();
    case OpInfo::NotMatch: return std::make_shared<NonMatch>();
    case OpInfo::iNotMatch: return std::make_shared<InsensitiveNonMatch>();
    default:
        return nullptr;
    }
}

std::shared_ptr<Predicate> PredicateParser::createLogicOp(const opInfo& opInfo)
{
    switch (opInfo.op)
    {
    case OpInfo::And: return std::make_shared<Add>();
    case OpInfo::Or: return std::make_shared<Or>();
    case OpInfo::Not: return std::make_shared<Not>();
    default:
        return nullptr;
    }
}

std::shared_ptr<Predicate> PredicateParser::createUnary(const OpInfo& opInfo, const std::shared_ptr<Predicate>& pChild)
{
    switch (opInfo.op)
    {
    case OpInfo::Not:
        return std::make_shared<Not>(pChild);
    default:
        return nullptr;
    }
}

std::shared_ptr<Expression> PredicateParser::onExit()
{
    return mResult;
}
}
