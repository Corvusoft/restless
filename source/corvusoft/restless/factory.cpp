/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restless/factory.hpp"
#include "corvusoft/restless/session.hpp"
#include "corvusoft/restless/request.hpp"
#include "corvusoft/restless/response.hpp"
#include "corvusoft/restless/detail/factory_impl.hpp"

//External Includes

//System Namespaces
using std::string;
using std::shared_ptr;
using std::unique_ptr;

//Project Namespaces
using corvusoft::restless::detail::FactoryImpl;

//External Namespaces
using corvusoft::core::RunLoop;

namespace corvusoft
{
    namespace restbed
    {
        Factory::Factory( const shared_ptr< RunLoop > runloop ) : m_pimpl( new FactoryImpl )
        {
            return;
        }
        
        Factory::~Factory( void )
        {
            return;
        }

        shared_ptr< Session > make_session( void )
        {

        }
        
        shared_ptr< Request > make_request( void )
        {

        }
        
        shared_ptr< Response > make_response( void )
        {

        }
    }
}
