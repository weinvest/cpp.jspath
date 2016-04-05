#include <boost/algorithm/string/predicate.hpp>
#include "predicate/Comparator.h"
namespace jspath
{
int Compare(std::shared_ptr<Operand> op1, std::shared_ptr<Operand> op2, const Context& cxt, const json& input, Operand::type t)
{
    switch(t)
    {
    case Operand::Bool:
	{
	    bool v1 = op1->getBoolValue(cxt, input);
	    bool v2 = op2->getBoolValue(cxt, input);
	    return v1 - v2;
	}
    case Operand::Integer:
	{
	    int v1 = op1->getIntValue(cxt, input);
	    int v2 = op2->getIntValue(cxt, input);
	    return v1 - v2;
	}
    case Operand::Real:
	{
	    double v1 = op1->getRealValue(cxt, input);
	    double v2 = op2->getRealValue(cxt, input);
	    return std::abs(v1 - v2) < 1e-8;
	}
    case Operand::String:
    {
        const auto& str1 = op1->getStringValue(cxt, input);
        const auto& str2 = op2->getStringValue(cxt, input);
        return strcmp(str1.c_str(), str2.c_str());
    }
    case Operand::Json:
	{
        const auto* v1 = &op1->getJsonValue(cxt, input);
        const auto* v2 = &op2->getJsonValue(cxt, input);

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

//=================================equal==============================
bool Equal::eval(const Context &cxt, const json &input)
{
    auto t1 = mOperand1->getType(cxt, input);
    auto t2 = mOperand2->getType(cxt, input);
    auto t = t1;
    if(t1 < t2)
    {
        if(!mOperand2->canConvert2(t1, cxt, input))
        {
            return false;
        }
    }
    else if(t1 > t2)
    {
        if(!mOperand1->canConvert2(t2, cxt, input))
        {
            return false;
        }
        t = t2;
    }

    return 0 == Compare(mOperand1, mOperand2, cxt, input, t);
}

//=================================strictly equal==============================
bool StrictlyEqual::eval(const Context &cxt, const json &input)
{
    if(mOperand1->getType(cxt, input) != mOperand2->getType(cxt, input))
    {
        return false;
    }

    return 0 == Compare(mOperand1, mOperand2, cxt, input, mOperand1->getType(cxt, input));
}

//=================================non equal==============================
bool NonEqual::eval(const Context &cxt, const json &input)
{
    auto t1 = mOperand1->getType(cxt, input);
    auto t2 = mOperand2->getType(cxt, input);
    auto t = t1;
    if(t1 < t2)
    {
        if(!mOperand2->canConvert2(t1, cxt, input))
	{
	    return false;
	}
    }
    else if(t1 > t2)
    {
	if(!mOperand1->canConvert2(t2, cxt, input))
	{
	    return false;
	}
	t = t2;
    }

    return 0 != Compare(mOperand1, mOperand2, cxt, input, t);
}

//=================================strictly non equal==============================
bool StrictlyNonEqual::eval(const Context &cxt, const json &input)
{
    if(mOperand1->getType(cxt, input) != mOperand2->getType(cxt, input))
    {
	return true;
    }
    return 0 != Compare(mOperand1, mOperand2, cxt, input, mOperand1->getType(cxt, input));
}

//=================================great than==============================
bool GreatThan::eval(const Context &cxt, const json &input)
{
    if(mOperand1->getType(cxt, input) != mOperand2->getType(cxt, input))
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, input, mOperand1->getType(cxt, input)) > 0;
}

//=================================great equal==============================
bool GreatEqual::eval(const Context &cxt, const json &input)
{
    if(mOperand1->getType(cxt, input) != mOperand2->getType(cxt, input))
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, input, mOperand1->getType(cxt, input)) >= 0;
}

//=================================less than ==============================
bool LessThan::eval(const Context &cxt, const json &input)
{
    if(mOperand1->getType(cxt, input) != mOperand2->getType(cxt, input))
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, input, mOperand1->getType(cxt, input)) < 0;
}

//=================================less equal ==============================
bool LessEqual::eval(const Context &cxt, const json &input)
{
    if(mOperand1->getType(cxt, input) != mOperand2->getType(cxt, input))
    {
        return false;
    }

    return Compare(mOperand1, mOperand2, cxt, input, mOperand1->getType(cxt, input)) <= 0;
}
}
