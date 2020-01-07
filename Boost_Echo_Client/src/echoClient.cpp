#include <stdlib.h>
#include "../include/ConnectionHandler.h"
#include "../include/ClientKeyboard.h"
#include "../include/ClientSocket.h"
#include <boost/system/error_code.hpp>
#include <thread>

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);
    
    ConnectionHandler*  connectionHandler = new ConnectionHandler(host, port);
    MsgInfo* info = new MsgInfo();
    bool shouldTerminate = false;
    ClientKeyboard clientKeyboard(connectionHandler,host,port,shouldTerminate,info);
    ClientSocket clientSocket(connectionHandler,host,port,shouldTerminate,info);
    clientSocket.connect();
    std::thread threadKeyboard(&ClientKeyboard::run,&clientKeyboard); // run keyboard thread
    std::thread threadSocket(&ClientSocket::run,&clientSocket); // run socket thread
    threadKeyboard.join();
    threadSocket.join();
    connectionHandler->close();

    return 0;
}
