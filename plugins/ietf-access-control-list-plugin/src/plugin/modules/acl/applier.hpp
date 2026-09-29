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

#include <srpcpp/datastore.hpp>

#include <sysrepo-cpp/Session.hpp>

/**
 * @brief Applier used to apply /ietf-access-control-list:acls values from the datastore to the system (nftables).
 */
class AclValuesApplier : public srpc::IDatastoreApplier {
public:
    /**
     * @brief Apply datastore content from the provided session to the system.
     *
     * @param session Session to use for retreiving datastore data.
     */
    virtual void applyDatastoreValues(sysrepo::Session& session) override;

    /**
     * @brief Get the paths which the checker/applier is assigned for.
     *
     * @return Assigned paths.
     */
    virtual std::list<std::string> getPaths() override
    {
        return {
            "/ietf-access-control-list:acls",
        };
    }
};
