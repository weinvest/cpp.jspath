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

    bool Operand::eval(const Context& cxt, const json& input)
    {
        return getBoolValue(cxt, input);
    }

    const json& Operand::getJsonValue(const Context& cxt, const json& input)
    {
        throw std::logic_error("no json value availabe");
    }

    //=======================BoolOperand===========================
    BoolOperand::BoolOperand(bool v)
    :Operand(Operand::Bool)
    ,mBoolValue(v)
    {
    }

    bool BoolOperand::canConvert2(type t, const Context& cxt, const json& input)
    {
         return Operand::Integer == t || Operand::Real == t;
    }

    bool BoolOperand::getBoolValue(const Context& cxt, const json& input)
    {
        return mBoolValue;
    }

    int BoolOperand::getIntValue(const Context& /*cxt*/, const json& /*input*/)
    {
        return mBoolValue;
    }

    double BoolOperand::getRealValue(const Context& /*cxt*/, const json& /*input*/)
    {
        return mBoolValue;
    }

    const std::string& BoolOperand::getStringValue(const Context& /*cxt*/, const json& /*input*/)
    {
        throw std::logic_error("BoolOperand::getStringValue not supported");
    }

    //=======================IntOperand===========================
    IntOperand::IntOperand(int v)
    :Operand(Operand::Integer)
    ,mIntValue(v)
    {}

    bool IntOperand::canConvert2(type t, const Context& cxt, const json& input)
    {
        return Operand::Bool == t || Operand::Real == t;
    }

    bool IntOperand::getBoolValue(const Context& cxt, const json& input)
    {
        return 0 != mIntValue;
    }

    int IntOperand::getIntValue(const Context& /*cxt*/, const json& /*input*/)
    {
        return mIntValue;
    }

    double IntOperand::getRealValue(const Context& /*cxt*/, const json& /*input*/)
    {
        return mIntValue;
    }

    const std::string& IntOperand::getStringValue(const Context& /*cxt*/, const json& /*input*/)
    {
        throw std::logic_error("IntOperand::getStringValue not supported");
    }

    //=======================RealOperand===========================
    RealOperand::RealOperand(double v)
    :Operand(Operand::Real)
    ,mRealValue(v)
    {}

    bool RealOperand::canConvert2(type t, const Context& cxt, const json& input)
    {
        return Operand::Bool == t || Operand::Integer == t;
    }

    bool RealOperand::getBoolValue(const Context& cxt, const json& input)
    {
        return std::abs(mRealValue) < 1e-8;
    }

    int RealOperand::getIntValue(const Context& /*cxt*/, const json& /*input*/)
    {
        return mRealValue;
    }

    double RealOperand::getRealValue(const Context& /*cxt*/, const json& /*input*/)
    {
        return mRealValue;
    }

    const std::string& RealOperand::getStringValue(const Context& /*cxt*/, const json& /*input*/)
    {
        throw std::logic_error("RealOperand::getStringValue not supported");
    }

    //=======================StringOperand===========================
    StringOperand::StringOperand(const std::string& v)
    :Operand(Operand::String)
    ,mValue(v)
    {}

    bool StringOperand::canConvert2(type t, const Context& cxt, const json& input)
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

    bool StringOperand::getBoolValue(const Context& cxt, const json& input)
    {
        return convert2Bool(mValue, 0, mValue.length());
    }

    int StringOperand::getIntValue(const Context& cxt, const json& input)
    {
        return convert2Bool(mValue, 0, mValue.length());
    }

    double StringOperand::getRealValue(const Context& cxt, const json& input)
    {
        return convert2Real(mValue, 0, mValue.length());
    }

    const std::string& StringOperand::getStringValue(const Context& cxt, const json& input)
    {
        return mValue;
    }

    //=======================JsonOperand===========================
    bool JsonOperand::canConvert2(type t, const Context& cxt, const json& input)
    {
        return false;
    }

    JsonOperand::JsonOperand(const json& v)
        :Operand(Operand::Json)
        ,mValue(v)
    {}

    bool JsonOperand::getBoolValue(const Context& cxt, const json& input)
    {
        throw std::logic_error("JsonOperand::getBoolValue not supported");
    }

    int JsonOperand::getIntValue(const Context& cxt, const json& input)
    {
        throw std::logic_error("JsonOperand::getIntValue not supported");
    }

    double JsonOperand::getRealValue(const Context& cxt, const json& input)
    {
        throw std::logic_error("JsonOperand::getRealValue not supported");
    }

    const std::string& JsonOperand::getStringValue(const Context& cxt, const json& input)
    {
        throw std::logic_error("JsonOperand::getStringValue not supported");
    }

    const json& JsonOperand::getJsonValue(const Context& cxt, const json& input)
    {
        return mValue;
    }
    //=======================LocationOperand===========================
    LocationOperand::LocationOperand(const std::shared_ptr<Expression>& p)
    :Operand(Operand::Location)
    ,mLocation(p)
    ,mCurrentInput(nullptr)
    {}

    void LocationOperand::makeSure(const Context& cxt, const json& input) const
    {
        if(input != mCurrentInput)
        {
            mCurrentInput = &input;

            auto input = mLocation->isAbsolute() ? cxt.getRootInput() : cxt.getInput();
            Context tmpCxt(input, cxt.getRootInput());
            mLocation->apply(tmpCxt);
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

    Operand::type LocationOperand::getType(const Context& cxt, const json& input) const
    {
        makeSure(cxt, input);
        if(nullptr == mResult)
        {
            return Operand::Unknown;
        }
        return mResult->getType(cxt, input);
    }

    bool LocationOperand::canConvert2(type t, const Context& cxt, const json& input)
    {
        makeSure(cxt, input);
        return mResult->canConvert2(t, cxt, input);
    }

    bool LocationOperand::getBoolValue(const Context& cxt, const json& input)
    {
        makeSure(cxt, input);
        return mResult->getBoolValue(cxt, input);
    }

    int LocationOperand::getIntValue(const Context& cxt, const json& input)
    {
        makeSure(cxt, input);
        return mResult->getIntValue(cxt, input);
    }

    double LocationOperand::getRealValue(const Context& cxt, const json& input)
    {
        makeSure(cxt, input);
        return mResult->getRealValue(cxt, input);
    }

    const std::string& LocationOperand::getStringValue(const Context& cxt, const json& input)
    {
        makeSure(cxt, input);
        return mResult->getStringValue(cxt, input);
    }

    const json& LocationOperand::getJsonValue(const Context& cxt, const json& input)
    {
        makeSure(cxt, input);
        return mResult->getJsonValue(cxt, input);
    }

    //=======================PredicateOperand===========================
    PredicateOperand::PredicateOperand(std::shared_ptr<Predicate> pChild)
    :Operand(Operand::Real)
    ,mChild(pChild)
    {
    }

    bool PredicateOperand::canConvert2(type t, const Context& cxt, const json& input)
    {
         return Operand::Integer == t || Operand::Real == t;
    }

    bool PredicateOperand::getBoolValue(const Context& cxt, const json& input)
    {
        return mChild->eval(cxt, input);
    }

    int PredicateOperand::getIntValue(const Context& cxt, const json& input)
    {
        return getBoolValue(cxt, input);
    }

    double PredicateOperand::getRealValue(const Context& cxt, const json& input)
    {
        return getBoolValue(cxt, input);
    }

    const std::string& PredicateOperand::getStringValue(const Context& /*cxt*/, const json& /*input*/)
    {
        throw std::logic_error("PredicateOperand::getStringValue not supported");
    }

    //=======================RegexOperand===========================
    RegexOperand::RegexOperand(const std::string& regex)
    :Operand(Operand::Regex)
    ,mRegex(regex)
    {
    }

    bool RegexOperand::getBoolValue(const Context& cxt, const json& input)
    {
        throw std::logic_error("RegexOperand::getBoolValue not supported");
    }

    int RegexOperand::getIntValue(const Context& cxt, const json& input)
    {
        throw std::logic_error("RegexOperand::getIntValue not supported");
    }

    double RegexOperand::getRealValue(const Context& cxt, const json& input)
    {
        throw std::logic_error("RegexOperand::getRealValue not supported");
    }

    const std::string& RegexOperand::getStringValue(const Context& cxt, const json& input)
    {
        return mRegex;
    }

}
