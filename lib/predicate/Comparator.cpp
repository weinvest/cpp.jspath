#include <boost/algorithm/string/predicate.hpp>
#include "predicate/Comparator.h"
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

        if(v1->is_structured() && v2->is_primitive())
        {
            const auto* tmp = v2;
            v2 = v1;
            v1 = tmp;
        }

        if(v1->is_primitive())
        {
            if(v2->is_primitive())
            {
                return *v1 == *v2;
            }

            if(v2->is_structured())
            {
                for(const auto& child : *v2)
                {
                    if(*v1 == child)
                    {
                        return true;
                    }
                }
            }
        }
        else
        {
            for(const auto& child1 : *v1)
            {
                for(const auto& child2 : *v2)
                {
                    if(child1 == child2)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
	}
    }

    return false;
}

int CompareJson(std::shared_ptr<Operand> op1
    , std::shared_ptr<Operand> op2
    , const Context& cxt
    , const json& variables
    , Operand::type t1
    , Operand::type t2)
{
    return false;
}
//================================CompareBase=========================
Operand::type CompareBase::compareAt(const Context& cxt, const json& variables)
{
    auto t1 = mOperand1->getType(cxt, variables);
    auto t2 = mOperand2->getType(cxt, variables);
    if(t1 == t2)
    {
        return t1;
    }
    else if(t1 < Operand::String && t2 < Operand::String)
    {
        return t1 > t2 ? t1 : t2;
    }
    else if(Operand::String == t1 && (t2 < Operand::String) && mOperand1->canConvert2(t2, cxt, variables))
    {
        return t2;
    }
    else if(Operand::String == t2 && (t1 < Operand::String) && mOperand2->canConvert2(t1, cxt, variables))
    {
        return t1;
    }

    return Operand::Unknown;
}

//=================================equal==============================
bool Equal::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == t)
    {
        return false;
    }

    return 0 == Compare(mOperand1, mOperand2, cxt, variables, t);
}

//=================================strictly equal==============================
bool StrictlyEqual::eval(const Context &cxt, const json &variables)
{
    auto t1 = mOperand1->getType(cxt, variables);
    auto t2 = mOperand2->getType(cxt, variables);
    if(t1 != t2)
    {
        return false;
    }

    return 0 == Compare(mOperand1, mOperand2, cxt, variables, t1);
}

//=================================non equal==============================
bool NonEqual::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == t)
    {
        return false;
    }

    return 0 != Compare(mOperand1, mOperand2, cxt, variables, t);
}

//=================================strictly non equal==============================
bool StrictlyNonEqual::eval(const Context &cxt, const json &variables)
{
    if(mOperand1->getType(cxt, variables) != mOperand2->getType(cxt, variables))
    {
	    return true;
    }
    return 0 != Compare(mOperand1, mOperand2, cxt, variables, mOperand1->getType(cxt, variables));
}

//=================================great than==============================
bool GreatThan::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == t)
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, variables, t) > 0;
}

//=================================great equal==============================
bool GreatEqual::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == t)
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, variables, t) >= 0;
}

//=================================less than ==============================
bool LessThan::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == t)
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, variables, t) < 0;
}

//=================================less equal ==============================
bool LessEqual::eval(const Context &cxt, const json &variables)
{
    auto t = compareAt(cxt, variables);
    if(Operand::Unknown == t)
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, variables, t) <= 0;
}
}
