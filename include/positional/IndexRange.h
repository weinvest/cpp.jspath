#ifndef _JSPATH_INDEX_RANGE_H
#define _JSPATH_INDEX_RANGE_H

#include <string>
namespace jspath
{

class IndexRange
{
public:
	static const int END = (1 << 30);

    IndexRange(const std::string& index);

    int begin(int size);
    int end(int size);

    int getStep() const { return mStep; }
private:
    int parseIndex(const std::string& str, size_t& from, int blankValue);

    bool mIsRange;
    int mFrom;
    int mTo;
    int mStep;
};
}
#endif
