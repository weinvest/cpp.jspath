#include <boost/algorithm/string.hpp>
#include "location/DotLocationPath.h"
#include "Context.h"
namespace jspath
{
DotLocationPath::DotLocationPath(const std::string& path)
    :LocationPath(boost::trim_copy(path))
{}

void DotLocationPath::doApply(Context& cxt)
{
	auto& input = cxt.getInput();
    if(input->is_object())
	{
        if(input->count(getPath()))
		{
            cxt.getOutput() = Context::StepOutput(&(*input)[getPath()], [](void*){});
		}
	}
    else if(input->is_array())
	{
        for(auto& child : *input)
		{
			if(child.count(getPath()))
			{
                cxt.getOutput()->push_back(child[getPath()]);
			}
		}
	}

}
}

