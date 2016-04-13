#include "compiler/PredicateParser.h"
#include "Context.h"
#include "Filter.h"
#include "compiler/Utils.h"
#include "predicate/LogicOperator.h"
#include "predicate/ArthemeticOperator.h"
#include "predicate/StringOperator.h"
#include "predicate/Operand.h"
#include "predicate/Comparator.h"
namespace jspath
{
bool operator> (const OpInfo& lhs, const OpInfo& rhs)
{
    if(std::abs(lhs.op - rhs.op) <= 16)
    {
        return true;
    }
    else
    {
        return lhs.op < rhs.op;
    }
}

PredicateParser::PredicateParser(bool rootParser)
    :mRootParser(rootParser)
{}

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
        fromPos += 1;
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
        fromPos += 1;
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
        //a variable
        //throw std::logic_error("syntax error");
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
            mOperators.emplace_back(OpInfo{OpInfo::iNotMatch, fromPos, fromPos + 2, mOperators.size()});
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
    if(mRootParser)
    {
        unmatched.push('{');
        ++fromPos;
    }

    fromPos = skipSpace(fullExpression, fromPos, endPos);
    auto oldFrom = fromPos;
    size_t outerSize = unmatched.size();

    for(; fromPos < endPos && !(mRootParser && unmatched.empty()); ++fromPos)
    {
        char c = fullExpression.at(fromPos);
        if(!matchRange(unmatched, fullExpression, fromPos, endPos) && outerSize == unmatched.size())
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
                {
                    size_t lastOpEnd = mOperators.empty() ? oldFrom : mOperators.back().to;
                    bool isMinus = true;
                    for(size_t cur = fromPos - 1; cur >= lastOpEnd; --cur)
                    {
                        if(!std::isspace(fullExpression[cur]))
                        {
                            isMinus = false;
                        }
                    }

                    if(isMinus)
                    {
                        mOperators.emplace_back(OpInfo{OpInfo::Minus, fromPos, fromPos + 1, mOperators.size()});
                    }
                    else
                    {
                        mOperators.emplace_back(OpInfo{OpInfo::Sub, fromPos, fromPos + 1, mOperators.size()});
                    }
                    break;
                }
            case '/':
                if((oldFrom != fromPos) && (mOperators.empty() || (mOperators.back().op < OpInfo::Match) && (mOperators.back().op > OpInfo::iNotMatch)))
                {
                    mOperators.emplace_back(OpInfo{OpInfo::Div, fromPos, fromPos + 1, mOperators.size()});
                }
                else
                {
                    fromPos = skip2(fullExpression, fromPos + 1, '/', endPos) + 1;
                }
                break;
            case '%':
                mOperators.emplace_back(OpInfo{OpInfo::Mod, fromPos, fromPos + 1, mOperators.size()});
                break;
            default:
                break;
            }
        }//match range
    }//foreach char

    auto newEnd = fromPos - (mRootParser ? 1 : 0);
    if(mOperators.empty() && '(' != fullExpression.at(oldFrom))
    {
        auto pOperand = createPrimitive(fullExpression, oldFrom, newEnd);
        mResult = pOperand;
    }
    else
    {
        auto pPredicate = createPredicate(fullExpression, 0, mOperators.size(), oldFrom, newEnd);
        mResult = pPredicate;
    }
}

std::shared_ptr<Predicate> PredicateParser::createPredicate(const std::string& fullExpression, int idxOpFrom, int idxOpTo, size_t from, size_t to)
{
    if(idxOpFrom  >= idxOpTo)
    {
        unpackBrackets(fullExpression, from, to);
        PredicateParser childParaser(false);
        childParaser.parse(fullExpression, from, to);
        return childParaser.getResult();
    }
    else
    {
        auto idxLowerest = idxOpFrom;
        for(auto idxCur = idxLowerest + 1; idxCur < idxOpTo; ++idxCur)
        {
            if(mOperators[idxLowerest] > mOperators[idxCur])
            {
                idxLowerest = idxCur;
            }
        }

        auto& opInfo = mOperators[idxLowerest];
        if(mOperators[idxLowerest].isUnary())
        {
            auto pChild = createPredicate(fullExpression, idxLowerest + 1, idxOpTo, opInfo.to, to);
            auto pUnary = createUnary(opInfo, pChild);
            return pUnary;
        }
        else
        {
            auto leftFrom = from;
            auto rightTo = to;

            auto pArthemetic = createArthemeticOp(opInfo);
            if(nullptr != pArthemetic)
            {
                auto pLeft = createOperand(fullExpression, idxOpFrom, idxLowerest, leftFrom, opInfo.from);
                auto pRight = createOperand(fullExpression, idxLowerest + 1, idxOpTo, opInfo.to, rightTo);

                pArthemetic->setLeft(pLeft);
                pArthemetic->setRight(pRight);

                return pArthemetic;
            }

            auto pCompare = createCompOp(opInfo);
            if(nullptr != pCompare)
            {
                auto pLeft = createOperand(fullExpression, idxOpFrom, idxLowerest, leftFrom, opInfo.from);
                auto pRight = createOperand(fullExpression, idxLowerest + 1, idxOpTo, opInfo.to, rightTo);

                pCompare->setLeft(pLeft);
                pCompare->setRight(pRight);

                return pCompare;
            }

            auto pLogic = createLogicOp(opInfo);
            if(nullptr != pLogic)
            {
                auto pLeft = createPredicate(fullExpression, idxOpFrom, idxLowerest, leftFrom, opInfo.from);
                auto pRight = createPredicate(fullExpression, idxLowerest + 1, idxOpTo, opInfo.to, rightTo);

                pLogic->setLeft(pLeft);
                pLogic->setRight(pRight);

                return pLogic;
            }

            throw std::logic_error("unknow operator");
        }
    }
}

