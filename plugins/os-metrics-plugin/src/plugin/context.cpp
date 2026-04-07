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

#include "context.hpp"

namespace metrics {

PluginContext::PluginContext(sysrepo::Session sess)
    : srpc::BasePluginContext(sess)
{
}

PluginContext::~PluginContext() { }

} // namespace metrics
