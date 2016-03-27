#include "JSPath.h"
#include "Context.h"
#include "Expression.h"
#include "compiler/JSPathCompiler.h"
namespace jspath
{
std::shared_ptr<Expression> compile(const std::string& applyExpr)
{
    Compiler compiler;
    return compiler.compile(applyExpr);
}

ptree apply(const ptree& root, std::shared_ptr<Expression> pExpression)
{
    ptree outRoot;
    apply(outRoot, root, pExpression);
    return outRoot;
}

void apply(ptree& outRoot, const ptree& root, std::shared_ptr<Expression> pExpression)
{
    Context cxt(root);
    pExpression->apply(cxt);

    for(auto pResultNode : cxt.getOutput())
    {
        outRoot.put_child("", *pResultNode);
    }
}
}
