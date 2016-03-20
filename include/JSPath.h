#ifndef _JSPATH_H
#define _JSPATH_H
#include <string>
#include <memory>
#include <boost/property_tree/ptree.hpp>
namespace jspath
{
class Expression;
std::shared_ptr<Expression> compile(const std::string& applyExpr);

using boost::property_tree::ptree;

ptree apply(const ptree& root, std::shared_ptr<Expression> pExpression);
void apply(ptree& outRoot, const ptree& root, std::shared_ptr<Expression> pExpression);
}
#endif
