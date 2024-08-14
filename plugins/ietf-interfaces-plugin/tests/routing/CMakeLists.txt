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

set(ROUTING_UTEST_NAME "routing_utest")

add_executable(
    ${ROUTING_UTEST_NAME}

    "routing_utest.c"
)
target_include_directories(
    ${ROUTING_UTEST_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/src/routing/src
)
target_link_libraries(
    ${ROUTING_UTEST_NAME}

	${CMOCKA_LIBRARIES}
	${SYSREPO_LIBRARIES}
	${LIBYANG_LIBRARIES}
)
add_test(
    NAME ${ROUTING_UTEST_NAME}
    COMMAND routing_utest
)
