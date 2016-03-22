#include "JSPath.h"
#include "Context.h"
#include "Expression.h"
#include "location/DotLocationPath.h"
namespace jspath
{
std::shared_ptr<Expression> compile(const std::string& applyExpr)
{
    auto pResultExpression = std::make_shared<DotLocationPath>("ee");
    //pResultExpression->compile(applyExpr);
    return pResultExpression;
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
