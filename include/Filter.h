#ifndef _JSPATH_FILTER_H
#define _JSPATH_FILTER_H
#include "Expression.h"
#include "predicate/Predicate.h"
namespace jspath
{

class Filter:public Expression
{
public:
    Filter(std::shared_ptr<Predicate> predicate);

private:
    void doApply(Context& cxt) override;

    std::shared_ptr<Predicate> mPredicate;
};
}
#endif
