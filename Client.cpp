#include "Client.h"

Client::Client(char * ip)
{
    
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888); // или любой другой порт...
    if (inet_aton(ip, &addr.sin_addr) == 0)
    {
        exit (4);
    }


    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }
    std::cout << "Connect" << "\n";
    
}

Client::~Client()
{
    close(sock);
}

void Client::Get()
{

    unsigned char number[sizeof(int)];
    char answer = 1;

    recv(sock, number, sizeof(int), 0);

    std::cout << "Размер получил" << "\n";

    //получаем количество эллементов
    int size = byteToInt(number);

    write(sock , &answer, sizeof(char));

    std::cout << "ответ отправил" << "\n";
    
    if (size < 0) 
    {
        exit(4);
    }


    while (size)
    {
        unsigned char message[POST_SC_SIZE];
        
        // принимаем пост
        recv(sock, message, POST_SC_SIZE, 0);

        std::cout << "Post " << size << " получил" << "\n";

        // сообщаем что все хорошо
        //send(sock, (void*)1, sizeof(int), 0);
        write(sock , &answer, sizeof(char));

        std::cout << "Ответ отправил" << "\n";

        PostSC post(message);
        posts.push(post);
        //recv(sock, buf, sizeof(message), 0);
        size--;
    }
}

void Client::updateFromServer(ObjectScene *scene)
{
    while (!posts.empty())
    {
        PostSC post = posts.top();
        posts.pop();

        switch (post.change)
        {
        case CREATE:
        {
            scene->addObject(post.id, Object(post.id, post.type, post.point));
            break;
        }
        case DELETE:
        {
            auto it = scene->map_objects.find(post.id);
            if (it == scene->map_objects.end()) break;
            scene->map_objects.erase(it);   
            break;
        }
        case MOVE:
        {
            auto it = scene->map_objects.find(post.id);
            if (it == scene->map_objects.end()) break;
            (*it).second->set_point(post.point);
            break;
        }
        case TURN:
        {
            auto it = scene->map_objects.find(post.id);
            if (it == scene->map_objects.end()) break;
            (*it).second->set_direction(post.direction);
            break;
        }
        default:
            break;
        }
    }

}