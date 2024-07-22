#include "srpcpp/callbacks.hpp"
#include "modules/acl.hpp"
#include "core/context.hpp"
#include "core/sub/context.hpp"
#include <memory>
#include <list>

AclModule::AclModule(ietf::acl::PluginContext &ctx) : srpc::IModule<ietf::acl::PluginContext>(ctx)
{
    m_operContext = std::make_shared<AclOperationalContext>();
    m_changeContext = std::make_shared<AclModuleChangesContext>();
    m_rpcContext = std::make_shared<AclRpcContext>();
}

std::shared_ptr<srpc::IModuleContext> AclModule::getOperationalContext()
{
    return m_operContext;
}


std::shared_ptr<srpc::IModuleContext> AclModule::getModuleChangesContext()
{
    return m_changeContext;
}


std::shared_ptr<srpc::IModuleContext> AclModule::getRpcContext()
{
    return m_rpcContext;
}


std::list<srpc::OperationalCallback> AclModule::getOperationalCallbacks()
{
    //TODO
    return std::list<srpc::OperationalCallback>();
}

std::list<srpc::ModuleChangeCallback> AclModule::getModuleChangeCallbacks()
{
    //TODO
    return {
        srpc::ModuleChangeCallback {
            "ietf-access-control-list",
            "/ietf-access-control-list:acls/acl",
            ietf::acl::sub::change::AclModuleChangeCb(m_changeContext),
        },
    };
}

std::list<srpc::RpcCallback> AclModule::getRpcCallbacks()
{
    //TODO
    return std::list<srpc::RpcCallback>();
}

constexpr const char* AclModule::getName() {return "ACL Module";}
