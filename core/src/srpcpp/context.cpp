#include "context.hpp"

namespace srpc
{
/**
 * Default constructor.
 *
 * @param sess Plugin session from the plugin init callback.
 *
 */
BasePluginContext::BasePluginContext(sysrepo::Session sess) : m_sess(sess)
{
}

/**
 * @brief Get the session by which the plugin was created.
 *
 * @return Plugin session from the init callback.
 *
 */
sysrepo::Session &BasePluginContext::getSession()
{
    return m_sess;
}

/**
 * @brief Get the sysrepo connection.
 *
 * @return Connection to sysrepo.
 *
 */
sysrepo::Connection BasePluginContext::getConnection()
{
    return m_sess.getConnection();
}

/**
 * @brief Get the subscription handle.
 *
 * @return Subscription handle.
 *
 */
std::optional<sysrepo::Subscription> &BasePluginContext::getSubscriptionHandle()
{
    return m_subHandle;
}

} // namespace srpc
