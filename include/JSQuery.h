#ifndef _JSQUERY_H
#define _JSQUERY_H
#include <string>
namespace jspath
{
class JSQuery
{
public:
    JSQuery();

    void compile(const std::string& queryExpr);
};
}
#endif

