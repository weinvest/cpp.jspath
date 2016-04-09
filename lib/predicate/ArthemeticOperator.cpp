#include <stdexcept>
#include "predicate/ArthemeticOperator.h"

namespace jspath
{
    //=============================ArthemeticOperator===========================
    ArthemeticOperator::ArthemeticOperator(Operator op)
        :Base(Operand::Composite)
        ,mOperator(op)
    {}

    Operand::type ArthemeticOperator::getType(const Context& cxt, const json& variables) const
    {
        auto t1 = mOperand1->getType(cxt, variables);
        auto t2 = mOperand2->getType(cxt, variables);
        if(t1 == t2)
        {
            if(Operand::Json == t1)
            {
                return Operand::Unknown;
            }
            else
            {
                return t1;
            }
        }
        else if(Operand::String > t1 && Operand::String > t2)
        {
            return t1 > t2 ? t1 : t2;
        }
        else
        {
            return Operand::Unknown;
        }
    }

    int ArthemeticOperator::getIntValue(const Context& cxt, const json& variables)
    {
        auto t = getType(cxt, variables);
        if(t <= Operand::Integer)
        {
            int v1 = mOperand1->getIntValue(cxt, variables);
            int v2 = mOperand2->getIntValue(cxt, variables);
            return apply(v1, v2);
        }
        throw std::logic_error("Divide.getIntValue only availabe for Operand::Bool/Int");
    }

    double ArthemeticOperator::getRealValue(const Context& cxt, const json& variables)
    {
        auto t = getType(cxt, variables);
        if(t <= Operand::Real)
        {
            double v1 = mOperand1->getRealValue(cxt, variables);
            double v2 = mOperand2->getRealValue(cxt, variables);
            return apply(v1, v2);
        }
        throw std::logic_error("Divide.getRealValue only availabe for Operand::Bool/Int/Real");
    }

    //===================================Add====================================
    Add::Add()
        :ArthemeticOperator(ArthemeticOperator::OP_Add)
    {
    }

    bool Add::getBoolValue(const Context& cxt, const json& variables)
    {
        auto t = getType(cxt, variables);
        switch (t)
        {
        case Operand::Bool:
            return mOperand1->getBoolValue(cxt, variables) || mOperand2->getBoolValue(cxt, variables);
        case Operand::Integer:
            return 0 != (mOperand1->getIntValue(cxt, variables) + mOperand2->getIntValue(cxt, variables));
        case Operand::Real:
            return std::abs(mOperand1->getIntValue(cxt, variables) + mOperand2->getIntValue(cxt, variables)) > 1e-8;
        case Operand::String:
            return mOperand1->getStringValue(cxt, variables).length() > 0
                || mOperand2->getStringValue(cxt, variables).length() > 0;
        default:
            throw std::logic_error("Add.getBoolValue only available for Operand::Bool/Int/Real/String");
        }
    }

    const std::string& Add::getStringValue(const Context& cxt, const json& variables)
    {
        auto t = getType(cxt, variables);
        if(Operand::String != t)
        {
            throw std::logic_error("Add.getStringValue only availabe for Operand::String");
        }

        mTemp = mOperand1->getStringValue(cxt, variables);
        mTemp += mOperand1->getStringValue(cxt, variables);
        return mTemp;
    }

    //===================================Sub====================================
    Sub::Sub()
        :ArthemeticOperator(ArthemeticOperator::OP_Sub)
    {
    }

    bool Sub::getBoolValue(const Context& cxt, const json& variables)
    {
        auto t = getType(cxt, variables);
        switch (t)
        {
        case Operand::Bool:
            return 0 != (mOperand1->getBoolValue(cxt, variables) - mOperand2->getBoolValue(cxt, variables));
        case Operand::Integer:
            return 0 != (mOperand1->getIntValue(cxt, variables) - mOperand2->getIntValue(cxt, variables));
        case Operand::Real:
            return std::abs(mOperand1->getIntValue(cxt, variables) - mOperand2->getIntValue(cxt, variables)) > 1e-8;
        default:
            throw std::logic_error("Sub.getBoolValue only available for Operand::Bool/Int/Real");
        }
    }

    const std::string& Sub::getStringValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("Sub.getStringValue not supported");
    }

    //===================================Multiply====================================
    Multiply::Multiply()
        :ArthemeticOperator(ArthemeticOperator::OP_Mul)
    {
    }

    bool Multiply::getBoolValue(const Context& cxt, const json& variables)
    {
        auto t = getType(cxt, variables);
        switch (t)
        {
        case Operand::Bool:
            return mOperand1->getBoolValue(cxt, variables) && mOperand2->getBoolValue(cxt, variables);
        case Operand::Integer:
            return 0 != (mOperand1->getIntValue(cxt, variables) * mOperand2->getIntValue(cxt, variables));
        case Operand::Real:
            return std::abs(mOperand1->getIntValue(cxt, variables) * mOperand2->getIntValue(cxt, variables)) > 1e-8;
        default:
            throw std::logic_error("Multiply.getBoolValue only available for Operand::Bool/Int/Real");
        }
    }

    const std::string& Multiply::getStringValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("Multiply.getStringValue not supported");
    }

    //===================================Divide====================================
    Divide::Divide()
        :ArthemeticOperator(ArthemeticOperator::OP_Div)
    {
    }

    bool Divide::getBoolValue(const Context& cxt, const json& variables)
    {
        auto t = getType(cxt, variables);
        switch (t)
        {
        case Operand::Bool:
            return mOperand1->getBoolValue(cxt, variables);
        case Operand::Integer:
            return 0 != mOperand1->getIntValue(cxt, variables);
        case Operand::Real:
            return std::abs(mOperand1->getIntValue(cxt, variables)) > 1e-8;
        default:
            throw std::logic_error("Divide.getBoolValue only available for Operand::Bool/Int/Real");
        }
    }

    const std::string& Divide::getStringValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("Divide.getStringValue not supported");
    }

    //===================================Module====================================
    Operand::type Module::getType(const Context& cxt, const json& variables) const
    {
        auto t1 = mOperand1->getType(cxt, variables);
        auto t2 = mOperand2->getType(cxt, variables);
        if(t1 == t2 && (Operand::Integer == t1))
        {
            return t1;
        }
        return Operand::Unknown;
    }

    bool Module::getBoolValue(const Context& cxt, const json& variables)
    {
        return 0 != getIntValue(cxt, variables);
    }

    int Module::getIntValue(const Context& cxt, const json& variables)
    {
        auto t = getType(cxt, variables);
        if (Operand::Integer == t)
        {
            return (mOperand1->getIntValue(cxt, variables) % mOperand2->getIntValue(cxt, variables));
        }
        else
        {
            throw std::logic_error("Module::getIntValue( only available for Operand::Int");
        }
    }

    double Module::getRealValue(const Context& cxt, const json& variables)
    {
        return getIntValue(cxt, variables);
    }

    const std::string& Module::getStringValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("Module::getStringValue not supported");
    }
}
