#include "DotLocationPath.h"
#include "Context.h"
namespace jspath
{
    DotLocationPath::DotLocationPath(const std::string& path)
	:LocationPath(path)
    {}

    void DotLocationPath::doApply(Context& cxt, const ptree& input)
    {
	if(input.count(getPath()))
	{
	    cxt.getOutput().push_back(&input.get_child(getPath()));
	}
    }
}

