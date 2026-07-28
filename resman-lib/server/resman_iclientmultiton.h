#ifndef RESMAN_ICLIENTMULTITON_H
#define RESMAN_ICLIENTMULTITON_H

#include <netmessages.pb.h>
#include <QObject>
#include <QString>

namespace ResourceServer
{
class IClientMultiton : public QObject
{
    Q_OBJECT
public:
    virtual QString getName() const = 0;
    virtual QString getIpAddress() const = 0;
signals:
    /**
      *@brief Notifies the SCPI::SCPIInterface of new SCPI commands
      */
    void sigScpiTransaction(IClientMultiton *clientMultiton, const ProtobufMessage::NetMessage_ScpiCommand &command);
public:
    /**
    * @brief Sends acknowledgement
    * @param message Optional text
    */
    virtual void doSendACK(const QString &t_message = QString()) const = 0;
    virtual void doSendError(const QString &t_message = QString()) const = 0;
    virtual void doSendNACK(const QString &t_message = QString()) const = 0;
};
}

#endif // RESMAN_ICLIENTMULTITON_H
