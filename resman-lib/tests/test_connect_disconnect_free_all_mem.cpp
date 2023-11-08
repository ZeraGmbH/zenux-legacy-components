#include "test_connect_disconnect_free_all_mem.h"
#include "resmanrunfacade.h"
#include "xiqnetpeer.h"
#include <QAbstractEventDispatcher>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_connect_disconnect_free_all_mem)

void test_connect_disconnect_free_all_mem::connect()
{
    ResmanRunFacade resman;
    feedEventLoop();

    XiQNetPeer rmConnection;
    QSignalSpy connectionSpy(&rmConnection, &XiQNetPeer::sigConnectionEstablished);
    rmConnection.startConnection("127.0.0.1", 6312);
    feedEventLoop();

    QCOMPARE(connectionSpy.count(), 1);
}

void test_connect_disconnect_free_all_mem::connectDisconnect()
{
    ResmanRunFacade resman;
    feedEventLoop();

    XiQNetPeer rmConnection;
    rmConnection.startConnection("127.0.0.1", 6312);
    feedEventLoop();

    QSignalSpy disconnectionSpy(&rmConnection, &XiQNetPeer::sigConnectionClosed);
    rmConnection.getTcpSocket()->close();
    feedEventLoop();

    QCOMPARE(disconnectionSpy.count(), 1);

}

void test_connect_disconnect_free_all_mem::feedEventLoop()
{
    while(QCoreApplication::eventDispatcher()->processEvents(QEventLoop::AllEvents));
}
