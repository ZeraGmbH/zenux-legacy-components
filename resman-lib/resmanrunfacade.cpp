#include "resmanrunfacade.h"

ResmanRunFacade::ResmanRunFacade() :
    m_scpiInterface(&m_resMan),
    m_serverInterface(&m_scpiInterface)
{
    init();
}

ResmanRunFacade::ResmanRunFacade(VeinTcp::AbstractTcpWorkerFactoryPtr tcpNetworkFactory) :
    m_scpiInterface(&m_resMan),
    m_serverInterface(&m_scpiInterface, tcpNetworkFactory)
{
    init();
}

void ResmanRunFacade::init()
{
    Application::ResourceIdentity::setSCPIInterface(&m_scpiInterface);
    m_serverInterface.start();
}
