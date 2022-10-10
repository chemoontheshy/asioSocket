//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "asio/asio.hpp"

using asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
    try
    {
        asio::io_context io_context;

        tcp::socket s(io_context);
        tcp::resolver resolver(io_context);
        asio::connect(s, resolver.resolve("127.0.0.1", "6000"));

        const char* temp = "chen mo is studied.";
        size_t request_length = 20;
        asio::write(s, asio::buffer(temp, request_length));

        char reply[max_length];
        size_t reply_length = asio::read(s,
            asio::buffer(reply, request_length));
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
