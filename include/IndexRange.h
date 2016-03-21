#ifndef _JSPATH_INDEX_RANGE_H
#define _JSPATH_INDEX_RANGE_H

namespace jspath
{

class IndexRange
{
public:
    IndexRange(const std::string& index);

private:
    size_t mFrom;
    size_t mTo;
};
}
#endif
