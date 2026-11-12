# Custom In-Memory Redis Server

Welcome to my custom-built, blazing-fast Redis clone! ⚡ This is a lightweight, multi-threaded, in-memory key-value database written entirely from scratch in C++. 

It speaks the official Redis Serialization Protocol (RESP), which means you can connect to it using the standard `redis-cli` and use it just like the real thing. Oh, and it handles **over 113,000 requests per second**! 

## Concepts & Tech Stack Under the Hood

Building a database from scratch is no joke! Here are the core computer science concepts powering this engine:

*   **Raw TCP/IP Sockets:** No high-level HTTP frameworks here! Network communication is handled entirely via low-level C-style sockets for maximum speed.
*   **Concurrency & Multithreading:** Spawns detached threads to effortlessly juggle hundreds of concurrent client connections without breaking a sweat.
*   **Thread Safety & Read-Write Locks:** Utilizes C++17 `std::shared_mutex` so thousands of users can read data at the exact same time, while write operations queue up safely.
*   **Custom RESP Parser:** Translates the raw byte streams from standard Redis clients into actionable C++ commands.
*   **O(1) Data Structures:** Powered by `std::unordered_map` for instant data retrieval, whether you're grabbing a string, pushing to a list, or checking a hash.
*   **Asynchronous Persistence:** A background thread periodically snapshots the RAM data and dumps it to a `.my_rdb` file so data survives server restarts.

## 🛠️ How to Spin It Up

Ready to play around? Getting this running on your local machine is super easy.

### 1. Build the Server
I've included a handy `Makefile`. Just run this to compile the highly-optimized C++17 binary:
```bash
make rebuild
```

### 2. Start the Server
Launch the server (it defaults to port 6380 so it doesn't conflict with any official Redis instances you might have running):
```bash
make run
# Alternatively: ./my_redis_server 6380
```

### 3. Connect as a Client
Open a **new** terminal window and use the official Redis CLI tool to talk to the custom server:
```bash
redis-cli -p 6380
```
Boom! You're connected. Try typing `PING`, `SET mykey "hello"`, or `GET mykey`!

## Try Breaking It (Load Testing)
Want to see this thing fly? If you have `redis-benchmark` installed, open a new terminal and throw 10,000 requests at it from 100 parallel clients:
```bash
redis-benchmark -p 6380 -c 100 -n 10000 -t ping,set,get
```
*Spoiler alert: It handles it in under a tenth of a second.* 