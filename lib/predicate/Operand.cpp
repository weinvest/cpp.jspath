#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "predicate/Operand.h"

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

    //=======================BoolOperand===========================
    BoolOperand::BoolOperand(const std::string& v)
    :Operand(Operand::Real)
    ,mRepresentation(v)
    {
        bool success = true;
        if(1 == v.length())
        {
            if('1' == v[0])
            {
                mBoolValue = true;
            }
            else if('0' == v[0])
            {
                mBoolValue = false;
            }
            else
            {
                success = false;
            }
        }
        else if(4 == v.length())
        {
            if(boost::algorithm::iequals(v, "true"))
            {
                mBoolValue = true;
            }
            else if(boost::algorithm::iequals(v, "false"))
            {
                mBoolValue = false;
            }
            else
            {
                success = false;
            }
        }

        if(!success)
        {
            throw std::logic_error(std::string("bad lexical cast: ") + v + " could not be interpreted as bool");
        }
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
        return mRepresentation;
    }

    //=======================IntOperand===========================
    IntOperand::IntOperand(const std::string& v)
    :Operand(Operand::Integer)
    ,mIntValue(boost::lexical_cast<double>(v))
    ,mRepresentation(v)
    {}

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
        return mRepresentation;
    }

    //=======================RealOperand===========================
    RealOperand::RealOperand(const std::string& v)
    :Operand(Operand::Real)
    ,mRealValue(boost::lexical_cast<double>(v))
    ,mRepresentation(v)
    {}

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
        return mRepresentation;
    }

    //=======================StringOperand===========================
    StringOperand::StringOperand(const std::string& v)
    :Operand(Operand::String)
    ,mValue(v)
    {}

    bool StringOperand::getBoolValue(const Context& cxt, const json& input)
    {
        return false;
    }

    int StringOperand::getIntValue(const Context& cxt, const json& input)
    {
        return 0;
    }

    double StringOperand::getRealValue(const Context& cxt, const json& input)
    {
        return 0;
    }

    const std::string& StringOperand::getStringValue(const Context& cxt, const json& input)
    {
        return mValue;
    }

    //=======================ArrayOperand===========================
    ArrayOperand::ArrayOperand(const std::string& v)
    :Operand(Operand::Array)
    {}

    bool ArrayOperand::getBoolValue(const Context& cxt, const json& input)
    {
        return false;
    }

    int ArrayOperand::getIntValue(const Context& cxt, const json& input)
    {
        return 0;
    }

    double ArrayOperand::getRealValue(const Context& cxt, const json& input)
    {
        return 0;
    }

    const std::string& ArrayOperand::getStringValue(const Context& cxt, const json& input)
    {
        return "";
        //return mValue;
    }


    //=======================LocationOperand===========================
    LocationOperand::LocationOperand(const std::shared_ptr<LocationPath> p)
    :Operand(Operand::Location)
    ,mLocation(p)
    {}

    bool LocationOperand::getBoolValue(const Context& cxt, const json& input)
    {
        return false;
    }

    int LocationOperand::getIntValue(const Context& cxt, const json& input)
    {
        return 0;
    }

    double LocationOperand::getRealValue(const Context& cxt, const json& input)
    {
        return 0;
    }

    const std::string& LocationOperand::getStringValue(const Context& cxt, const json& input)
    {
        return "";
        //return mValue;
    }


}
