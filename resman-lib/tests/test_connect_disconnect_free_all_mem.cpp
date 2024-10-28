#include "test_connect_disconnect_free_all_mem.h"
#include "resmanrunfacade.h"
#include <timemachineobject.h>
#include <tcpnetworkfactory.h>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_connect_disconnect_free_all_mem)

void test_connect_disconnect_free_all_mem::connect()
{
    ResmanRunFacade resman(VeinTcp::TcpNetworkFactory::create());
    TimeMachineObject::feedEventLoop();

    VeinTcp::TcpPeer rmConnection;
    QSignalSpy connectionSpy(&rmConnection, &VeinTcp::TcpPeer::sigConnectionEstablished);
    rmConnection.startConnection("127.0.0.1", 6312);
    TimeMachineObject::feedEventLoop();

    QCOMPARE(connectionSpy.count(), 1);
}
