#
# telekom / sysrepo-plugins
#
# This program is made available under the terms of the
# BSD 3-Clause license which is available at
# https://opensource.org/licenses/BSD-3-Clause
#
# SPDX-FileCopyrightText: 2024 Deutsche Telekom AG
# SPDX-FileContributor: Sartura d.d.
#
# SPDX-License-Identifier: BSD-3-Clause
#

from robot.api.deco import keyword


ROBOT_AUTO_KEYWORDS = False


@keyword('Create Dict From Lists')
def create_dict_from_lists(keys, values):
    return dict(zip(keys, values))

@keyword('Format String')
def format_str(string, *args, **kwargs):
    return string.format(*args, **kwargs)

