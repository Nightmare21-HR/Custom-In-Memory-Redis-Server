#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include "../include/RedisServer.h"
#include "../include/RedisDatabase.h"
#include "../include/Config.h"

using namespace std;
int main(int argc, char* argv[]){
    loadEnv(".env");
    int port=6380;
    if (const char* env_port = std::getenv("PORT")) {
        port = std::stoi(env_port);
    }
    if(argc>=2) port=stoi(argv[1]);
    std::string dump_file = "fs";
    if (const char* env_dump = std::getenv("DUMP_FILE")) {
        dump_file = env_dump;
    }
    if(RedisDatabase::getInstance().load(dump_file))
    std::cout<<"Database loaded from the db\n";
    else
    std::cout<<"No Dump found or load failed:";
    RedisServer server(port);

    // Background Persistance: dump the database every 300 sec (5*60 save database)
    std::thread persistanceThread([dump_file](){
        while(true){
            std::this_thread::sleep_for(std::chrono::seconds(300));
            if (!RedisDatabase::getInstance().dump(dump_file))
            std::cerr<<"Error Dumping Database\n";
            else
            std::cout<<"Database Dumped"<<dump_file<<"\n";

        }
    });
    persistanceThread.detach();
    server.run();

    return 0;

}