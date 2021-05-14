#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stack>

#include "Object.h"
#include "Posts.h"



// Экземпляр этого класса будет создаваться у второстепенных игроков

/*
    Клиент будет получать данные о сцене объектов сервера 
    и будет отталкиваться от них.

    Клиент будет отправлять сообщения о получении данных, И!!!
    ЛИБО Изменение положения танка
    ЛИБО Действия которые он совершает (его Controller будет на сервере)
*/
class Client
{
public:
    Client();
    ~Client();

    //
    void Get();

    // Обновляется от сервера 
    void updateFromServer(ObjectScene *scene);

private:
    std::unordered_map <int, Object*> object_list;
    std::stack<Post> posts;

    int sock;
};