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

#include <sysrepo.h>

extern "C" {
int sr_plugin_init_cb(sr_session_ctx_t *session, void **priv);
void sr_plugin_cleanup_cb(sr_session_ctx_t *session, void *priv);
}