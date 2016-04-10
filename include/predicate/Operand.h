#ifndef _JSPATH_OPERAND_H
#define _JSPATH_OPERAND_H
#include "json.hpp"
#include "Predicate.h"
#include "Enum.h"
namespace jspath
{
using nlohmann::json;
class Operand: public Predicate
{
public:
    #define OPERAND_TYPES  ((Bool,0))((Integer,1))((Real,2))((String,3))\
                           ((Json,4))((Regex,5))((Location,6))((Composite,7))\
                           ((Variable,8))((Unknown,9))

    enum type
    {
        JSENUM_VALUE(OPERAND_TYPES)
    };

    static const std::string& toString(type t);
    static bool parse(const std::string& value, type& v);

    Operand():Operand(Composite){}

    Operand(type t);
    virtual ~Operand();

    virtual bool canConvert2(type t, const Context& cxt, const json& variables) { return false; }
    virtual bool getBoolValue(const Context& cxt, const json& variables) = 0;
    virtual int getIntValue(const Context& cxt, const json& variables) = 0;
    virtual double getRealValue(const Context& cxt, const json& variables) = 0;
    virtual const std::string& getStringValue(const Context& cxt, const json& variables) = 0;
    virtual const json& getJsonValue(const Context& cxt, const json& variables);

    virtual type getType(const Context& /*cxt*/, const json& /*input*/) const { return mType; }
    bool IsDynamic() const { return mType < Location; }

    bool eval(const Context& cxt, const json& variables) override;
private:
    type mType;
};

class BoolOperand: public Operand
{
public:
    BoolOperand(bool v);

    bool canConvert2(type t, const Context& cxt, const json& variables) override;
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;

private:
    bool mBoolValue;
};

class IntOperand: public Operand
{
public:
    IntOperand(int v);

    bool canConvert2(type t, const Context& cxt, const json& variables) override;
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;

private:
    int mIntValue;
};

class RealOperand: public Operand
{
public:
    RealOperand(double v);

    bool canConvert2(type t, const Context& cxt, const json& variables) override;
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;

private:
    double mRealValue;
};

class StringOperand: public Operand
{
public:
    StringOperand(const std::string& v);

    bool canConvert2(type t, const Context& cxt, const json& variables) override;
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;

private:
    std::string mValue;
};

class JsonOperand: public Operand
{
public:
    JsonOperand(const json& v);

    bool canConvert2(type t, const Context& cxt, const json& variables) override;
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;
    const json& getJsonValue(const Context& cxt, const json& variables) override;
private:
    json mValue;
};

class Expression;
class LocationOperand: public Operand
{
public:
    LocationOperand(const std::shared_ptr<Expression>& v);

    bool canConvert2(type t, const Context& cxt, const json& variables) override;
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;
    type getType(const Context& /*cxt*/, const json& /*input*/) const override;
    const json& getJsonValue(const Context& cxt, const json& variables) override;

    bool eval(const Context& cxt, const json& variables) override;
private:
    void makeSure(const Context& cxt, const json& variables) const;

    std::shared_ptr<Expression> mLocation;
    mutable std::shared_ptr<Operand> mResult; //TODO thread safe
    mutable uint32_t mCurrentContext; //TODO: thread safe
};

class PredicateOperand: public Operand
{
public:
    PredicateOperand(std::shared_ptr<Predicate> pChild);

    bool canConvert2(type t, const Context& cxt, const json& variables) override;
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;

private:
    std::shared_ptr<Predicate> mChild;
};

class RegexOperand: public Operand
{
public:
    RegexOperand(const std::string& regex);
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;

private:
    std::string mRegex;
};

class VariableOperand: public Operand
{
public:
    VariableOperand(const std::string& variableName);

    bool canConvert2(type t, const Context& cxt, const json& variables) override;
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;
    type getType(const Context& /*cxt*/, const json& /*input*/) const override;
    const json& getJsonValue(const Context& cxt, const json& variables) override;
private:
    void makeSure(const Context& cxt, const json& variables) const;

    std::string mVariableName;
    mutable std::shared_ptr<Operand> mResult; //TODO thread safe
    mutable uint32_t mCurrentContext; //TODO: thread safe
};

class MinusOperand: public Operand
{
public:
    MinusOperand(const std::shared_ptr<Operand>& child);

    bool canConvert2(type t, const Context& cxt, const json& variables) override;
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;
    type getType(const Context& /*cxt*/, const json& /*input*/) const override;
    const json& getJsonValue(const Context& cxt, const json& variables) override;
private:
    std::shared_ptr<Operand> mChild;
};
}
#endif
