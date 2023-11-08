#ifndef TEST_CONNECT_DISCONNECT_FREE_ALL_MEM_H
#define TEST_CONNECT_DISCONNECT_FREE_ALL_MEM_H

#include <QObject>

class test_connect_disconnect_free_all_mem : public QObject
{
    Q_OBJECT
private slots:
    void connect();
    void connectDisconnect();
private:
    void feedEventLoop();
};

#endif // TEST_CONNECT_DISCONNECT_FREE_ALL_MEM_H
