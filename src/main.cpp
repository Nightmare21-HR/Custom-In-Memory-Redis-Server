#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include "../include/RedisServer.h"
#include "../include/RedisDatabase.h"

using namespace std;
int main(int argc, char* argv[]){
    int port =6380; // default
    if(argc>=2) port=stoi(argv[1]);
    if(RedisDatabase::getInstance().load("dump.my_rdb"))
    std::cout<<"Database loaded from the db\n";
    else
    std::cout<<"No Dump found or load failed:";
    RedisServer server(port);

    // Background Persistance: dump the database every 300 sec (5*60 save database)
    std::thread persistanceThread([](){
        while(true){
            std::this_thread::sleep_for(std::chrono::seconds(10));
            if(!RedisDatabase::getInstance().dump("dump.my_rdb"))
            std::cerr<<"Error Dumping Database\n";
            else
            std::cout<<"Database Dumped to dump.my_rdb\n";

        }
    });
    persistanceThread.detach();
    server.run();

    return 0;

}