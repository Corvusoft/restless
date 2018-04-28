Restless [![Build Status](https://travis-ci.org/Corvusoft/restless.svg?branch=master)](https://travis-ci.org/Corvusoft/restless)
=============================================================================================================================

---

Restless is a comprehensive and consistent programming model for building applications that require seamless and secure communication over HTTP, with the ability to model a range of business processes, designed to target mobile, tablet, desktop and embedded production environments.

Example
-------

```C++
#include <memory>
#include <system_error>

#include <corvusoft/restless/session.hpp>
#include <corvusoft/restless/request.hpp>
#include <corvusoft/restless/response.hpp>

using std::shared_ptr;
using std::error_code;
using std::make_shared;

using corvusoft::restless::Session;
using corvusoft::restless::Request;
using corvusoft::restless::Response;

auto session = make_shared< Session >( adaptor, runloop );
session->open( "www.corvusoft.co.uk", 80, [ ]( auto session, auto status )
{    
    auto request = make_shared< Request >( );
    request->set_version( 1.1 );
    request->set_path( "/" );
    request->set_method( "GET" );
    request->set_protocol( "HTTP" );
    
    session->send( request, [ ] ( auto session, auto response, auto status )
    {
        //Process response...
        return error_code( );
    } );
    
    return error_code( );
} );
```

License
-------

&copy; 2013-2018 Corvusoft Limited, United Kingdom. All rights reserved.

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
cmake  ..
make install
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
| Compiler |            C++14 compliant or above             |

Contact
-------

| Method                                      | Description                                 |
|:--------------------------------------------|:--------------------------------------------|
| [Twitter](http://www.twitter.com/corvusoft) | Tweet us your questions & feature requests. |
| support@corvusoft.co.uk                     | Support related queries.                    |
| sales@corvusoft.co.uk                       | Sale related queries.                       |
