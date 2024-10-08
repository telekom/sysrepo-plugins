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

#include <sdbus-c++/sdbus-c++.h>
#include <string>

// error messages
#include <sysrepo.h>

namespace ietf::sys {

// [TODO]: Document this class
template <class GET, class... SET>
class SdBus {
public:
    SdBus(std::string destination, std::string objectPath, std::string interface, std::string set_method, std::string property)
        : m_dest(destination)
        , m_objPath(objectPath)
        , m_interface(interface)
        , m_setMethod(set_method)
        , m_property(property)
    {
        m_connection = sdbus::createSystemBusConnection();
        m_srvc_name = sdbus::ServiceName(m_dest);
        m_obj_path = sdbus::ObjectPath(m_objPath);
    }

protected:
    void exportToSdBus(SET... data)
    {

        try {
            auto proxy = sdbus::createProxy(*m_connection ,m_srvc_name, m_obj_path);
            proxy->callMethod(m_setMethod).onInterface(m_interface).withArguments(data...);
        } catch (sdbus::Error& e) {
            SRPLG_LOG_ERR("sd-bus", "Error exporting data to sd-bus: %s", e.what());
            throw std::runtime_error(e.getMessage());
        };
    }

    GET importFromSdBus()
    {
        GET data;

        try {
            auto proxy = sdbus::createProxy(*m_connection, m_srvc_name, m_obj_path);
            sdbus::Variant v = proxy->getProperty(m_property).onInterface(m_interface);
            data = v.get<GET>();
        } catch (sdbus::Error& e) {
            SRPLG_LOG_ERR("sd-bus", "Error importing data from sd-bus: %s", e.what());
            throw std::runtime_error(e.getMessage());
        }

        return data;
    }

private:
    std::string m_dest;
    std::string m_objPath;
    std::string m_interface;
    std::string m_setMethod;
    std::string m_property;
    std::unique_ptr<sdbus::IConnection> m_connection;
    sdbus::ServiceName m_srvc_name;
    sdbus::ObjectPath m_obj_path;
};
}
