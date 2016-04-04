#include <stdexcept>
#include "predicate/ArthemeticOperator.h"

namespace jspath
{
    //=============================ArthemeticOperator===========================
    ArthemeticOperator::ArthemeticOperator(Operator op)
        :Base(Operand::Composite)
        ,mOperator(op)
    {}

    Operand::type ArthemeticOperator::getType(const Context& cxt, const json& input) const
    {
        auto t1 = mOperand1->getType(cxt, input);
        auto t2 = mOperand2->getType(cxt, input);
        if(t1 == t2)
        {
            if(Operand::Array == t1)
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

    int ArthemeticOperator::getIntValue(const Context& cxt, const json& input)
    {
        auto t = getType(cxt, input);
        if(t <= Operand::Integer)
        {
            int v1 = mOperand1->getIntValue(cxt, input);
            int v2 = mOperand2->getIntValue(cxt, input);
            return apply(v1, v2);
        }
        throw std::logic_error("Divide.getIntValue only availabe for Operand::Bool/Int");
    }

    double ArthemeticOperator::getRealValue(const Context& cxt, const json& input)
    {
        auto t = getType(cxt, input);
        if(t <= Operand::Real)
        {
            double v1 = mOperand1->getRealValue(cxt, input);
            double v2 = mOperand2->getRealValue(cxt, input);
            return apply(v1, v2);
        }
        throw std::logic_error("Divide.getRealValue only availabe for Operand::Bool/Int/Real");
    }

    //===================================Add====================================
    Add::Add()
        :ArthemeticOperator(ArthemeticOperator::OP_Div)
    {
    }

    bool Add::getBoolValue(const Context& cxt, const json& input)
    {
        auto t = getType(cxt, input);
        switch (t)
        {
        case Operand::Bool:
            return mOperand1->getBoolValue(cxt, input) || mOperand2->getBoolValue(cxt, input);
        case Operand::Integer:
            return 0 != (mOperand1->getIntValue(cxt, input) + mOperand2->getIntValue(cxt, input));
        case Operand::Real:
            return std::abs(mOperand1->getIntValue(cxt, input) + mOperand2->getIntValue(cxt, input)) > 1e-8;
        case Operand::String:
            return mOperand1->getStringValue(cxt, input).length() > 0
                || mOperand2->getStringValue(cxt, input).length() > 0;
        default:
            throw std::logic_error("Add.getBoolValue only available for Operand::Bool/Int/Real/String");
        }
    }

    const std::string& Add::getStringValue(const Context& cxt, const json& input)
    {
        static std::string result;
        auto t = getType(cxt, input);
        if(Operand::String != t)
        {
            throw std::logic_error("Add.getStringValue only availabe for Operand::String");
        }

        result = mOperand1->getStringValue(cxt, input);
        result += mOperand1->getStringValue(cxt, input);
        return result;
    }

    //===================================Sub====================================
    Sub::Sub()
        :ArthemeticOperator(ArthemeticOperator::OP_Sub)
    {
    }

    bool Sub::getBoolValue(const Context& cxt, const json& input)
    {
        auto t = getType(cxt, input);
        switch (t)
        {
        case Operand::Bool:
            return mOperand1->getBoolValue(cxt, input) || mOperand2->getBoolValue(cxt, input);
        case Operand::Integer:
            return 0 != (mOperand1->getIntValue(cxt, input) + mOperand2->getIntValue(cxt, input));
        case Operand::Real:
            return std::abs(mOperand1->getIntValue(cxt, input) + mOperand2->getIntValue(cxt, input)) > 1e-8;
        case Operand::String:
            return mOperand1->getStringValue(cxt, input).length() > 0
                || mOperand2->getStringValue(cxt, input).length() > 0;
        default:
            throw std::logic_error("Sub.getBoolValue only available for Operand::Bool/Int/Real/String");
        }
    }

    const std::string& Sub::getStringValue(const Context& cxt, const json& input)
    {
        static std::string result;
        auto t = getType(cxt, input);
        if(Operand::String != t)
        {
            throw std::logic_error("Sub.getStringValue only availabe for Operand::String");
        }

        result = mOperand1->getStringValue(cxt, input);
        result += mOperand1->getStringValue(cxt, input);
        return result;
    }

    //===================================Multiply====================================
    Multiply::Multiply()
        :ArthemeticOperator(ArthemeticOperator::OP_Multiply)
    {
    }

    bool Multiply::getBoolValue(const Context& cxt, const json& input)
    {
        auto t = getType(cxt, input);
        switch (t)
        {
        case Operand::Bool:
            return mOperand1->getBoolValue(cxt, input) || mOperand2->getBoolValue(cxt, input);
        case Operand::Integer:
            return 0 != (mOperand1->getIntValue(cxt, input) + mOperand2->getIntValue(cxt, input));
        case Operand::Real:
            return std::abs(mOperand1->getIntValue(cxt, input) + mOperand2->getIntValue(cxt, input)) > 1e-8;
        case Operand::String:
            return mOperand1->getStringValue(cxt, input).length() > 0
                || mOperand2->getStringValue(cxt, input).length() > 0;
        default:
            throw std::logic_error("Multiply.getBoolValue only available for Operand::Bool/Int/Real/String");
        }
    }

    const std::string& Multiply::getStringValue(const Context& cxt, const json& input)
    {
        static std::string result;
        auto t = getType(cxt, input);
        if(Operand::String != t)
        {
            throw std::logic_error("Multiply.getStringValue only availabe for Operand::String");
        }

        result = mOperand1->getStringValue(cxt, input);
        result += mOperand1->getStringValue(cxt, input);
        return result;
    }

    //===================================Divide====================================
    Divide::Divide()
        :ArthemeticOperator(ArthemeticOperator::OP_Divide)
    {
    }

    bool Divide::getBoolValue(const Context& cxt, const json& input)
    {
        auto t = getType(cxt, input);
        switch (t)
        {
        case Operand::Bool:
            return mOperand1->getBoolValue(cxt, input) || mOperand2->getBoolValue(cxt, input);
        case Operand::Integer:
            return 0 != (mOperand1->getIntValue(cxt, input) + mOperand2->getIntValue(cxt, input));
        case Operand::Real:
            return std::abs(mOperand1->getIntValue(cxt, input) + mOperand2->getIntValue(cxt, input)) > 1e-8;
        case Operand::String:
            return mOperand1->getStringValue(cxt, input).length() > 0
                || mOperand2->getStringValue(cxt, input).length() > 0;
        default:
            throw std::logic_error("Divide.getBoolValue only available for Operand::Bool/Int/Real/String");
        }
    }

    const std::string& Divide::getStringValue(const Context& cxt, const json& input)
    {
        static std::string result;
        auto t = getType(cxt, input);
        if(Operand::String != t)
        {
            throw std::logic_error("Divide.getStringValue only availabe for Operand::String");
        }

        result = mOperand1->getStringValue(cxt, input);
        result += mOperand1->getStringValue(cxt, input);
        return result;
    }
}
