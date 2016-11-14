Restless [![Build Status](https://travis-ci.org/Corvusoft/restless.svg?branch=master)](https://travis-ci.org/Corvusoft/restless)
=============================================================================================================================

---

Restless is a comprehensive and consistent programming model for building applications that require seamless and secure communication over HTTP, with the ability to model a range of business processes, designed to target mobile, tablet, desktop and embedded production environments.

Features
--------

| Feature                                                                                                                                                                                                       | Description                                                                                                                                                                                                                                                                                          |
|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Compliance                                                                                                                                                                                                    | Flexibility to address HTTP 1.0/1.1+ compliance.                                                                                                                                                                                                                                                     |
| Mature                                                                                                                                                                                                        | Secure, Stable, and extensively tested since 2013.                                                                                                                                                                                                                                                   |
| Community                                                                                                                                                                                                     | Active, vibrant and energetic open source community.                                                                                                                                                                                                                                                 |
| Support                                                                                                                                                                                                       | Commercial support is available from [Corvusoft](http://www.corvusoft.co.uk).                                                                                                                                                                                                                        |

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <restless>

using namespace std;
using namespace restless;

void response_handler( const shared_ptr< Session > session )
{
    auto response = session->get_response( );
    auto length = response->get_header( "Content-Length", 0 );
    
    session->fetch( length, [ ]( const shared_ptr< Session > session )
    {
        print( session->get_response( ) );
    } );
}

int main( const int, const char** )
{
    auto session = make_shared< Session >( );
    
    auto request = make_shared< Request >( Uri( "https://www.corvusoft.co.uk/" ) );
    request->set_header( "Accept", "*/*" );
    request->set_header( "Host", "www.corvusoft.co.uk" );
    request->set_query_parameter( "query", "search term" );
    
    session->send( request, response_handler );
    session->wait( );
    
    return EXIT_SUCCESS;
}
```

More in-depth examples can be found [here](https://github.com/corvusoft/restless/tree/master/example).

License
-------

&copy; 2013-2016 Corvusoft Limited, United Kingdom. All rights reserved.

The Restless framework is dual licensed; See [LICENSE](LICENSE) for full details.

Support
-------

Please contact sales@corvusoft.co.uk, for support and licensing options including bespoke software development, testing, design consultation, training, mentoring and code review.

Build
-----

```bash
git clone --recursive https://github.com/corvusoft/restless.git
mkdir restless/build
cd restless/build
cmake [-DBUILD_TESTS=YES] [-DBUILD_EXAMPLES=YES] [-DBUILD_SSL=NO] [-DBUILD_SHARED=YES] [-DCMAKE_INSTALL_PREFIX=/output-directory] ..
make [-j CPU_CORES+1] install
make test
```

You will now find all required components installed in the distribution folder.

Please submit all enhancements, proposals, and defects via the [issue](http://github.com/corvusoft/restless/issues) tracker; Alternatively ask a question on [StackOverflow](http://stackoverflow.com/questions/ask) tagged [#restless](http://stackoverflow.com/questions/tagged/restless).

Documentation
-------------

This codebase is intended to be as self documenting as possible. We have supplied many [examples](https://github.com/corvusoft/restless/tree/master/example) and [test suites](https://github.com/corvusoft/restless/tree/master/test) to help aid developers.

We are currently working on textual API documentation, however it's subject to erratic and frequent alteration; you've been warned.

Minimum Requirements
--------------------

| Resource | Requirement                                     |
|:--------:|:-----------------------------------------------:|
| Compiler |            C++11 compliant or above             |
|    OS    | BSD, Linux, Mac OSX, Solaris, Windows, Raspbian |

Road Map
--------

| Milestone                                                                            | Feature                                 | Status       |
|:------------------------------------------------------------------------------------:|:---------------------------------------:|:------------:|
|             [0.0](https://github.com/Corvusoft/restless/milestones/0.0)              |        (A)synchronous HTTP client       |  development |
|             [1.0](https://github.com/Corvusoft/restless/milestones/1.0)              |           HTTP 1.0 Compliance           |  development |
|             [1.0](https://github.com/Corvusoft/restless/milestones/1.0)              |           HTTP 1.1 Compliance           |  development |
|             [1.0](https://github.com/Corvusoft/restless/milestones/1.0)              |           Secure Socket Layer           |  development |
|             [1.0](https://github.com/Corvusoft/restless/milestones/4.5)              |            API Documentation            |  development |
|             [1.5](https://github.com/Corvusoft/restless/milestones/1.0)              |    Bind Service to specific Address     |    pending   |
|             [1.5](https://github.com/Corvusoft/restless/milestones/4.5)              |               Web Sockets               |    pending   |
|             [2.0](https://github.com/Corvusoft/restless/milestones/4.5)              |            Server-Side Events           |    pending   |
|             [2.5](https://github.com/Corvusoft/restless/milestones/5.0)              |      Client-side SSL certificates       |    pending   |
|             [3.0](https://github.com/Corvusoft/restless/milestones/5.0)              |            HTTP 2 compliance            |    pending   |
|             [3.5](https://github.com/Corvusoft/restless/milestones/5.0)              |         Refactor, Reduce, Reuse         |    pending   |

Contact
-------

| Method                                      | Description                                 |
|:--------------------------------------------|:--------------------------------------------|
| [Twitter](http://www.twitter.com/corvusoft) | Tweet us your questions & feature requests. |
| support@corvusoft.co.uk                     | Support related queries.                    |
| sales@corvusoft.co.uk                       | Sale related queries.                       |
