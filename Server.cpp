#include "Server.h"

Server::Server()
{
    int listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

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
    
    while(1)
    {
        // accept - принять соединение на сокете
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        while(1)
        {
            // recv* - получить сообщение из сокета
            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
            // send* - отправляет сообщения в сокет  
            send(sock, buf, bytes_read, 0);
        }
    }
    
}

Server::~Server()
{
    // Закрываем сокет
    close(sock);
}