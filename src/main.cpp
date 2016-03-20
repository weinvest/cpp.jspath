#include "JSPath.h"
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/exception/all.hpp>
int main(int argc, char** argv)
{
    using namespace boost::program_options;
    options_description opts("jspath options");
    opts.add_options()
            ("help,h","print this help information.")
            ("input,i",value<std::string>(),"input json file")
            ("query,q",value<std::string>(), "query expression")
            ("substs,p",value<std::string>(),"substitutions");


    variables_map vm;
    store(parse_command_line(argc,argv,opts),vm);

    if(vm.count("help"))
    {
        std::cout<<opts<<std::endl;
        return 0;
    }

    if(0 == vm.count("input") || 0 == vm.count("query"))
    {
        std::cout<<opts<<std::endl;
        return -1;
    }

    namespace bfs = boost::filesystem;
    std::string inputFileName = vm["input"].as<std::string>();
    if(!bfs::is_regular_file(inputFileName))
    {
        std::cout << inputFileName << " is not a file" << std::endl;
        return -1;
    }

    try
    {
        using namespace boost::property_tree;
        ptree inputJson;
        read_json(inputFileName, inputJson);

        auto queryExpr = vm["query"].as<std::string>();
        auto query = jspath::compile(queryExpr);
        auto result = jspath::query(inputJson, query);

        write_json(std::cout, result);
        return 0;
    }
    catch(boost::exception& ex)
    {
        std::cout << "exception: " << boost::diagnostic_information(ex) << std::endl;
    }
    catch(const std::exception& ex)
    {
        std::cout << "exception: " << ex.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "unknow exception" << std::endl;
    }

    return -1;
}
