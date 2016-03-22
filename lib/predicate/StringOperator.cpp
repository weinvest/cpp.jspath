#include <cstdlib>
#include <boost/algorithm/string/predicate.hpp>
#include "predicate/StringOperator.h"
namespace jspath
{
//================================sensitive equal=========================
SensitiveEqual::SensitiveEqual(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool SensitiveEqual::eval(const Context& cxt, const ptree& input)
{
    auto str1 = mOperand1->getStringValue(cxt, input);
    auto str2 = mOperand2->getStringValue(cxt, input);

    return boost::algorithm::equals(str1, str2);
}

//================================insensitive equal=========================
InsensitiveEqual::InsensitiveEqual(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool InsensitiveEqual::eval(const Context& cxt, const ptree& input)
{
    auto str1 = mOperand1->getStringValue(cxt, input);
    auto str2 = mOperand2->getStringValue(cxt, input);

    return boost::algorithm::iequals(str1, str2);
}

//================================starts with =========================
StartsWith::StartsWith(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool StartsWith::eval(const Context& cxt, const ptree& input)
{
    auto str1 = mOperand1->getStringValue(cxt, input);
    auto str2 = mOperand2->getStringValue(cxt, input);
    return boost::starts_with(str1, str2);
}

//================================insensitive starts with =========================
InsensitiveStartsWith::InsensitiveStartsWith(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool InsensitiveStartsWith::eval(const Context& cxt, const ptree& input)
{
    auto str1 = mOperand1->getStringValue(cxt, input);
    auto str2 = mOperand2->getStringValue(cxt, input);

    return boost::istarts_with(str1, str2);
}

//================================ends with =========================
EndsWith::EndsWith(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool EndsWith::eval(const Context& cxt, const ptree& input)
{
    auto str1 = mOperand1->getStringValue(cxt, input);
    auto str2 = mOperand2->getStringValue(cxt, input);
    return boost::ends_with(str1, str2);
}

//================================insensitive ends with =========================
InsensitiveEndsWith::InsensitiveEndsWith(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool InsensitiveEndsWith::eval(const Context& cxt, const ptree& input)
{
    auto str1 = mOperand1->getStringValue(cxt, input);
    auto str2 = mOperand2->getStringValue(cxt, input);

    return boost::iends_with(str1, str2);
}

//===============================contains===========================================
Contains::Contains(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool Contains::eval(const Context& cxt, const ptree& input)
{
    auto str1 = mOperand1->getStringValue(cxt, input);
    auto str2 = mOperand2->getStringValue(cxt, input);

    return boost::algorithm::contains(str1, str2);
}

//===============================insensitive contains===========================================
InsensitiveContains::InsensitiveContains(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool InsensitiveContains::eval(const Context& cxt, const ptree& input)
{
    auto str1 = mOperand1->getStringValue(cxt, input);
    auto str2 = mOperand2->getStringValue(cxt, input);

    return boost::algorithm::icontains(str1, str2);
}
}
