//System Includes
#include <memory>

//Project Includes
#include <corvusoft/restless/session.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/stub/adaptor.hpp>
#include <corvusoft/stub/run_loop.hpp>

//System Namespaces
using std::make_shared;

//Project Namespaces
using corvusoft::restless::Session;

//External Namespaces
using corvusoft::stub::RunLoop;
using corvusoft::stub::Adaptor;

TEST_CASE( "Create class instance." )
{
    auto runloop = make_shared< RunLoop >( );
    auto adaptor = make_shared< Adaptor >( runloop );
    
    REQUIRE_NOTHROW( Session( ) );
    REQUIRE_NOTHROW( Session( nullptr, nullptr ) );
    REQUIRE_NOTHROW( Session( nullptr, runloop ) );
    REQUIRE_NOTHROW( Session( adaptor, nullptr ) );
    REQUIRE_NOTHROW( Session( adaptor, runloop ) );
}
