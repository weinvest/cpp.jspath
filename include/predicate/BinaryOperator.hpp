#ifndef JSPATH_BINARY_OPERATOR_H
#define JSPATH_BINARY_OPERATOR_H

namespace jspath
{
    template<typename OP, typename Base>
    class BinaryOperator:public Base
    {
    public:
        using Base::Base;
        BinaryOperator(){}

        void setLeft(const std::shared_ptr<OP>& pLeft) { mOperand1 = pLeft; }
        void setRight(const std::shared_ptr<OP>& pRight) { mOperand2 = pRight; }
    protected:
        std::shared_ptr<OP> mOperand1;
        std::shared_ptr<OP> mOperand2;
    };
}
#endif
