#pragma once 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stack>

#include "Object.h"
#include "Posts.h"



// Экземпляр этого класса будет создаваться у главного (первого) игрока
class Server
{
public:
    Server();
    ~Server();

    // метод для работы в фоновом режиме
    void Run();

    // 
    void Send();  

    // Обновляется и обновляет текущую объектную сцену
    void synchronize(ObjectScene *scene);

    // Обновляется и обновляет других игроков  
    void checkClients();

    void addObject(int x, Object&);

private:
    std::unordered_map <int, Object*> object_list;
    std::stack<Post> posts;
    //std::vector<int> clients;

    int client;

    int sock;
    int listener;
};