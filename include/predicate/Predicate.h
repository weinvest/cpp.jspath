#ifndef _JSPATH_PREDICATE_H
#define _JSPATH_PREDICATE_H
#include "json.hpp"
namespace jspath
{
using nlohmann::json;
class Context;
class Predicate
{
public:
    Predicate();
    virtual ~Predicate();

    virtual bool eval(const Context& cxt, const json& variables) = 0;
};
}
#endif
