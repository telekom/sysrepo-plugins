#pragma once

#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Connection.hpp>

namespace srpc
{
/**
 * @brief Base of the plugin context. Each plugin context can inherit the given class and add its own properties to it
 * but must maintain the base properties.
 */
class BasePluginContext
{
  public:
    /**
     * Default constructor.
     *
     * @param sess Plugin session from the plugin init callback.
     *
     */
    BasePluginContext(sysrepo::Session sess);

    /**
     * @brief Get the session by which the plugin was created.
     *
     * @return Plugin session from the init callback.
     *
     */
    sysrepo::Session &getSession();

    /**
     * @brief Get the sysrepo connection.
     *
     * @return Connection to sysrepo.
     *
     */
    sysrepo::Connection getConnection();

    /**
     * @brief Get the subscription handle.
     *
     * @return Subscription handle.
     *
     */
    std::optional<sysrepo::Subscription> &getSubscriptionHandle();

    /**
     * @brief Get the name of the plugin which uses this context.
     *
     * @return Plugin name string.
     */
    virtual constexpr const char *getPluginName() = 0;

    /**
     * sysrepo-plugin-generator: Generated default destructor for plugin context.
     */
    ~BasePluginContext()
    {
    }

  private:
    sysrepo::Session m_sess; ///< Plugin session from the plugin init callback.
    std::optional<sysrepo::Subscription>
        m_subHandle; ///< Subscription handle used for creating subscriptions (change, oper and RPC).
};

/**
 * @brief Context concept used for determining valid context type at compile time.
 */
template <typename T>
concept PluginContext = std::is_base_of<BasePluginContext, T>::value;
} // namespace srpc
