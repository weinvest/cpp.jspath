#ifndef _JSPATH_POSITIONAL_H
#define _JSPATH_POSITIONAL_H
#include "Expression.h"
#include "IndexRange.h"
namespace jspath
{

class Positional: public Expression
{
public:
    Positional(IndexRange range);


private:
    void doApply(Context& cxt, const json& input) override;

    IndexRange mRange;
};
}
#endif
