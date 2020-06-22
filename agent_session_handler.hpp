#ifndef __AGENT_SESSION_HANDLER_HPP__
#define __AGENT_SESSION_HANDLER_HPP__

#include "inc.hpp"

// using _socket = boost::asio::ip::tcp::socket;

class agent_session_handler : public std::enable_shared_from_this<agent_session_handler> {
public:
    agent_session_handler(boost::asio::io_service & service) : 
        service_(service), 
        socket_(service),
        strand_(service){
        
        std::cout << "agent_session_handler" << std::endl;
    
    }
    boost::asio::ip::tcp::socket & socket(){
        return socket_;
    }
    void start(){
        read_packet();
    }
    void read_packet(){
        std::cout << "agent_session_handler::read_packet" << std::endl;
        
        boost::asio::async_read( socket_, 
                                boost::asio::buffer(in_packet_),
                                boost::asio::transfer_at_least(7),
                                [me=shared_from_this()] ( boost::system::error_code const & error, std::size_t bytes_size) {
                                    me->read_packet_done(error, bytes_size);
                                        });
    }
    void read_packet_done(boost::system::error_code const & error, std::size_t bytes_size){
        
        std::cout << "read_packet_done!!" << " thread Id: " << std::this_thread::get_id() << std::endl;
        std::cout.write(&in_packet_[0], bytes_size);
        read_packet();
    }

private:
    boost::asio::io_service& service_;    
    boost::asio::ip::tcp::socket socket_;
    boost::asio::io_service::strand strand_;
    boost::array<char, 8192> in_packet_;
    // boost::asio::streambuf in_packet_;
    std::deque<std::string> send_packet_queue; 


    

};

#endif