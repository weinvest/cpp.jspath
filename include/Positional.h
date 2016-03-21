#ifndef _JSPATH_POSITIONAL_H
#define _JSPATH_POSITIONAL_H
#include "Expression.h"
namespace jspath
{

class Positional: public Expression
{
public:
    Positional();


private:
    void doApply(Context& cxt, const ptree& input) override;
};
}
#endif
