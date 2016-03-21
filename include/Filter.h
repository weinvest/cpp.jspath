#ifndef _JSPATH_FILTER_H
#define _JSPATH_FILTER_H
#include "Expression.h"
namespace jspath
{

class Filter:public Expression
{
public:
    Filter();

private:
    void doApply(Context& cxt, const ptree& input) override;
};
}
#endif
