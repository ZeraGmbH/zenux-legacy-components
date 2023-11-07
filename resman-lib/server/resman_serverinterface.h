#ifndef H2012_SERVERINTERFACE_H
#define H2012_SERVERINTERFACE_H

#include <QObject>
#include <QSet>

class XiQNetServer;
class XiQNetPeer;

class RMProtobufWrapper;

namespace SCPI
{
class SCPIInterface;
}

namespace ResourceServer
{
class IClientMultiton;
class ClientSocket;

class ServerInterface : public QObject
{
    Q_OBJECT
public:
    explicit ServerInterface(SCPI::SCPIInterface *t_scpiInterface, QObject *t_parent = 0);
    ~ServerInterface();
    void start();

public slots:
    void clientDisconnected(ClientSocket *t_clientSocket);
    void newClient(XiQNetPeer *t_newClient);
    void onClientIdentified(ResourceServer::IClientMultiton *t_clientMultiton);
signals:
    void sigClientDisconnected(ResourceServer::IClientMultiton *t_clientMultiton);

private:
    SCPI::SCPIInterface *m_scpiInterface = nullptr;
    QList<ClientSocket*> m_clientSockets;
    XiQNetServer* m_zServer = nullptr;
    RMProtobufWrapper* m_defaultWrapper = nullptr;
    Q_DISABLE_COPY(ServerInterface)
};
}
#endif // H2012_SERVERINTERFACE_H
