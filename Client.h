#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Object.h"


// Экземпляр этого класса будет создаваться у второстепенных игроков
class Client
{
public:
    Client();
    ~Client();

    // Обновляется и обновляет текущую объектную сцену
    void synchronize(ObjectScene *scene);

    // Обновляется и обновляет других игроков  
    void checkServer();

private:
    std::unordered_map <int, Object*> object_list;
};