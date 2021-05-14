#include "Server.h"

Server::Server()
{
    
    struct sockaddr_in addr;

    // SOCK_STREAM - Обеспечивает создание двусторонних надежных и 
    // последовательных потоков байтов , поддерживающих соединения
    listener = socket(AF_INET, SOCK_STREAM, 0);         // socket - создает конечную точку соединения и возвращает ее описатель
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    // hton* и ntoh* переводят данные из узлового порядка
    // расположения байтов в сетевой и наоборот
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind - привязывает к сокету sockfd локальный адрес
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    // listen - слушать соединения на сокете  
    listen(listener, 1);
    
}

Server::~Server()
{
    // Закрываем сокет
    close(sock);
}

void Server::synchronize(ObjectScene *scene)
{
    for(auto i: scene->map_objects){                       
        if (i.second->data.type == "Spawner") 
            continue;         // Пропускаем спавнеры

        if (object_list.find(i.first) == object_list.end())
        {
            object_list[i.first] = new Object (i.first, i.second->data.type, i.second->get_point(), i.second->get_health());
            posts.push(Object (i.first, i.second->data.type, i.second->get_point(), i.second->get_health()));
             
        }
    }
        //сверяет изменения с абстрактной сценой и удаляет объекты
        std::vector<int> to_remove;
        for(auto i: this->object_list) {
            if (scene->map_objects.find(i.first) ==
                scene->map_objects.end()) {
                delete i.second;                        //если нет объекта в абстрактной сцене
                                                        //значит его надо удалить и из нашей сцены
                to_remove.push_back(i.first);
            }
        }
        for (auto i : to_remove) {
            object_list.erase(i);
        }
}

void Server::Send()
{
    char* buf;
    int bytes_read;
    
    sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        // Мы отправляем все изменения 
        while (!posts.empty())
        {
            while (*buf == 0)
            {
                int size = 0;
                void* post = NULL;//encrypt(posts.top());

                // send* - отправляет сообщения в сокет
                send(sock, post, size, 0);

                // recv* - получить сообщение из сокета
                bytes_read = recv(sock, buf, 1, 0);
            }
            posts.pop();
        }  
            
        
}

void* encrypt(Object obj , int& size)
{
    unsigned char* answer = 0;
    size = sizeof(int) + sizeof(obj.data.type) +
            sizeof(Point) + sizeof(int);

        answer = new unsigned char[size];
        
        
        
    

        return (void*) answer;
}