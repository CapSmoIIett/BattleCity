#include "Server.h"

Server::Server()
{
    int client;
	struct sockaddr_in addr_client;   
    struct sockaddr_in addr;

    //std::cout << "size" << sizeof(Post) << "\n";

    // SOCK_STREAM - Обеспечивает создание двусторонних надежных и 
    // последовательных потоков байтов , поддерживающих соединения
    listener = socket(AF_INET, SOCK_STREAM, 0);         // socket - создает конечную точку соединения и возвращает ее описатель
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    //TODO искать свободный порт
    // hton* и ntoh* переводят данные из узлового порядка
    // расположения байтов в сетевой и наоборот
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_addr.s_addr = INADDR_ANY;

    // bind - привязывает к сокету sockfd локальный адрес
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    // listen - слушать соединения на сокете 
    if (listen(listener, 1) < 0)
    {
        exit (2);
    }

    sock = accept(listener, (struct sockaddr *)&addr_client, (socklen_t*)&client);
    if(sock < 0)
    {
        perror("accept");
        exit(3);
    }
 
    std::cout << "Connect" << "\n";
}

Server::~Server()
{
    // Закрываем сокет
    close(sock);
}

void Server::synchronize(ObjectScene *scene)
{
    for(auto i: scene->map_objects){                       
        if (i.second->type == SPAWNER) 
            continue;         // Пропускаем спавнеры
    
        auto obj = object_list.find(i.first);

        if (i.second->type == TANK ||
            i.second->type == PLAYER_TANK ||
            i.second->type == BULLET)
        {
            int dir_scene = dynamic_cast<Directable*>(i.second)->get_dir();
            //int dir_obj =  static_cast<Directable*>(&obj).get_dir();
            //if (dir )
        }

        // Поиск под пункт Create
        if (obj == object_list.end())
        {
            object_list[i.first] = new Object (i.first, i.second->type, i.second->get_point(), i.second->get_health());
            posts.push(Post(i.first, CREATE, Object (i.first, i.second->type, i.second->get_point(), i.second->get_health())));
            continue; 
        }

        //  Поиск под пункт Move
        if  (i.second->get_point() != (*obj).second->get_point())
        {
            (*obj).second->set_point(i.second->get_point());
            posts.push(Post(i.first, MOVE, Object (i.first, i.second->type, i.second->get_point())));
            continue;
        }
        
        // ДЛя изменения направлдения необходимо переписать Post с объединением
        //if (i.second->dir != (*obj).second->get_point())
    }
    
    // Remove
    // сверяет изменения с абстрактной сценой и удаляет объекты
    std::vector<int> to_remove;
    for(auto i: this->object_list) {
        if (scene->map_objects.find(i.first) == scene->map_objects.end()) {
            delete i.second;                        //если нет объекта в абстрактной сцене
                                                    //значит его надо удалить и из нашей сцены
            to_remove.push_back(i.first);
            posts.push(Post(i.first, DELETE, Object (i.first, i.second->type, i.second->get_point())));
        }
    }
    for (auto i : to_remove) {
        object_list.erase(i);
    }
}

void Server::Send()
{
    char buf;

        unsigned char* number = new unsigned char [sizeof(int)];

        intToByte(posts.size(), number);

        // отправляем количество изменений
        //send(sock, number, sizeof(int), 0);
        write(sock , number, sizeof(int));

        std::cout << "Размер отправил" << "\n";

        recv(sock, &buf, sizeof(char), 0);

        std::cout << "Ответ получил" << "\n";

        // Мы отправляем все изменения 
        while (!posts.empty())
        {
            buf = 0;
            int size = 0;
                Post post = posts.top();

                // send* - отправляет сообщения в сокет
                send(sock, post.encrypt(), POST_SIZE, 0);

                std::cout << post.object.get_point().x 
                    << post.object.get_point().y << "\n";
                std::cout << "Post отправил" << "\n";

                // recv* - получить сообщение из сокета
                recv(sock, &buf, sizeof(char), 0);

                std::cout << "Ответ получил" << "\n";
            
            posts.pop();
        }     
    delete[] number;
}
