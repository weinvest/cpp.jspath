#ifndef JSPATH_BINARY_OPERATOR_H
#define JSPATH_BINARY_OPERATOR_H

namespace jspath
{
    template<typename OP, typename Base>
    class BinaryOperator:public Base
    {
    public:
        BinaryOperator(std::shared_ptr<OP> op1, std::shared_ptr<OP> op2)
            :mOperand1(op1)
            ,mOperand2(op2)
        {}

    protected:
        std::shared_ptr<OP> mOperand1;
        std::shared_ptr<OP> mOperand2;
    };
}
#endif

