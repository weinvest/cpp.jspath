#include <cstdlib>
#include <boost/algorithm/string/predicate.hpp>
#include "compiler/Utils.h"
#include "predicate/StringOperator.h"
namespace jspath
{
//================================sensitive equal=========================
bool SensitiveEqual::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);

    return boost::algorithm::equals(str1, str2);
}

//================================insensitive equal=========================
bool InsensitiveEqual::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);

    return boost::algorithm::iequals(str1, str2);
}

//================================starts with =========================
bool StartsWith::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);
    return boost::starts_with(str1, str2);
}

//================================insensitive starts with =========================
bool InsensitiveStartsWith::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);

    return boost::istarts_with(str1, str2);
}

//================================ends with =========================
bool EndsWith::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);
    return boost::ends_with(str1, str2);
}

//================================insensitive ends with =========================
bool InsensitiveEndsWith::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);

    return boost::iends_with(str1, str2);
}

//===============================Match===========================================
bool Contains::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);

    return boost::algorithm::contains(str1, str2);
}

//===============================insensitive contains===========================================
bool InsensitiveContains::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);

    return boost::algorithm::icontains(str1, str2);
}

//===============================Match===========================================
bool Match::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);

    return isMatch(str1, str2);
}

//===============================insensitive Match===========================================
bool InsensitiveMatch::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);

    return isMatch(str1, str2, true);
}

//===============================Match===========================================
bool NonMatch::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);

    return !isMatch(str1, str2);
}

//===============================insensitive Match===========================================
bool InsensitiveNonMatch::eval(const Context& cxt, const json& variables)
{
    const auto& str1 = mOperand1->getStringValue(cxt, variables);
    const auto& str2 = mOperand2->getStringValue(cxt, variables);

    return !isMatch(str1, str2, true);
}
}
