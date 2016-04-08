#include "JSPath.h"
#include "Context.h"
#include "Expression.h"
#include "compiler/JSPathCompiler.h"
namespace jspath
{
std::shared_ptr<Expression> compile(const std::string& applyExpr)
{
    size_t pos = 0;
    try
    {
        Compiler compiler;
        return compiler.compile(applyExpr, pos);
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << " at column " << pos << std::endl;
        return nullptr;
    }
}

json apply(const json& root, std::shared_ptr<Expression> pExpression, const json& variables)
{
    json outRoot;
    apply(outRoot, root, pExpression, variables);
    return outRoot;
}

void apply(json& outRoot, const json& root, std::shared_ptr<Expression> pExpression, const json& variables)
{
    Context cxt(root);
    pExpression->apply(cxt, variables);
    cxt.getOutput()->swap(outRoot);
}
}
