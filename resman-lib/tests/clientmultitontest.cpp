#include "clientmultitontest.h"

ClientMultitonTest::ClientMultitonTest(const QString &name, const QString &ipAddress) :
    m_name(name),
    m_ipAddress(ipAddress)
{
}

QString ClientMultitonTest::getName() const
{
    return m_name;
}

QString ClientMultitonTest::getIpAddress() const
{
    return m_ipAddress;
}

void ClientMultitonTest::doSendACK(const QString &message)
{
    m_ackList.append(message);
}

void ClientMultitonTest::doSendError(const QString &message)
{
    m_errList.append(message);
}

void ClientMultitonTest::doSendNACK(const QString &message)
{
    m_nackList.append(message);
}

const QStringList &ClientMultitonTest::getAckList() const
{
    return m_ackList;
}

const QStringList &ClientMultitonTest::getNackList() const
{
    return m_nackList;
}

const QStringList &ClientMultitonTest::getErrList() const
{
    return m_errList;
}
