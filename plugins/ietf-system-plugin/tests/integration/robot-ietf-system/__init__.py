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

import sys
import os


ROBOT_AUTO_KEYWORDS = False


@keyword('Import Root Robot Path')
def import_root_robot_path() -> None:
    sys.path.insert(0, os.path.dirname(__file__))

