#ifndef _JSPATH_EXPRESSION_H
#define _JSPATH_EXPRESSION_H
#include <memory>
#include "json.hpp"
namespace jspath
{
    using nlohmann::json;
    class Context;
    class Expression
    {
    public:
        virtual ~Expression() {}
        virtual void apply(Context& cxt);

        void setSuccessor(std::shared_ptr<Expression> pSuccessor);
        std::shared_ptr<Expression> getSuccessor() { return mSuccessor; }
    protected:
        virtual void doApply(Context& cxt, const json& input) = 0;

        std::shared_ptr<Expression> mSuccessor;
    };
}
#endif

