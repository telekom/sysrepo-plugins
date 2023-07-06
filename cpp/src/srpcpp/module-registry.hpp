#pragma once

#include "module.hpp"

#include <typeindex>
#include <map>
#include <memory>
#include <list>
#include <iostream>

namespace srpc
{
template <typename PluginContextType> using ModuleList = std::list<std::unique_ptr<IModule<PluginContextType>>>;

/**
 * @brief Module registry. Singleton class for creating and getting modules.
 */
template <typename PluginContextType> class ModuleRegistry
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
    template <typename ModuleType> size_t registerModule(PluginContextType &plugin_ctx)
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
