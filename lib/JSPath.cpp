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

json apply(const json& root, std::shared_ptr<Expression> pExpression)
{
    json outRoot;
    apply(outRoot, root, pExpression);
    return outRoot;
}

void apply(json& outRoot, const json& root, std::shared_ptr<Expression> pExpression)
{
    Context cxt(root);
    pExpression->apply(cxt);

    for(auto pResultNode : cxt.getOutput())
    {
        outRoot.push_back(*pResultNode);
    }
}
}
