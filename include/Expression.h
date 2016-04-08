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
    Expression(bool isAbsolute = false);

    virtual ~Expression() {}
    virtual void apply(Context& cxt);

    void setSuccessor(std::shared_ptr<Expression> pSuccessor);
    std::shared_ptr<Expression> getSuccessor() { return mSuccessor; }
    bool isAbsolute() const { return mIsAbsolute; }
    void setAbsolute(bool isAbsolute = true) { mIsAbsolute = isAbsolute; }
protected:
    virtual void doApply(Context& cxt) = 0;

    std::shared_ptr<Expression> mSuccessor;
    bool mIsAbsolute;
};
}
#endif
