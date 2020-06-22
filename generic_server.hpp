#ifndef __GENERIC_SERVER_HPP__
#define __GENERIC_SERVER_HPP__

#include "inc.hpp"

using boost::asio::ip::tcp;
using boost::system::error_code;
using boost::asio::streambuf;


template <typename ConnectionHandler>
class generic_server{
    using shared_handler_t = std::shared_ptr<ConnectionHandler>;
    
public:

    generic_server(int thread_count = 1) 
        : thread_count_(thread_count)
        , acceptor_(io_service_)
    {
    }
    void start_server(uint16_t port){
        std::cout << "start server .. port : " << port << std::endl;
        auto handler = std::make_shared<ConnectionHandler> (std::ref(io_service_));
        // auto handler = std::make_shared<ConnectionHandler> (io_service_);

        
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(tcp::acceptor::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();

        std::cout << "start server .. listen.." << std::endl;
        acceptor_.async_accept( handler->socket() 
                               , [=, this] (auto ec) {
                                   handle_new_connection(handler, ec);
                               });
        std::cout << "start server .. emplace_back.." << std::endl;
        for(int i = 0 ; i < thread_count_; i++){
            thread_pool_.emplace_back( [=, this]{io_service_.run();});
        }
        std::cout << "start server .. end.." << std::endl;
    }
private:
    void handle_new_connection( shared_handler_t handler,
                                boost::system::error_code const & error){
        std::cout << "generic_server handle_new_connection" << std::endl;
        if(error) return;
        handler->start();

        auto new_handler
            = std::make_shared<ConnectionHandler> (io_service_);

        acceptor_.async_accept( new_handler->socket()
                                , [=, this](auto ec) {
                                    handle_new_connection( new_handler, ec);
                                });
    }
    int thread_count_;
    std::vector<std::thread> thread_pool_;
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
};

#endif