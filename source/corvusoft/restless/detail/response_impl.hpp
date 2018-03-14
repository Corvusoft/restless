/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTLESS_DETAIL_RESPONSE_IMPL_H
#define _CORVUSOFT_RESTLESS_DETAIL_RESPONSE_IMPL_H 1

//System Includes
#include <map>
#include <string>

//Project Includes

//External Includes
#include <corvusoft/core/byte.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace restless
    {
        //Forward Declarations
        
        namespace detail
        {
            //Forward Declarations
            
            struct ResponseImpl
            {
                int status = 0;
                
                double version = 0;
                
                core::Bytes body { };
                
                std::string message { };
                
                std::string protocol { };
                
                std::multimap< std::string, std::string > headers { };
                
                std::multimap< std::string, std::string > parameters { };
            };
        }
    }
}

#endif  /* _CORVUSOFT_RESTLESS_DETAIL_RESPONSE_IMPL_H */
