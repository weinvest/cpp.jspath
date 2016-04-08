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

    void apply(Context& cxt, const json& variables) override;
private:
    void doApply(Context& cxt, const json& variables) override;

    IndexRange mRange;
};
}
#endif
