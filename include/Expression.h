#ifndef _JSPATH_EXPRESSION_H
#define _JSPATH_EXPRESSION_H
#include <memory>
#include <boost/property_tree/ptree.hpp>
namespace jspath
{
    using boost::property_tree::ptree;
    class Context;
    class Expression
    {
    public:
        virtual ~Expression() {}
        void apply(Context& cxt);

        void setSuccessor(std::shared_ptr<Expression> pSuccessor);

    protected:
        virtual void doApply(Context& cxt, const ptree& input) = 0;

        std::shared_ptr<Expression> mSuccessor;
    };
}
#endif

