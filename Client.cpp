#include "Client.h"

Client::Client()
{
    
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    
}

Client::~Client()
{
    close(sock);
}

void Client::Get()
{

    unsigned char number[sizeof(int)];

    recv(sock, number, sizeof(int), 0);

    //получаем количество эллементов
    int size = byteToInt(number);


    while (size--)
    {
        unsigned char message[POST_SIZE];
        
        // принимаем пост
        recv(sock, message, POST_SIZE, 0);

        // сообщаем что все хорошо
        send(sock, (void*)1, sizeof(int), 0);

        Post post(message);
        posts.push(post);
        //recv(sock, buf, sizeof(message), 0);
    }
}

void Client::updateFromServer(ObjectScene *scene)
{
    while (!posts.empty())
    {
        Post post = posts.top();
        Object obj = post.object;

        switch (post.change)
        {
        case CREATE:
        {
            Point p = obj.get_point();
            scene->addObject(p.x, p.y, obj.type);
            break;
        }
        
        default:
            break;
        }
    }

}