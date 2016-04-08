#ifndef _JSPATH_H
#define _JSPATH_H
#include <string>
#include <memory>
#include "json.hpp"
namespace jspath
{
class Expression;
std::shared_ptr<Expression> compile(const std::string& applyExpr);
using nlohmann::json;
json apply(const json& root, std::shared_ptr<Expression> pExpression, const json& variables);
void apply(json& outRoot, const json& root, std::shared_ptr<Expression> pExpression, const json& variables);
}
#endif
