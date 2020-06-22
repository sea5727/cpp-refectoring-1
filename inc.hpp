#ifndef __INC_HPP__
#define __INC_HPP__

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/chrono.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <iostream>
#include <thread>
#include "generic_server.hpp"
#include "agent_session_handler.hpp"

using boost::asio::ip::tcp;
using boost::system::error_code;
using boost::asio::streambuf;

#endif