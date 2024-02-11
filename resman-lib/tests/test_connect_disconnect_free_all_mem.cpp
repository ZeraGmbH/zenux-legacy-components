#include "test_connect_disconnect_free_all_mem.h"
#include "resmanrunfacade.h"
#include "xiqnetpeer.h"
#include <timemachineobject.h>
#include <QSignalSpy>
#include <QTest>
#include <memory>

QTEST_MAIN(test_connect_disconnect_free_all_mem)

void test_connect_disconnect_free_all_mem::connect()
{
    ResmanRunFacade resman;
    TimeMachineObject::feedEventLoop();

    XiQNetPeer rmConnection;
    QSignalSpy connectionSpy(&rmConnection, &XiQNetPeer::sigConnectionEstablished);
    rmConnection.startConnection("127.0.0.1", 6312);
    TimeMachineObject::feedEventLoop();

    QCOMPARE(connectionSpy.count(), 1);
}
