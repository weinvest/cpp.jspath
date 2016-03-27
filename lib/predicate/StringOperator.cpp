#include <cstdlib>
#include <boost/algorithm/string/predicate.hpp>
#include "predicate/StringOperator.h"
namespace jspath
{
//================================sensitive equal=========================
bool SensitiveEqual::eval(const Context& cxt, const json& input)
{
    const auto& str1 = mOperand1->getStringValue(cxt, input);
    const auto& str2 = mOperand2->getStringValue(cxt, input);

    return boost::algorithm::equals(str1, str2);
}

//================================insensitive equal=========================
bool InsensitiveEqual::eval(const Context& cxt, const json& input)
{
    const auto& str1 = mOperand1->getStringValue(cxt, input);
    const auto& str2 = mOperand2->getStringValue(cxt, input);

    return boost::algorithm::iequals(str1, str2);
}

//================================starts with =========================
bool StartsWith::eval(const Context& cxt, const json& input)
{
    const auto& str1 = mOperand1->getStringValue(cxt, input);
    const auto& str2 = mOperand2->getStringValue(cxt, input);
    return boost::starts_with(str1, str2);
}

//================================insensitive starts with =========================
bool InsensitiveStartsWith::eval(const Context& cxt, const json& input)
{
    const auto& str1 = mOperand1->getStringValue(cxt, input);
    const auto& str2 = mOperand2->getStringValue(cxt, input);

    return boost::istarts_with(str1, str2);
}

//================================ends with =========================
bool EndsWith::eval(const Context& cxt, const json& input)
{
    const auto& str1 = mOperand1->getStringValue(cxt, input);
    const auto& str2 = mOperand2->getStringValue(cxt, input);
    return boost::ends_with(str1, str2);
}

//================================insensitive ends with =========================
bool InsensitiveEndsWith::eval(const Context& cxt, const json& input)
{
    const auto& str1 = mOperand1->getStringValue(cxt, input);
    const auto& str2 = mOperand2->getStringValue(cxt, input);

    return boost::iends_with(str1, str2);
}

//===============================contains===========================================
bool Contains::eval(const Context& cxt, const json& input)
{
    const auto& str1 = mOperand1->getStringValue(cxt, input);
    const auto& str2 = mOperand2->getStringValue(cxt, input);

    return boost::algorithm::contains(str1, str2);
}

//===============================insensitive contains===========================================
bool InsensitiveContains::eval(const Context& cxt, const json& input)
{
    const auto& str1 = mOperand1->getStringValue(cxt, input);
    const auto& str2 = mOperand2->getStringValue(cxt, input);

    return boost::algorithm::icontains(str1, str2);
}
}
