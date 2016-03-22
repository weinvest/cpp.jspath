#ifndef _JSPATH_PREDICATE_H
#define _JSPATH_PREDICATE_H
#include <boost/property_tree/ptree.hpp>
namespace jspath
{
using boost::property_tree::ptree;
class Context;
class Predicate
{
public:
    Predicate();
    virtual ~Predicate();

    virtual bool eval(const Context& cxt, const ptree& input) = 0;
};
}
#endif
