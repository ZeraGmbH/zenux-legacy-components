#include "resman_clientmultiton.h"

#include "resman_clientsocket.h"
#include "resman_scpiinterface.h"
#include "resman_resource.h"
#include <netmessages.pb.h>

#include <QDebug>

namespace ResourceServer
{
ClientMultiton::ClientMultiton(ResourceServer::ClientSocket *t_parent, const QByteArray& t_clientId) :
    m_parent(t_parent),
    m_clientId(t_clientId)
{
}

ClientMultiton::~ClientMultiton()
{
    qDebug() << "Client disconnected:" << m_name;
}

QString ClientMultiton::getName() const
{
    return m_name;
}

QString ClientMultiton::getIpAddress() const
{
    return m_parent->getIpAdress();
}

void ClientMultiton::doSendACK(const QString &t_message) const
{
    m_parent->doSendACK(t_message, m_clientId);
}

void ClientMultiton::doSendDebug(const QString &t_message) const
{
    m_parent->doSendDebug(t_message, m_clientId);
}

void ClientMultiton::doSendError(const QString &t_message) const
{
    m_parent->doSendError(t_message, m_clientId);
}

void ClientMultiton::doSendNACK(const QString &t_message) const
{
    m_parent->doSendNACK(t_message, m_clientId);
}

void ClientMultiton::onMessageReceived(const std::shared_ptr<ProtobufMessage::NetMessage> &message)
{
    Q_ASSERT(message != nullptr);
    if(message->has_reply())
    {
        switch(message->reply().rtype())
        {
        case ProtobufMessage::NetMessage::NetReply::IDENT:
        {
            m_name = QString::fromStdString(message->reply().body());
            qDebug() << "Resourcemanager: Client identified" << m_name;
            doSendACK();
            break;
        }
        case ProtobufMessage::NetMessage::NetReply::ACK:
        {
            break;
        }
        case ProtobufMessage::NetMessage::NetReply::DEBUG:
        {
            qDebug() << QString("Client '%1' sent debug message:\n%2").arg(m_name).arg(QString::fromStdString(message->reply().body()));
            break;
        }
        default:
        {
            qWarning("Resourcemanager: Something went wrong with network messages!");
            /// @todo this is the error case
            break;
        }
        }
    }
    if(message->has_scpi())
    {
        ProtobufMessage::NetMessage_ScpiCommand tmpCMD = message->scpi();
        emit sigScpiTransaction(this, tmpCMD);
    }
}
}
