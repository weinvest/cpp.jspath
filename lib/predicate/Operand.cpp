#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "predicate/Operand.h"
#include "compiler/Utils.h"
#include "Expression.h"
#include "Context.h"
namespace jspath
{
    JSENUM_IMPL_TO_STRING(Operand, OPERAND_TYPES)
    JSENUM_IMPL_PARSE(Operand, OPERAND_TYPES)

    //=======================Operand===========================
    Operand::Operand(type t)
    :mType(t)
    {}

    Operand::~Operand()
    {}

    bool Operand::eval(const Context& cxt, const json& variables)
    {
        return getBoolValue(cxt, variables);
    }

    const json& Operand::getJsonValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("no json value availabe");
    }

    //=======================BoolOperand===========================
    BoolOperand::BoolOperand(bool v)
    :Operand(Operand::Bool)
    ,mBoolValue(v)
    {
    }

    bool BoolOperand::canConvert2(type t, const Context& cxt, const json& variables)
    {
         return Operand::Integer == t || Operand::Real == t;
    }

    bool BoolOperand::getBoolValue(const Context& cxt, const json& variables)
    {
        return mBoolValue;
    }

    int BoolOperand::getIntValue(const Context& /*cxt*/, const json& /*variables*/)
    {
        return mBoolValue;
    }

    double BoolOperand::getRealValue(const Context& /*cxt*/, const json& /*variables*/)
    {
        return mBoolValue;
    }

    const std::string& BoolOperand::getStringValue(const Context& /*cxt*/, const json& /*variables*/)
    {
        throw std::logic_error("BoolOperand::getStringValue not supported");
    }

    //=======================IntOperand===========================
    IntOperand::IntOperand(int v)
    :Operand(Operand::Integer)
    ,mIntValue(v)
    {}

    bool IntOperand::canConvert2(type t, const Context& cxt, const json& variables)
    {
        return Operand::Bool == t || Operand::Real == t;
    }

    bool IntOperand::getBoolValue(const Context& cxt, const json& variables)
    {
        return 0 != mIntValue;
    }

    int IntOperand::getIntValue(const Context& /*cxt*/, const json& /*variables*/)
    {
        return mIntValue;
    }

    double IntOperand::getRealValue(const Context& /*cxt*/, const json& /*variables*/)
    {
        return mIntValue;
    }

    const std::string& IntOperand::getStringValue(const Context& /*cxt*/, const json& /*variables*/)
    {
        throw std::logic_error("IntOperand::getStringValue not supported");
    }

    //=======================RealOperand===========================
    RealOperand::RealOperand(double v)
    :Operand(Operand::Real)
    ,mRealValue(v)
    {}

    bool RealOperand::canConvert2(type t, const Context& cxt, const json& variables)
    {
        return Operand::Bool == t || Operand::Integer == t;
    }

    bool RealOperand::getBoolValue(const Context& cxt, const json& variables)
    {
        return std::abs(mRealValue) < 1e-8;
    }

    int RealOperand::getIntValue(const Context& /*cxt*/, const json& /*variables*/)
    {
        return mRealValue;
    }

    double RealOperand::getRealValue(const Context& /*cxt*/, const json& /*variables*/)
    {
        return mRealValue;
    }

    const std::string& RealOperand::getStringValue(const Context& /*cxt*/, const json& /*variables*/)
    {
        throw std::logic_error("RealOperand::getStringValue not supported");
    }

    //=======================StringOperand===========================
    StringOperand::StringOperand(const std::string& v)
    :Operand(Operand::String)
    ,mValue(v)
    {}

    bool StringOperand::canConvert2(type t, const Context& cxt, const json& variables)
    {
        if(Operand::Bool == t)
        {
            return isBool(mValue, 0, mValue.length());
        }
        else if(Operand::Integer == t)
        {
            return isInt(mValue, 0, mValue.length());
        }
        else if(Operand::Real == t)
        {
            return isReal(mValue, 0, mValue.length());
        }

        return false;
    }

    bool StringOperand::getBoolValue(const Context& cxt, const json& variables)
    {
        return convert2Bool(mValue, 0, mValue.length());
    }

    int StringOperand::getIntValue(const Context& cxt, const json& variables)
    {
        return convert2Bool(mValue, 0, mValue.length());
    }

    double StringOperand::getRealValue(const Context& cxt, const json& variables)
    {
        return convert2Real(mValue, 0, mValue.length());
    }

    const std::string& StringOperand::getStringValue(const Context& cxt, const json& variables)
    {
        return mValue;
    }

    //=======================JsonOperand===========================
    bool JsonOperand::canConvert2(type t, const Context& cxt, const json& variables)
    {
        return false;
    }

    JsonOperand::JsonOperand(const json& v)
        :Operand(Operand::Json)
        ,mValue(v)
    {}

    bool JsonOperand::getBoolValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("JsonOperand::getBoolValue not supported");
    }

    int JsonOperand::getIntValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("JsonOperand::getIntValue not supported");
    }

    double JsonOperand::getRealValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("JsonOperand::getRealValue not supported");
    }

    const std::string& JsonOperand::getStringValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("JsonOperand::getStringValue not supported");
    }

    const json& JsonOperand::getJsonValue(const Context& cxt, const json& variables)
    {
        return mValue;
    }
    //=======================LocationOperand===========================
    LocationOperand::LocationOperand(const std::shared_ptr<Expression>& p)
    :Operand(Operand::Location)
    ,mLocation(p)
    ,mCurrentContext(0)
    {}

    void LocationOperand::makeSure(const Context& cxt, const json& variables) const
    {
        if(cxt.getId() != mCurrentContext)
        {
            mCurrentContext = cxt.getId();

            auto tmpInput = mLocation->isAbsolute() ? cxt.getRootInput() : cxt.getInput();
            Context tmpCxt(tmpInput, cxt.getRootInput());
            mLocation->apply(tmpCxt, variables);
            auto result = tmpCxt.getOutput();

            if(result->is_boolean())
            {
                mResult = std::make_shared<BoolOperand>(result->get<bool>());
            }
            else if(result->is_number_integer())
            {
                mResult = std::make_shared<IntOperand>(result->get<int>());
            }
            else if(result->is_number_float())
            {
                mResult = std::make_shared<RealOperand>(result->get<double>());
            }
            else if(result->is_string())
            {
                mResult = std::make_shared<StringOperand>(result->get<std::string>());
            }
            else if(!result->is_null())
            {
                mResult = std::make_shared<JsonOperand>(*result);
            }
            else
            {
                mResult.reset();
            }
        }
    }

    Operand::type LocationOperand::getType(const Context& cxt, const json& variables) const
    {
        makeSure(cxt, variables);
        if(nullptr == mResult)
        {
            return Operand::Unknown;
        }
        return mResult->getType(cxt, variables);
    }

    bool LocationOperand::canConvert2(type t, const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->canConvert2(t, cxt, variables);
    }

    bool LocationOperand::getBoolValue(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->getBoolValue(cxt, variables);
    }

    int LocationOperand::getIntValue(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->getIntValue(cxt, variables);
    }

    double LocationOperand::getRealValue(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->getRealValue(cxt, variables);
    }

    const std::string& LocationOperand::getStringValue(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->getStringValue(cxt, variables);
    }

    const json& LocationOperand::getJsonValue(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->getJsonValue(cxt, variables);
    }

    bool LocationOperand::eval(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return nullptr != mResult;
    }
    //=======================PredicateOperand===========================
    PredicateOperand::PredicateOperand(std::shared_ptr<Predicate> pChild)
    :Operand(Operand::Bool)
    ,mChild(pChild)
    {
    }

    bool PredicateOperand::canConvert2(type t, const Context& cxt, const json& variables)
    {
         return Operand::Integer == t || Operand::Real == t;
    }

    bool PredicateOperand::getBoolValue(const Context& cxt, const json& variables)
    {
        return mChild->eval(cxt, variables);
    }

    int PredicateOperand::getIntValue(const Context& cxt, const json& variables)
    {
        return getBoolValue(cxt, variables);
    }

    double PredicateOperand::getRealValue(const Context& cxt, const json& variables)
    {
        return getBoolValue(cxt, variables);
    }

    const std::string& PredicateOperand::getStringValue(const Context& /*cxt*/, const json& /*variables*/)
    {
        throw std::logic_error("PredicateOperand::getStringValue not supported");
    }

    //=======================RegexOperand===========================
    RegexOperand::RegexOperand(const std::string& regex)
    :Operand(Operand::Regex)
    ,mRegex(regex)
    {
    }

    bool RegexOperand::getBoolValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("RegexOperand::getBoolValue not supported");
    }

    int RegexOperand::getIntValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("RegexOperand::getIntValue not supported");
    }

    double RegexOperand::getRealValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("RegexOperand::getRealValue not supported");
    }

    const std::string& RegexOperand::getStringValue(const Context& cxt, const json& variables)
    {
        return mRegex;
    }

    //=======================VariableOperand===========================
    VariableOperand::VariableOperand(const std::string& variableName)
    :Operand(Operand::Variable)
    ,mVariableName(variableName)
    ,mCurrentContext(0)
    {}

    void VariableOperand::makeSure(const Context& cxt, const json& variables) const
    {
        if(cxt.getId() != mCurrentContext)
        {
            mCurrentContext = cxt.getId();

            auto result = variables[mVariableName];
            if(result.is_boolean())
            {
                mResult = std::make_shared<BoolOperand>(result.get<bool>());
            }
            else if(result.is_number_integer())
            {
                mResult = std::make_shared<IntOperand>(result.get<int>());
            }
            else if(result.is_number_float())
            {
                mResult = std::make_shared<RealOperand>(result.get<double>());
            }
            else if(result.is_string())
            {
                mResult = std::make_shared<StringOperand>(result.get<std::string>());
            }
            else if(!result.is_null())
            {
                mResult = std::make_shared<JsonOperand>(result);
            }
            else
            {
                mResult.reset();
            }
        }
    }

    Operand::type VariableOperand::getType(const Context& cxt, const json& variables) const
    {
        makeSure(cxt, variables);
        if(nullptr == mResult)
        {
            return Operand::Unknown;
        }
        return mResult->getType(cxt, variables);
    }

    bool VariableOperand::canConvert2(type t, const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->canConvert2(t, cxt, variables);
    }

    bool VariableOperand::getBoolValue(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->getBoolValue(cxt, variables);
    }

    int VariableOperand::getIntValue(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->getIntValue(cxt, variables);
    }

    double VariableOperand::getRealValue(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->getRealValue(cxt, variables);
    }

    const std::string& VariableOperand::getStringValue(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->getStringValue(cxt, variables);
    }

    const json& VariableOperand::getJsonValue(const Context& cxt, const json& variables)
    {
        makeSure(cxt, variables);
        return mResult->getJsonValue(cxt, variables);
    }

    //=======================MinusOperand===========================
    MinusOperand::MinusOperand(const std::shared_ptr<Operand>& child)
    :Operand(Operand::Composite)
    ,mChild(child)
    {}

    Operand::type MinusOperand::getType(const Context& cxt, const json& variables) const
    {
        return mChild->getType(cxt, variables);
    }

    bool MinusOperand::canConvert2(type t, const Context& cxt, const json& variables)
    {
        return mChild->canConvert2(t, cxt, variables);
    }

    bool MinusOperand::getBoolValue(const Context& cxt, const json& variables)
    {
        return mChild->getBoolValue(cxt, variables);
    }

    int MinusOperand::getIntValue(const Context& cxt, const json& variables)
    {
        return -mChild->getIntValue(cxt, variables);
    }

    double MinusOperand::getRealValue(const Context& cxt, const json& variables)
    {
        return -mChild->getRealValue(cxt, variables);
    }

    const std::string& MinusOperand::getStringValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("MinusOperand::getStringValue not supported");
    }

    const json& MinusOperand::getJsonValue(const Context& cxt, const json& variables)
    {
        throw std::logic_error("MinusOperand::getJsonValue not supported");
    }
}
