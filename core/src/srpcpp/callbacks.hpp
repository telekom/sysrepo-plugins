#pragma once

#include <string>
#include <sysrepo-cpp/Session.hpp>

namespace srpc
{
/**
 * @brief Operational callback struct.
 */
struct OperationalCallback
{
    std::string Module;          ///< Module for the callback.
    std::string XPath;           ///< XPath of the data.
    sysrepo::OperGetCb Callback; ///< Callback function.
};

/**
 * @brief Module change callback struct.
 */
struct ModuleChangeCallback
{
    std::string Module;               ///< Module for the callback.
    std::string XPath;                ///< XPath of the data.
    sysrepo::ModuleChangeCb Callback; ///< Callback function.
};

/**
 * @brief RPC callback struct.
 */
struct RpcCallback
{
    std::string XPath;             ///< XPath of the data.
    sysrepo::RpcActionCb Callback; ///< Callback function.
};
} // namespace srpc
