#ifndef _JSPATH_H
#define _JSPATH_H
#include <string>
#include <memory>
#include <boost/property_tree/ptree.hpp>
namespace jspath
{
class JSQuery;
std::shared_ptr<JSQuery> compile(const std::string& queryExpr);

using boost::property_tree::ptree;

ptree query(const ptree& root, std::shared_ptr<JSQuery> pQuery);
void query(ptree& outRoot, const ptree& root, std::shared_ptr<JSQuery> pQuery);
}
#endif
