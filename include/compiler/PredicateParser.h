#ifndef _JSPATH_PREDICATE_PARSER_H
#define _JSPATH_PREDICATE_PARSER_H
#include "compiler/JSPathCompiler.h"
#include "predicate/BinaryOperator.hpp"
namespace jspath
{

struct OpInfo
{
    enum Precedence
    {
       Highest = 0x0020,
       Second = 0x0040,
       Third = 0x0080,
       Fourth = 0x0100,
       Fifth = 0x0200,
       Sixth = 0x0400,
       Lowest = 0x0800
    };

    enum type
    {
        //========================================comparison operators======================================
        Equal = Fifth, // == Returns is true if both operands are equal, eg .id == "1"
        StrictlyEqual = Fifth + 1, // === Returns true if both operands are strictly equal with no type conversion, eg .id === 1
        NonEqual = Fifth + 2, // != Returns true if the operands are not equal, eg .id != "1"
        StrictlyNonEqual = Fifth + 3, // !== Returns true if the operands are not equal and/or not of the same type, eg .id !== 1
        GreatThan = Fourth, // > Returns true if the left operand is greater than the right operand, eg .id > 1
        GreatEqual = Fourth + 1, // >= Returns true if the left operand is greater than or equal to the right operand, eg .id >= 1
        LessThan = Fourth + 2, // < Returns true if the left operand is less than the right operand, eg .id < 1
        LessEqual = Fourth + 3, // <= Returns true if the left operand is less than or equal to the right operand, eg .id <= 1

        //=========================================string comparison operators=================================
        StartsWith = Fifth + 4, // ^== Returns true if left operand value beginning with right operand value, eg .title ^== "Javascript"
        iStartsWith = Fifth + 5, // ^= Like the '^==' but case insensitive, eg  .title ^= "javascript"
        EndsWith = Fifth + 6, // $== Returns true if left operand value ending with right operand value, eg .title $== "Javascript"
        iEndsWith = Fifth + 7, // $= Like the '$==' but case insensitive, eg .title $= "javascript"
        Contains = Fifth + 8, // *== Returns true if left operand value contains right operand value, eg .title *== "Javascript"
        iContains = Fifth + 9, // *= Like the '*==' but case insensitive, eg .title *= "javascript"
        Match = Second + 3, // ~== /regex/ Returns true if left operand value math regex, eg .title ~== /Java(\w+)/
        iMatch = Second + 4, // ~= /regex/ Like the '~==' bug case insensitive, eg .title ~= /java(\w+)/
        NotMatch = Second + 5, // ~!= /regex/
        iNotMatch = Second + 6, // ~! /regex/

        //============================================logic operators===========================================
        And = Sixth, // && Returns true if both operands are true, eg .price > 19 && .author.name === "Robert C. Martin"
        Or = Lowest, // || Returns true if either operand is true, eg .title === "Maintainable JavaScript" || .title === "Clean Code"
        Not = Highest, // ! Returns true if operand is false, eg !.title

        //=============================================arithmetic operators===================================
        Add = Third, // +
        Sub = Third + 1, // -
        Mul = Second, // *
        Div = Second + 1, // /
        Mod = Second + 2, // %
        Minus = Highest + 1// -
    };

    const type op;
    const size_t from,to; //position in fullExpression[from,to)
    const size_t index; //index in mOperators which declared in PredicateParser

    bool isUnary() const { return op == Not; }
    friend bool operator< (const OpInfo& lhs, const OpInfo& rhs);
};

class Predicate;
class Operand;
struct PredicateParser: public SubExpressionParser
{
public:
    PredicateParser(bool rootParser = true);

    void onEntry() override;
    void parse(const std::string& fullExpression, size_t& fromPos, size_t endPos) override;
    std::shared_ptr<Expression> onExit() override;

    type getCode() const override { return PredicateExp; }

private:
    std::shared_ptr<Predicate> getResult() { return mResult; }
    std::shared_ptr<Predicate> createPredicate(const std::string& fullExpression, size_t idxOpFrom, size_t idxOpTo, size_t from, size_t to);
    std::shared_ptr<Operand> createOperand(const std::string& fullExpression, size_t idxOpFrom, size_t idxOpTo, size_t from, size_t to);
    std::shared_ptr<Operand> createPrimitive(const std::string& fullExpression, size_t from, size_t to);

    void parseEqual(const std::string& fullExpression, size_t& fromPos);
    void parseGreat(const std::string& fullExpression, size_t& fromPos);
    void parseLess(const std::string& fullExpression, size_t& fromPos);
    void parseNonEqual(const std::string& fullExpression, size_t& fromPos);
    void parseStartsWith(const std::string& fullExpression, size_t& fromPos);
    void parseEndsWith(const std::string& fullExpression, size_t& fromPos);
    void parseContains(const std::string& fullExpression, size_t& fromPos);
    void parseMatch(const std::string& fullExpression, size_t& fromPos);
    void parseAnd(const std::string& fullExpression, size_t& fromPos);
    void parseOr(const std::string& fullExpression, size_t& fromPos);
    void parseSub(const std::string& fullExpression, size_t& fromPos);

    std::shared_ptr<BinaryOperator<Operand, Operand>> createArthemeticOp(const OpInfo& opInfo);
    std::shared_ptr<BinaryOperator<Operand, Predicate>> createCompOp(const OpInfo& opInfo);
    std::shared_ptr<BinaryOperator<Predicate, Predicate>> createLogicOp(const OpInfo& opInfo);
    std::shared_ptr<Predicate> createUnary(const OpInfo& opInfo, const std::shared_ptr<Predicate>& pChild);

    bool mRootParser;
    std::vector<OpInfo> mOperators;
    std::shared_ptr<Predicate> mResult;
};
}
#endif
