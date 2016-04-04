#ifndef _JSPATH_JSENUM_H
#define _JSPATH_JSENUM_H
#include <cstdint>
#include <string>
#include <vector>
#include <boost/unordered/unordered_map.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/thread/once.hpp>
#define JSENUM_EXPAND(z,d,i,e) BOOST_PP_COMMA_IF(i) BOOST_PP_TUPLE_ELEM(2,0,e) = BOOST_PP_TUPLE_ELEM(2,1,e)
#define JSENUM_VALUE(seq) BOOST_PP_SEQ_FOR_EACH_I(JSENUM_EXPAND,-,seq)
#define JSENUM_PARSE(z,d,i,e) gString2Enum->insert(std::make_pair(BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2,0,e)),BOOST_PP_TUPLE_ELEM(2,0,e)));
#define JSENUM_TOSTR(z,d,i,e) gEnum2String->insert(std::make_pair(BOOST_PP_TUPLE_ELEM(2,0,e),BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2,0,e))));

#define JSENUM_IMPL_TO_STRING(EnumName,seq) \
    const std::string& EnumName::toString(EnumName::type v)\
    {\
        static boost::unordered_map<EnumName::type,std::string>* gEnum2String = nullptr;\
        static boost::once_flag initMap= BOOST_ONCE_INIT;\
        static const std::string UNKNOWN_VALUE("Unknow value for "#EnumName);\
        boost::call_once(initMap\
        ,[]()\
        {\
            gEnum2String = new boost::unordered_map<EnumName::type,std::string>();\
            BOOST_PP_SEQ_FOR_EACH_I(JSENUM_TOSTR,~,seq)\
        });\
        auto itResult = gEnum2String->find(v);\
        if(itResult != gEnum2String->end())\
        {\
            return itResult->second;\
        }\
        return UNKNOWN_VALUE;\
    }

#define JSENUM_IMPL_PARSE(EnumName,seq)\
    bool EnumName::parse(const std::string& value,EnumName::type& v)\
    {\
        static boost::unordered_map<std::string,EnumName::type>* gString2Enum = nullptr;\
        static boost::once_flag initMap= BOOST_ONCE_INIT;\
        boost::call_once(initMap\
        ,[]()\
		{\
            gString2Enum = new boost::unordered_map<std::string,EnumName::type>();\
            BOOST_PP_SEQ_FOR_EACH_I(JSENUM_PARSE,~,seq)\
		});\
        auto itResult = gString2Enum->find(value);\
        if(gString2Enum->end() != itResult)\
        {\
            v = itResult->second;\
            return true;\
        }\
        return false;\
   }

#define JSENUM_IMPL_PARSE_EX(EnumName, seq)\
    bool EnumName::parseEx(const std::string& value,int32_t& v)\
    {\
        std::vector<std::string> actions;\
        boost::algorithm::split(actions,value,boost::is_any_of("|"),boost::algorithm::token_compress_on);\
\
        for(auto& action : actions)\
        {\
            EnumName::type tmpAction;\
            if(Parse(action,tmpAction))\
            {\
                v |= tmpAction;\
            }\
            else\
            {\
                return false;\
            }\
        }\
\
        return true;\
    }


#endif
