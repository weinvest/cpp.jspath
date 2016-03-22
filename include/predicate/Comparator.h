#ifndef _JSPATH_COMPARATOR_H
#define _JSPATH_COMPARATOR_H

#include "predicate/Operand.h"
namespace jspath
{
class Equal: public Predicate
{
public:
    Equal(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);

    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class StrictlyEqual: public Predicate
{
public:
    StrictlyEqual(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);

    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;

};

class NonEqual: public Predicate
{
public:
    NonEqual(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);

    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class StrictlyNonEqual: public Predicate
{
public:
    StrictlyNonEqual(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);

    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class GreatThan: public Predicate
{
public:
    GreatThan(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);

    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class GreatEqual: public Predicate
{
public:
    GreatEqual(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);

    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class LessThan: public Predicate
{
public:
    LessThan(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);

    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};

class LessEqual: public Predicate
{
public:
    LessEqual(std::shared_ptr<Operand> pOperand1 , std::shared_ptr<Operand> pOperand2);

    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Operand> mOperand1;
    std::shared_ptr<Operand> mOperand2;
};
}
#endif
