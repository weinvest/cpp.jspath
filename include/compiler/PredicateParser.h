#ifndef _JSPATH_PREDICATE_PARSER_H
#define _JSPATH_PREDICATE_PARSER_H
#include "compiler/JSPathCompiler.h"

namespace jspath
{

struct OpInfo
{
    enum Precedence
    {
       Highest = 0x00000001,
       Second = 0x00000010,
       Third = 0x00000100,
       Fourth = 0x00001000,
       Fifth = 0x00010000,
       Sixth = 0x00100000,
       Lowest = 0x01000000
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

    friend bool operator< (const OpInfo& lhs, const OpInfo& rhs);
};

struct PredicateParser: public SubExpressionParser
{
public:
    void onEntry() override;
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override;
    std::shared_ptr<Expression> onExit() override;

    type getCode() const override { return PredicateExp; }
private:
    std::vector<OpInfo> mOperators;
    std::shared_ptr<Expression> mResult;
};
}
#endif
