#ifndef H2012_CLIENT_H
#define H2012_CLIENT_H

#include <vtcp_peer.h>
#include <QObject>
#include <QQueue>
#include <QHash>
#include <memory>

namespace google
{
namespace protobuf
{
class Message;
}
}

namespace ProtobufMessage
{
class NetMessage;
}

namespace ResourceServer
{
class ClientMultiton;
class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(VeinTcp::TcpPeer *t_clientSocket, QObject *parent = 0);
    ~ClientSocket();
    QString getIpAdress() const;

signals:
    void sigAboutToDisconnect(VeinTcp::TcpPeer *peer);
    void sigDisconnectedClientId(const QByteArray &t_clientId);
    void sigClientIdentified(ClientMultiton *t_clientMultiton);
    void sigClientMultitonDisconnected(ClientMultiton *t_clientMultiton);

public slots:
    void doSendACK(const QString &t_message=QString(), const QByteArray &t_cID=QByteArray()) const;
    void doSendDebug(const QString &t_message, const QByteArray &t_cID=QByteArray()) const;
    void doSendError(const QString &t_message=QString(), const QByteArray &t_cID=QByteArray()) const;
    void doSendNACK(const QString &t_message=QString(), const QByteArray &t_cID=QByteArray()) const;

private slots:
    void onDisconnectCleanup();
    void onMessageReceived(VeinTcp::TcpPeer *thisPeer, QByteArray message);
private:
    void handleMessageReceivedProto(std::shared_ptr<google::protobuf::Message> t_message);
    void sendMessage(ProtobufMessage::NetMessage &t_message) const;
    VeinTcp::TcpPeer* m_zClient;
    QQueue<qint64> m_messageIdQueue;

    //QSet<QByteArray> m_clientIds;

    QHash<QByteArray, ClientMultiton*> m_clientSockets;
    Q_DISABLE_COPY(ClientSocket)
};
}

#endif // H2012_CLIENT_H
