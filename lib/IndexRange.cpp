#include <cstdlib>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "IndexRange.h"

namespace jspath
{
IndexRange::IndexRange(const std::string& index)
    :mIsRange(true)
    ,mStep(1)
{
	auto firstPos = index.find_first_of(':');
	if(std::string::npos == firstPos)
	{
		mIsRange = false;
	    mFrom = boost::lexical_cast<int>(index);
	}
	else
	{
        size_t fromBeg = 0;
        if(isBlank(index, fromBeg, firstPos))
        {
        	mFrom = 0;
        }
        else
        {
            mFrom = boost::lexical_cast<int>(index.substr(fromBeg, firstPos - fromBeg));
        }

        size_t toBeg = firstPos + 1;
        auto secondPos = index.find_first_of(toBeg + 1, ':');
        if(std::string::npos == secondPos)
        {
            if(isBlank(index, toBeg, std::string::npos))
            {
            	mTo = END;
            }
            else
            {
            	mTo = boost::lexical_cast<int>(index.substr(toBeg));
            }
        }
        else
        {
            mTo = boost::lexical_cast<int>(index.substr(toBeg, secondPos));
            mStep = boost::lexical_cast<int>(index.substr(secondPos + 1));
        }
	}
}

bool IndexRange::isBlank(const std::string& str, size_t& from, size_t to)
{
    for(; !std::isdigit(str.at(from)) && from < to; ++from){}
    return from == to;
}

int IndexRange::begin(int size)
{
	if(mFrom <= -size)
	{
		return 0;
	}
	else if(mFrom >= size)
	{
		return END;
	}

    return (mFrom + size) % size;
}

int IndexRange::end(int size)
{
	if(!mIsRange)
	{
	    return begin(size) + 1;
	}

	if(mTo >= size)
	{
		return size;
	}
	else if(mTo <= -size)
	{
		return -1;
	}

	return (mTo + size) % size;
}
}
