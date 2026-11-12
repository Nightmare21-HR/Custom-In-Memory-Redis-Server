#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 

inline void loadEnv(const std::string& filename = ".env") {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No .env file found, using defaults.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
   
        if (line.empty() || line[0] == '#') continue;

        auto pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            
         
            setenv(key.c_str(), value.c_str(), 1);
        }
    }
}
#endif