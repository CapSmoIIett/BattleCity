#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Object.h"


// Экземпляр этого класса будет создаваться у главного (первого) игрока
class Server
{
public:
    Server();
    ~Server();

    // Обновляется и обновляет текущую объектную сцену
    void synchronize(ObjectScene *scene);

    // Обновляется и обновляет других игроков  
    void checkClients();

private:
    std::unordered_map <int, Object*> object_list;
    std::vector<int> clients;
};