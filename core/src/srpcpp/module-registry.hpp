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

#pragma once

#include "module.hpp"
#include "context.hpp"

#include <typeindex>
#include <map>
#include <memory>
#include <list>

namespace srpc
{
template <PluginContext PluginContextType> using ModuleList = std::list<std::unique_ptr<IModule<PluginContextType>>>;

/**
 * @brief Module registry. Singleton class for creating and getting modules.
 */
template <PluginContext PluginContextType> class ModuleRegistry
{
  public:
    /**
     * Return the singleton instance of the class.
     */
    static ModuleRegistry<PluginContextType> &getInstance()
    {
        static ModuleRegistry<PluginContextType> reg;
        return reg;
    }

    /**
     * Register a module.
     */
    template <PluginModule<PluginContextType> ModuleType> size_t registerModule(PluginContextType &plugin_ctx)
    {
        m_modules.push_back(std::make_unique<ModuleType>(plugin_ctx));
        return m_modules.size() - 1;
    }

    /**
     * Returns the list of registered modules.
     */
    ModuleList<PluginContextType> &getRegisteredModules()
    {
        return m_modules;
    }

  private:
    ModuleRegistry() = default;
    ~ModuleRegistry() = default;
    ModuleList<PluginContextType> m_modules;
};

} // namespace srpc
