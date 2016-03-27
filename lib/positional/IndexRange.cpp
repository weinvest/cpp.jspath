#include <cstdlib>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "positional/IndexRange.h"

namespace jspath
{
IndexRange::IndexRange(const std::string& index)
    :mIsRange(true)
    ,mFrom(END)
    ,mTo(-1)
    ,mStep(1)
{
    size_t pos = 0;
    mFrom = parseIndex(index, pos, 0);

    if(pos == index.length())
    {
        mIsRange = false;
    }
    else
    {
        mTo = parseIndex(index, ++pos, END);
        mStep = parseIndex(index, ++pos, 1);
    }
}

int IndexRange::parseIndex(const std::string& str, size_t& from, int blankValue)
{
    for(; from < str.length() && std::isspace(str.at(from)); ++from)
    {}

    if(from >= str.length())
    {
        return blankValue;
    }

    if(':' == str.at(from))
    {
        return blankValue;
    }

    int value = 0, sign = 1;
    if('-' == str.at(from))
    {
        sign = -1;
        ++from;
    }
    else if('+' == str.at(from))
    {
        ++from;
    }

    for(; from < str.length() && std::isdigit(str.at(from)); ++from)
    {
        value *= 10;
        value += (str.at(from) - '0');
    }
    value *= sign;


    for(; from < str.length() && std::isspace(str.at(from)); ++from)
    {}

    if(from < str.length())
    {
        if(':' != str.at(from))
        {
            throw std::logic_error("The primitive 4 array index must be in set{0,1,2,3,4,5,6,7,8,9,space,':'} and index range should be divided by ':'");
        }
    }

    return value;
}

int IndexRange::begin(int size)
{
    if(mIsRange)
    {
        if(mFrom <= -size)
        {
            return 0;
        }
        else if(mFrom >= size)
        {
            return END;
        }
    }
    else if(mFrom < -size || mFrom >= size)
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
