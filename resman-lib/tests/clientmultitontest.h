#ifndef CLIENTMULTITONTEST_H
#define CLIENTMULTITONTEST_H

#include "resman_iclientmultiton.h"
#include <QStringList>

/**
 * @brief ClientMultitonTest: Mock for resman client collecting responses on
 * SCPI commands
 */
class ClientMultitonTest : public ResourceServer::IClientMultiton
{
    Q_OBJECT
public:
    ClientMultitonTest(const QString &name, const QString &ipAddress);
    QString getName() const override;
    QString getIpAddress() const override;
public:
    void doSendACK(const QString &message = QString()) override;
    void doSendError(const QString &message = QString()) override;
    void doSendNACK(const QString &message = QString()) override;
    const QStringList &getAckList() const;
    const QStringList &getNackList() const;
    const QStringList &getErrList() const;

private:
    QString m_name;
    QString m_ipAddress;
    QStringList m_ackList;
    QStringList m_nackList;
    QStringList m_errList;
};

#endif // CLIENTMULTITONTEST_H
