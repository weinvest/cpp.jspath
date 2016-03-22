#ifndef _JSPATH_STRING_OPERATOR_H
#define _JSPATH_STRING_OPERATOR_H
#include "predicate/Predicate.h"
#include "predicate/Operand.h"
namespace jspath
{

class SensitiveEqual: public Predicate
{
public:
    SensitiveEqual(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);
    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class InsensitiveEqual: public Predicate
{
public:
    InsensitiveEqual(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);
    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class StartsWith: public Predicate
{
public:
    StartsWith(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);
    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class InsensitiveStartsWith: public Predicate
{
public:
    InsensitiveStartsWith(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);
    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class EndsWith: public Predicate
{
public:
    EndsWith(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);
    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class InsensitiveEndsWith: public Predicate
{
public:
    InsensitiveEndsWith(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);
    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class Contains: public Predicate
{
public:
    Contains(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);
    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class InsensitiveContains: public Predicate
{
public:
    InsensitiveContains(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);
    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};
}
#endif

