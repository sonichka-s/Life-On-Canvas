//
// Created by sonichka on 19.05.22.
//
#include <thread>
#include <chrono>
#include <thread_controller.h>

thread_controller *tc = new thread_controller;

//void timerFunc(){
//    int i = 0;
//    for (;;){
//        tc->simple("Test " + std::to_string(i));
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//        i++;
//    }
//}



int main(int argc, char **argv) {


//    wscb->options->asClient = true;
    tc->manager->ip = "192.168.1.10";

    tc->manager->cb.on_open = [](void *conn) -> void {
        std::cout << "[WS] Connection opened!" << std::endl;

//        wscb->simple("testing", [](json json_) -> void{
//            std::cout << "Response: " << json_.dump() << std::endl;
//        }, conn);

        //start a timer thread that sends a message to the server/clients every second.
//        std::thread thread = std::thread([]() {timerFunc();});
//        thread.detach();
    };

//    //uncomment "onListening" to start a WebSocket server instead
    tc->manager->cb.on_listen = []() -> void {
        std::cout << "[WS] Server listening! \n";
    };

    tc->manager->cb.on_error = [](cb_error error) -> void {
        std::cout << "[WS] Error: " << error.msg << ": " << error.ec.message() << std::endl;
    };

    tc->manager->cb.on_close = []() -> void {
        std::cout << "[WS] Session closed: <reason>" << std::endl;
    };



//    tc->manager->cb.onUnexpectedMessage = [](const json json_, const void* conn) -> void{
//        std::cout << "[WS] Unexpected message: " << json_.dump() << std::endl;
//
//        //Unexpected message = Server sent a message and is NOT expecting a response
//    };

//    wscb->on(
//            "test", //if the command "test" is received, the lambda below will be executed.
//            [](json json_, std::function<void(const json)> respondWith) -> void{
//                std::cout << "[WS] Responding to expectation 'testing' with it's own message." << std::endl;
//                respondWith(json_);
//            }
//    );
//
//    wscb->on(
//            "progress", //if the command "test" is received, the lambda below will be executed.
//            [](json json_, std::function<void(const json)> respondWith) -> void{
//                std::cout << "[WS] Testing progress..." << std::endl;
//
//                json json__ = json::parse(json_.dump());
//
//                for (int i = 0; i <= 10; i++){
//                    json__["progress"] = std::to_string(i);
//                    respondWith(json__);
//                }
//            }
//    );
//
    tc->start_server();
//
//


    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();


    return EXIT_SUCCESS;
}