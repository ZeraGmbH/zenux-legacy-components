#ifndef RESMANSCPIINTERFACE_H
#define RESMANSCPIINTERFACE_H

#include <QObject>
#include <QSet>

#include <netmessages.pb.h>
#include <scpi.h>
#include "resman_delegate.h"
#include "resman_catalog.h"
#include "resman_iclientmultiton.h"

namespace ResourceServer
{
class ClientMultiton;
}

namespace Application
{
class Resource;
}

class ResourceManager;

namespace SCPI
{
namespace CommandParams
{
/**
      @brief This enum allows parameter reordering and will provide legacy support if changed
      */
enum Parameters
{
    type=0,
    name,
    amount,
    description,
    port,
    _paramcount
};
}

namespace SetParams
{
const QString SET_RESOURCE="set";
enum Parameters
{
    command=0,
    amount
};
}

namespace FreeParams
{
const QString FREE_RESOURCE="free";
enum Parameters
{
    command=0
};
}

class ResourceSCPIObject;

/**
    @brief The interface between this application and the SCPI library
  */
class SCPIInterface : public QObject
{
    Q_OBJECT
public:
    explicit SCPIInterface(ResourceManager *t_resourceManager, QObject *t_parent=0);

    /**
      @brief Lists types which have a Catalog command
      */
    QString listTypes() const;

    /**
     * @brief deletes scpi nodes by their scpi command
     * @param t_command the location of the scpi node to remove
     */
    void removeSCPICommand(cSCPICommand t_command);
signals:

public slots:
    /**
      @brief The clients SCPI data is handled here
      */
    void onScpiTransaction(ResourceServer::IClientMultiton *t_clientMultiton, const ProtobufMessage::NetMessage_ScpiCommand &t_pbSCPICommand);

    void onClientMultitonDisconnected(ResourceServer::IClientMultiton *t_clientMultiton);

private:
    /**
     * @brief scpiAddResource
     * @param t_command
     * @param t_clientMultiton
     * @param [out] t_answerOut the result string of the operation
     * @return true for success
     */
    bool scpiAddResource(cSCPICommand t_command, ResourceServer::IClientMultiton *t_clientMultiton, QString &t_answerOut);

    /**
     * @brief gets the SCPI::Catalog for the t_resourceType or creates one if it doesn't exist
     * @param t_resourceType
     * @param t_scpiHierarchy
     * @return the SCPI::Catalog for the t_resource type is returned
     */
    CatalogPtr getOrCreateResourceTypeCatalog(const QString &t_resourceType, const QStringList &t_scpiHierarchy);

    /**
     * @brief getTypedCatalogHash
     * @return a hash of all catalogs by resource type is returned
     */
    QHash<QString, std::shared_ptr<Catalog>> getTypedCatalogHash() const;

    DelegatePtr m_addResource = std::make_shared<Delegate>("ADD", isCmdwP);
    DelegatePtr m_catalogType = std::make_shared<Delegate>("CATALOG", isCmd);
    DelegatePtr m_removeResource = std::make_shared<Delegate>("REMOVE", isCmdwP);
    DelegatePtr m_resourceModel = std::make_shared<Delegate>("MODEL",isQuery);
    DelegatePtr m_resourceProvider = std::make_shared<Delegate>("PROVIDER",isCmdwP);

    cSCPI m_scpiInstance;

    /**
     * @brief pointer to the resource manager
     */
    ResourceManager *m_resourceManager = nullptr;

    /**
      @brief Disables copying due to Singleton pattern
      */
    Q_DISABLE_COPY(SCPIInterface)
};
}
#endif // RESMANSCPIINTERFACE_H
