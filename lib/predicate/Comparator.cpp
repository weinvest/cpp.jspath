#include <boost/algorithm/string/predicate.hpp>
#include "predicate/Comparator.h"
#include "compiler/Utils.h"
namespace jspath
{
int Compare(std::shared_ptr<Operand> op1, std::shared_ptr<Operand> op2
    , const Context& cxt
    , const json& variables
    , Operand::type t)
{
    switch(t)
    {
    case Operand::Bool:
	{
	    bool v1 = op1->getBoolValue(cxt, variables);
	    bool v2 = op2->getBoolValue(cxt, variables);
	    return v1 - v2;
	}
    case Operand::Integer:
	{
	    int v1 = op1->getIntValue(cxt, variables);
	    int v2 = op2->getIntValue(cxt, variables);
	    return v1 - v2;
	}
    case Operand::Real:
	{
	    double v1 = op1->getRealValue(cxt, variables);
	    double v2 = op2->getRealValue(cxt, variables);

        double diff = v1 - v2;
	    if(std::abs(diff) < 1e-8)
        {
            return 0;
        }

        return diff > 0 ? 1 : -1;
	}
    case Operand::String:
    {
        const auto& str1 = op1->getStringValue(cxt, variables);
        const auto& str2 = op2->getStringValue(cxt, variables);
        return strcmp(str1.c_str(), str2.c_str());
    }
    case Operand::Json:
	{
        const auto* v1 = &op1->getJsonValue(cxt, variables);
        const auto* v2 = &op2->getJsonValue(cxt, variables);

        if((v1->is_primitive() && v2->is_primitive())
            ||
           (v1->is_object() && v2->is_object()))
        {
            return *v1 == *v2 ? 0 : 1;
        }

        if(v1->is_array() && !v2->is_array())
        {
            const auto* tmp = v2;
            v2 = v1;
            v1 = tmp;
        }

        if(v1->is_array() && v2->is_array())
        {
            for(const auto& child1 : *v1)
            {
                for(const auto& child2 : *v2)
                {
                    if(child1 == child2)
                    {
                        return 0;
                    }
                }
            }
        }
        else if(v2->is_array())
        {
            for(const auto& child : *v2)
            {
                if(*v1 == child)
                {
                    return 0;
                }
            }
        }

        return 1;
	}
    }//switch

    return 1;
}

bool CompareJson(std::shared_ptr<Operand> op1
    , std::shared_ptr<Operand> op2
    , const Context& cxt
    , const json& variables
    , const CompareBase::CompareAtT& t
    , bool isStrict = false)
{
    if(Operand::Json != std::get<1>(t))
    {
        std::shared_ptr<Operand> tmp(op1);
        op1 = op2;
        op2 = tmp;
    }

    const auto& v2 = op2->getJsonValue(cxt, variables);
    if(!v2.is_array())
    {
        return false;
    }

    auto t1 = std::get<0>(t);
    for(auto& child : v2)
    {
        if(child.is_primitive())
        {
            if(child.is_string() && Operand::String == t1)
            {
                if(child.get<std::string>() == op1->getStringValue(cxt, variables))
                {
                    return true;
                }
            }
            else if(child.is_string())
            {
                if(isStrict)
                {
                    continue;
                }

                auto s = child.get<std::string>();
                auto size = s.size();
                switch (t1)
                {
                case Operand::Bool:
                    if(isBool(s, 0, size) && convert2Bool(s, 0, size) == op1->getBoolValue(cxt, variables))
                    {
                        return true;
                    }
                    break;
                case Operand::Integer:
                    if(isInt(s, 0, size) && convert2Int(s, 0, size) == op1->getIntValue(cxt, variables))
                    {
                        return true;
                    }
                    break;
                case Operand::Real:
                    if(isReal(s, 0, size) && convert2Real(s, 0, size) == op1->getRealValue(cxt, variables))
                    {
                        return true;
                    }
                    break;
                default:
                    /* code */
                    break;
                }
            }
            else
            {
                if(isStrict)
                {
                    continue;
                }

                if(child.is_boolean()
                    && op1->canConvert2(Operand::Bool, cxt, variables)
                    && child.get<bool>() == op1->getBoolValue(cxt, variables))
                {
                    return true;
                }
                else if(child.is_number_integer()
                    && op1->canConvert2(Operand::Integer, cxt, variables)
                    && child.get<int>() == op1->getIntValue(cxt, variables))
                {
                    return true;
                }
                else if(child.is_number_float()
                    && op1->canConvert2(Operand::Real, cxt, variables)
                    && child.get<double>() == op1->getRealValue(cxt, variables))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
//================================CompareBase=========================
CompareBase::CompareAtT CompareBase::compareAt(const Context& cxt, const json& variables)
{
    auto t1 = mOperand1->getType(cxt, variables);
    auto t2 = mOperand2->getType(cxt, variables);
    if(t1 == t2)
    {
        return std::make_tuple(t1, t2, t1);
    }
    else if(t1 < Operand::String && t2 < Operand::String)
    {
        return std::make_tuple(t1, t2, t1 > t2 ? t1 : t2);
    }
    else if(Operand::String == t1 && (t2 < Operand::String) && mOperand1->canConvert2(t2, cxt, variables))
    {
        return std::make_tuple(t1, t2, t2);
    }
    else if(Operand::String == t2 && (t1 < Operand::String) && mOperand2->canConvert2(t1, cxt, variables))
    {
        return std::make_tuple(t1, t2, t1);
    }

    return std::make_tuple(t1, t2, Operand::Unknown);
}

//=================================equal==============================
bool Equal::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == std::get<2>(t))
    {
        if(Operand::Json == std::get<0>(t) || Operand::Json == std::get<1>(t))
        {
            return CompareJson(mOperand1, mOperand2, cxt, variables, t);
        }
        return false;
    }

    return 0 == Compare(mOperand1, mOperand2, cxt, variables, std::get<2>(t));
}

//=================================strictly equal==============================
bool StrictlyEqual::eval(const Context &cxt, const json &variables)
{
    auto t1 = mOperand1->getType(cxt, variables);
    auto t2 = mOperand2->getType(cxt, variables);
    if(t1 != t2)
    {
        if(Operand::Json == t1 || Operand::Json == t2)
        {
            return CompareJson(mOperand1, mOperand2, cxt, variables, std::make_tuple(t1, t2, Operand::Json), true);
        }
        return false;
    }

    return 0 == Compare(mOperand1, mOperand2, cxt, variables, t1);
}

//=================================non equal==============================
bool NonEqual::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == std::get<2>(t))
    {
        if(Operand::Json == std::get<0>(t) || Operand::Json == std::get<1>(t))
        {
            return !CompareJson(mOperand1, mOperand2, cxt, variables, t);
        }
        return false;
    }

    return 0 != Compare(mOperand1, mOperand2, cxt, variables, std::get<2>(t));
}

//=================================strictly non equal==============================
bool StrictlyNonEqual::eval(const Context &cxt, const json &variables)
{
    auto t1 = mOperand1->getType(cxt, variables);
    auto t2 = mOperand2->getType(cxt, variables);
    if(t1 != t2)
    {
        if(Operand::Json == t1 || Operand::Json == t2)
        {
            return !CompareJson(mOperand1, mOperand2, cxt, variables, std::make_tuple(t1, t2, Operand::Json), true);
        }
	    return false;
    }
    return 0 != Compare(mOperand1, mOperand2, cxt, variables, t1);
}

//=================================great than==============================
bool GreatThan::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == std::get<2>(t))
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, variables, std::get<2>(t)) > 0;
}

//=================================great equal==============================
bool GreatEqual::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == std::get<2>(t))
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, variables, std::get<2>(t)) >= 0;
}

//=================================less than ==============================
bool LessThan::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == std::get<2>(t))
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, variables, std::get<2>(t)) < 0;
}

//=================================less equal ==============================
bool LessEqual::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == std::get<2>(t))
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, variables, std::get<2>(t)) <= 0;
}
}
