/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

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
            
            struct RequestImpl
            {
                double version = 0;
                
                core::Bytes body { };
                
                std::string path { };
                
                std::string method { };
                
                std::string protocol { };
                
                std::multimap< std::string, std::string > headers { };
                
                std::multimap< std::string, std::string > parameters { };
            };
        }
    }
}
