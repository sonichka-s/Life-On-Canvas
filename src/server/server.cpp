#include <iostream>
#include <httpserver.hpp>

using namespace httpserver;

class Server:
public:
    Server(port Port){}

    void registerResourceCreate(std::string resource, ch){}
    void registerResourceCreate(std::string resource, uh){}
    void registerResourceCreate(std::string resource, rh){}
    void registerResourceCreate(std::string resource, dh){}
    void registerResourceCreate(std::string resource, jh){}

}
private:
    int Port;
    createHandler& ch;
    updateHandler& uh;
    readHandler& rh;
    deleteHandler& dh;
    joinHandler& jh;