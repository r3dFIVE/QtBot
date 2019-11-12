#include <QCoreApplication>
#include "bot.h"

#ifdef __cplusplus
extern "C"{
#endif

#include <sodium.h>
#include <opus.h>

#ifdef __cplusplus
}
#endif

#include "payloads/gatewaypayload.h"
#include "lockingdeque.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string test = "{ \"id\" : \"1\", \"username\" : \"ross\" }";


    LockingDeque<int> q;
    q.enqueue_front(1);
    q.enqueue_front(2);
    q.enqueue_front(3);
    q.enqueue_front(4);
    q.enqueue_front(5);
   // QDeque<GatewayPayload> (QList<GatewayPayload) d;
   // auto t = q.dequeue();

    Bot().Run();

    return 0;
}


