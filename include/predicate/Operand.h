#ifndef _JSPATH_OPERAND_H
#define _JSPATH_OPERAND_H
#include "json.hpp"
#include "Predicate.h"
namespace jspath
{
using nlohmann::json;
class Operand: public Predicate
{
public:
    enum type
    {
	Bool,
	Integer,
        Real,
        String,
        Array,
        Location,
        Other
    };

    Operand(type t);
    virtual ~Operand();

    virtual bool canConvert2(type t, const Context& cxt, const json& input) { return false; }
    virtual bool getBoolValue(const Context& cxt, const json& input) = 0;
    virtual int getIntValue(const Context& cxt, const json& input) = 0;
    virtual double getRealValue(const Context& cxt, const json& input) = 0;
    virtual const std::string& getStringValue(const Context& cxt, const json& input) = 0;

    virtual type getType(const Context& /*cxt*/, const json& /*input*/) const { return mType; }
    virtual bool IsDynamic() const { return false; }

    bool eval(const Context& cxt, const json& input) override;
private:
    type mType;
};

class BoolOperand: public Operand
{
public:
    BoolOperand(const std::string& v);

    bool getBoolValue(const Context& cxt, const json& input) override;
    int getIntValue(const Context& cxt, const json& input) override;
    double getRealValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;
private:
    std::string mRepresentation;
    bool mBoolValue;
};

class IntOperand: public Operand
{
public:
    IntOperand(const std::string& v);

    bool getBoolValue(const Context& cxt, const json& input) override;
    int getIntValue(const Context& cxt, const json& input) override;
    double getRealValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;

private:
    std::string mRepresentation;
    int mIntValue;
};

class RealOperand: public Operand
{
public:
    RealOperand(const std::string& v); 

    bool getBoolValue(const Context& cxt, const json& input) override;
    int getIntValue(const Context& cxt, const json& input) override;
    double getRealValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;

private:
    std::string mRepresentation;
    double mRealValue;
};

class StringOperand: public Operand
{
public:
    StringOperand(const std::string& v);

    bool getBoolValue(const Context& cxt, const json& input) override;
    int getIntValue(const Context& cxt, const json& input) override;
    double getRealValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;

private:
    std::string mValue;
};

class ArrayOperand: public Operand
{
public:
    ArrayOperand(const std::string& v);

    bool getBoolValue(const Context& cxt, const json& input) override;
    int getIntValue(const Context& cxt, const json& input) override;
    double getRealValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;
};

class LocationPath;
class LocationOperand: public Operand
{
public:
    LocationOperand(std::shared_ptr<LocationPath> v);
    bool IsDynamic() const override { return true; }

    bool getBoolValue(const Context& cxt, const json& input) override;
    int getIntValue(const Context& cxt, const json& input) override;
    double getRealValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;

private:
    std::shared_ptr<LocationPath> mLocation;
};


}
#endif