std::shared_ptr<Operand> PredicateParser::createOperand(const std::string& fullExpression, int idxOpFrom, int idxOpTo, size_t from, size_t to)
{
    auto pPredicate = createPredicate(fullExpression, idxOpFrom, idxOpTo, from, to);
    auto pOperand = std::dynamic_pointer_cast<Operand>(pPredicate);
    if(nullptr != pOperand)
    {
        return pOperand;
    }
    else
    {
        return std::make_shared<PredicateOperand>(pPredicate);
    }
}

std::shared_ptr<BinaryOperator<Operand, Operand>> PredicateParser::createArthemeticOp(const OpInfo& opInfo)
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

std::shared_ptr<BinaryOperator<Operand, Predicate>> PredicateParser::createCompOp(const OpInfo& opInfo)
{
    switch (opInfo.op)
    {
    case OpInfo::Equal: return std::make_shared<Equal>();
    case OpInfo::StrictlyEqual: return std::make_shared<StrictlyEqual>();
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

std::shared_ptr<BinaryOperator<Predicate, Predicate>> PredicateParser::createLogicOp(const OpInfo& opInfo)
{
    switch (opInfo.op)
    {
    case OpInfo::And: return std::make_shared<And>();
    case OpInfo::Or: return std::make_shared<Or>();
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
    case OpInfo::Minus:
        {
            auto pOperand = std::dynamic_pointer_cast<Operand>(pChild);
            if(nullptr == pOperand)
            {
                throw std::logic_error("minus shoul apply to an operand");
            }
            return std::make_shared<MinusOperand>(pOperand);
        }
    default:
        return nullptr;
    }
}

std::shared_ptr<Operand> PredicateParser::createPrimitive(const std::string& fullExpression, size_t from, size_t to)
{
    from = skipSpace(fullExpression, from, to);
    while(to > from && std::isspace(fullExpression.at(to - 1)))
    {
        --to;
    }

    if(from >= to)
    {
        return nullptr;
    }

    char c = fullExpression.at(from);
    switch(c)
    {
    case '"':
    {
        auto last = skipString(fullExpression, from + 1, to);
        auto str = fullExpression.substr(from + 1, last - from - 1);
        if(last == to)
        {
            throw std::logic_error(str + " not a string");
        }

        return std::make_shared<StringOperand>(str);
    }
    case '^':
    case '.':
    {
        Compiler subCompiler;
        auto subExpression = subCompiler.compile(fullExpression, from, to);
        return std::make_shared<LocationOperand>(subExpression);
    }
    case '{':
    {
        auto last = skip2(fullExpression, from, '}', to);
        auto str = fullExpression.substr(from, last - from + 1);
        if(last == to)
        {
            throw std::logic_error(str + " not a json");
        }

        json value(str);
        return std::make_shared<JsonOperand>(value);
    }
    case '/':
    {
        auto toPos = skip2(fullExpression, from + 1, '/', to);
        auto regex = fullExpression.substr(from + 1, toPos - from - 1);
        return std::make_shared<RegexOperand>(regex);
    }
    case '$':
    {
        auto variableName = fullExpression.substr(from + 1, to - from - 1);
        return std::make_shared<VariableOperand>(variableName);
    }
    default:
        if(isBool(fullExpression, from, to))
        {
            bool v = convert2Bool(fullExpression, from, to);
            return std::make_shared<BoolOperand>(v);
        }
        else if(isInt(fullExpression, from, to))
        {
            int v = convert2Int(fullExpression, from, to);
            return std::make_shared<IntOperand>(v);
        }
        else if(isReal(fullExpression, from, to))
        {
            double v = convert2Real(fullExpression, from, to);
            return std::make_shared<RealOperand>(v);
        }
        else
        {
            throw std::logic_error(fullExpression.substr(from, to - from) + " can't be interpreted as an operand");
        }
    }
}

std::shared_ptr<Expression> PredicateParser::onExit()
{
    return std::make_shared<Filter>(mResult);
}
}
