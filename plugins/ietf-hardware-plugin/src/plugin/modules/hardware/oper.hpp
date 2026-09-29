//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#pragma once

#include "context.hpp"

#include <optional>
#include <string_view>

#include <sysrepo-cpp/Session.hpp>
#include <libyang-cpp/Context.hpp>

namespace sr = sysrepo;
namespace ly = libyang;

namespace ietf::hw {
namespace sub::oper {
    /**
     * @brief Operational get functor for path /ietf-hardware:hardware.
     */
    class HardwareOperGetCb {
    public:
        /**
         * Default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        HardwareOperGetCb(std::shared_ptr<HardwareOperationalContext> ctx);

        /**
         * Operational get operator() for path /ietf-hardware:hardware.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param requestXPath The optional xpath of the request.
         * @param requestId Request ID unique for the specific module_name.
         * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
            std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<HardwareOperationalContext> m_ctx;
    };
}
}
