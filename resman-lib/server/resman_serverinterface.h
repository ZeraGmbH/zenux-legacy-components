#ifndef H2012_SERVERINTERFACE_H
#define H2012_SERVERINTERFACE_H

#include <vtcp_server.h>
#include <abstracttcpworkerfactory.h>
#include <QObject>
#include <QSet>

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
    explicit ServerInterface(SCPI::SCPIInterface *t_scpiInterface,
                             VeinTcp::AbstractTcpWorkerFactoryPtr tcpWorkerFactory, QObject *t_parent = 0);
    ~ServerInterface();
    void start();

public slots:
    void clientDisconnected(ClientSocket *t_clientSocket);
    void newClient(VeinTcp::TcpPeer *t_newClient);
    void onClientIdentified(ResourceServer::IClientMultiton *t_clientMultiton);
signals:
    void sigClientDisconnected(ResourceServer::IClientMultiton *t_clientMultiton);

private:
    SCPI::SCPIInterface *m_scpiInterface = nullptr;
    QList<ClientSocket*> m_clientSockets;
    VeinTcp::TcpServer* m_zServer = nullptr;
    Q_DISABLE_COPY(ServerInterface)
};
}
#endif // H2012_SERVERINTERFACE_H
