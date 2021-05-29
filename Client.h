#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stack>
#include <arpa/inet.h>

#include "Object.h"
#include "Posts.h"



// Экземпляр этого класса будет создаваться у второстепенных игроков

/*
    Клиент будет получать данные о сцене объектов сервера 
    и будет отталкиваться от них.

    Клиент будет отправлять сообщения о получении данных, и
    действиях которые он совершает (его Controller будет на сервере)
*/
class Client
{
public:
    Client(char *  ip = "127.0.0.1");
    ~Client();

    // Принимаем изменения
    void Get();

    // Отправляем команды
    void Send();

    void SetCommands(int command, int direction = 0);
    
    // Обновляется от сервера 
    void updateFromServer(ObjectScene *scene);

private:
    std::unordered_map <int, Object*> object_list;
    std::stack<PostSC> posts;
    std::stack<PostC> commands;

    int sock;
};