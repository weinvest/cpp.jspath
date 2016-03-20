#include "JSPath.h"
#include "JSQuery.h"
namespace jspath
{
std::shared_ptr<JSQuery> compile(const std::string& queryExpr)
{
    auto query = std::make_shared<JSQuery>();
    query->compile(queryExpr);
    return query;
}

ptree query(const ptree& root, std::shared_ptr<JSQuery> pQuery)
{
    ptree outRoot;
    query(outRoot, root, pQuery);
    return outRoot;
}

void query(ptree& outRoot, const ptree& root, std::shared_ptr<JSQuery> pQuery)
{

}
}
