#ifndef RESOURCEOBJECT_H
#define RESOURCEOBJECT_H

#include <scpiobject.h>
#include <resman_resourceidentity.h>
#include <memory>

namespace SCPI
{
/**
    @brief Represents the resource in the SCPI world
    */
class ResourceSCPIObject : public ScpiObject
{
public:
    /**
      @brief this constructor will set the const pointer to the Application::Resource
      */
    explicit ResourceSCPIObject(const QString &name, quint8 type);
    /**
     * @brief executeSCPI
     * @param t_input
     * @param t_output returns information about the resource
     * @return returns true if the t_input is a query
     */
    bool executeSCPI(const QString& t_input, QString& t_output) override;
    /**
     * @brief setter for m_resourceIdentity
     * @param t_resourceIdentity
     */
    void setResourceIdentity(Application::ResourceIdentity *t_resourceIdentity);

private:
    Application::ResourceIdentity *m_resourceIdentity = nullptr;
};

typedef std::shared_ptr<ResourceSCPIObject> ResourceSCPIObjectPtr;

}
#endif // RESOURCEOBJECT_H
