#include "context.hpp"

namespace ieee::br {
/**
 * @brief Default constructor.
 *
 * @param sess Plugin session from the plugin init callback.
 *
 */
PluginContext::PluginContext(sysrepo::Session sess)
    : srpc::BasePluginContext(sess)
{
}

/**
 * @brief Default destructor.
 */
PluginContext::~PluginContext() { }
}
