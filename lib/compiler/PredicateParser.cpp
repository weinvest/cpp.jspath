#include "compiler/PredicateParser.h"
#include "Context.h"
#include "compiler/Utils.h"
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

std::shared_ptr<Expression> PredicateParser::createSyntaxTree(const std::string& fullExpression, size_t idxOpFrom, size_ idxOpTo)
{
    if(idxOpFrom == idxOpTo)
    {

    }
    else
    {
        
    }
}

std::shared_ptr<Expression> PredicateParser::onExit()
{
    return mResult;
}
}
