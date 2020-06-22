#include "inc.hpp"

int session_count = 0;

int main(int, char**) {
    generic_server<agent_session_handler> tmf(10);
    tmf.start_server(12345);
    while(1){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
