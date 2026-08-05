#ifndef CLIENTMULTITON_H
#define CLIENTMULTITON_H

#include "resman_iclientmultiton.h"
#include <QObject>
#include <QSet>
#include <netmessages.pb.h>
#include <memory>

namespace Application
{
class Resource;
}

namespace ResourceServer
{
class ClientSocket;

/**
  * @brief Multiple clients can share one socket connection
  * this class represents a client
  */
class ClientMultiton : public IClientMultiton
{
    Q_OBJECT
public:
    explicit ClientMultiton(ResourceServer::ClientSocket *t_parent, const QByteArray& t_clientId);
    ~ClientMultiton();
    QString getName() const override;

    QString getIpAddress() const override;
signals:
    /**
     * @brief is called when a client sent the IDENT command
     */
    void sigClientIdentified();

public:
    void doSendACK(const QString &t_message=QString()) override;
    void doSendDebug(const QString &t_message) const;
    void doSendError(const QString &t_message=QString()) override;
    void doSendNACK(const QString &t_message=QString()) override;

    void onMessageReceived(const std::shared_ptr<ProtobufMessage::NetMessage> &message);

private:
    QString m_name;

    ResourceServer::ClientSocket *m_parent;
    const QByteArray m_clientId;

    Q_DISABLE_COPY(ClientMultiton)
};
}
#endif // CLIENTMULTITON_H
