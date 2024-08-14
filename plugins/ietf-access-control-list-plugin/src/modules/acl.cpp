//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2024 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#include "modules/acl.hpp"
#include "srpcpp/callbacks.hpp"
#include "core/context.hpp"
#include <memory>

AclModule::AclModule(ietf::acl::PluginContext &ctx) : srpc::IModule<ietf::acl::PluginContext>(ctx)
{}

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
    return std::list<srpc::ModuleChangeCallback>();
}

std::list<srpc::RpcCallback> AclModule::getRpcCallbacks()
{
    //TODO
    return std::list<srpc::RpcCallback>();
}

constexpr const char* AclModule::getName() {return "";}
