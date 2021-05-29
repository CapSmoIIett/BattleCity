#pragma once 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stack>

#include "Object.h"
#include "Posts.h"
#include "Controller.h"


// Экземпляр этого класса будет создаваться у главного (первого) игрока
class Server
{
public:
    Server();
    ~Server();

    // Отправляет изменения клиенту
    void Send();  

    // Принимаем команды от клиента
    void Get();

    // Обновляется и обновляет текущую объектную сцену
    void synchronize(ObjectScene *scene);
    
    //
    void updateController(Controller& controller, ObjectScene* scene);

    void addObject(int x, Object&);

private:
    std::unordered_map <int, Object*> object_list;
    std::stack<PostSC> posts;
    std::stack<PostC> commands;
    //std::vector<int> clients;

    int client;

    int sock;
    int listener;
};