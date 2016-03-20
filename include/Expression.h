#ifndef _JSPATH_EXPRESSION_H
#define _JSPATH_EXPRESSION_H
#include <memory>
namespace jspath
{
    class Context;
    class Expression
    {
    public:
        virtual ~Expression() {}
        void apply(Context& cxt);

        void setSuccessor(std::shared_ptr<Expression> pSuccessor);

    protected:
        void doApply(Context& cxt);

        std::shared_ptr<Expression> mSuccessor;
    };
}
#endif

