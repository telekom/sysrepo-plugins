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

#include "ntp.hpp"

ietf::sys::ntp::NTP::NTP(const std::string& file_path) {
    //open the ntp.conf file for reading only
    this->path = file_path;

    error_flag = false;

    file.open(file_path, std::ios::in);
    temp_filepath = file_path + "temp";

    //open temporary file for writing
    temp_file.open(temp_filepath, std::ios::out | std::ios::app);

    if (!file.is_open()) {
        raiseError();
        throw NtpFileException();
    }

    if (!temp_file.is_open()) {
        raiseError();
        throw NtpFileException();
    }

    readServersFromFile();
};

ietf::sys::ntp::NTP::~NTP() {
    if (!error_flag)
        applyChanges();

    file.close();
    temp_file.close();

    if (!error_flag) {
        std::rename(temp_filepath.c_str(), path.c_str());
    }
    else {
        std::remove(temp_filepath.c_str());
    };

};

void ietf::sys::ntp::NTP::addServer(const NTPServer& server) {
    this->servers.push_back(server);
}

void ietf::sys::ntp::NTP::clearServers() {
    servers.clear();
}

bool ietf::sys::ntp::NTP::removeServer(const NTPServer& server, NTPServerRemoveOpts opt) {
    bool deleted = false;

    for (auto it = servers.begin(); it != servers.end();) {
        if (*it <=> server) {
            servers.erase(it);
            deleted = true;
            if (opt == FIRST_MATCHING)
                break;
        }
        else
            it++;
    }
    return deleted;
}

void ietf::sys::ntp::NTP::applyChanges() {

    for (NTPServer server : servers) {
        temp_file << parseAssocToString(server.getServerAssociationType()) << " " << server.getNTPServer();

        if (server.is_iburst()) temp_file << " iburst";
        if (server.is_prefer()) temp_file << " prefer";

        temp_file << std::endl;
    }
}

std::vector<ietf::sys::ntp::NTPServer> ietf::sys::ntp::NTP::getNTPServersList() {
    return servers;
}

ietf::sys::ntp::NTPServerAssociationType ietf::sys::ntp::NTP::parseAssocFromString(const std::string& assoc_type) {
    if (assoc_type == "pool") {
        return ietf::sys::ntp::NTPServerAssociationType::POOL;
    }
    else if (assoc_type == "peer") {
        return ietf::sys::ntp::NTPServerAssociationType::PEER;
    }
    else if (assoc_type == "server") {
        return ietf::sys::ntp::NTPServerAssociationType::SERVER;
    }
    else {
        throw NtpUnknownAssociationTypeException();
    }
}

std::string ietf::sys::ntp::NTP::parseAssocToString(NTPServerAssociationType assoc_type) {

    switch (assoc_type) {
    case POOL:
        return "pool";
    case PEER:
        return "peer";
    case SERVER:
        return "server";
    default:
        throw NtpUnknownAssociationTypeException();
    }
}

void ietf::sys::ntp::NTP::raiseError() {
    error_flag = true;
};

void ietf::sys::ntp::NTP::readServersFromFile() {
    std::string input_line;

    while (std::getline(file, input_line)) {
        if (input_line.rfind("pool", 0) == 0 || input_line.rfind("server", 0) == 0 || input_line.rfind("peer", 0) == 0) {
            // server found
            bool iburst = false;
            bool prefer = false;

            std::string assoc_type;
            std::string server;

            NTPServerAssociationType assoctype;
            std::string servername;
            std::string bulk;
            std::vector<std::string> params;
            std::string param;

            std::istringstream server_stream(input_line);

            server_stream >> assoc_type >> server;
            assoctype = parseAssocFromString(assoc_type);

            while (server_stream >> param) {
                params.push_back(param);
            }
            //now lets construct the NTPServer object
            for (const std::string& arg : params) {
                if (arg == "iburst") iburst = true;
                if (arg == "prefer") prefer = true;
                if (arg.rfind("#$servername$%:")) {
                    std::istringstream(param) >> bulk >> servername;
                }
            }
            // here we have some other params like iburst prefer name etc

            std::optional<std::string> srv_opt_name;
            servername.empty() ? srv_opt_name = std::nullopt : srv_opt_name = servername;
            servers.push_back(NTPServer(assoctype, server, iburst, prefer, srv_opt_name));
        }
        else {
            temp_file << input_line << std::endl;
        }
    }
}

ietf::sys::ntp::NTPServer::NTPServer(NTPServerAssociationType assoc_type, const std::string& server, bool iburst, bool prefer, const std::optional<std::string>& name = std::nullopt)
    : m_assoc_type(assoc_type),
    m_server(server),
    m_iburst(iburst),
    m_prefer(prefer),
    m_name(name)
{};

std::string ietf::sys::ntp::NTPServer::getNTPServer() {
    return m_server;
}

bool ietf::sys::ntp::NTPServer::operator<(const NTPServer& other)const {
    return (m_server.compare(other.m_server) < 0);
}

bool ietf::sys::ntp::NTPServer::operator==(const NTPServer& other)const {
    return (m_server.compare(other.m_server) == 0);
}

//strict comparation
bool ietf::sys::ntp::NTPServer::operator<=>(const NTPServer& other)const {
    return ((m_server.compare(other.m_server) == 0) &&
        (m_assoc_type == other.m_assoc_type) &&
        (m_iburst == other.m_iburst) &&
        (m_prefer == other.m_prefer)
        );
}

ietf::sys::ntp::NTPServerAssociationType ietf::sys::ntp::NTPServer::getServerAssociationType() {
    return m_assoc_type;
}

bool ietf::sys::ntp::NTPServer::is_iburst() {
    return m_iburst;
}

bool ietf::sys::ntp::NTPServer::is_prefer() {
    return m_prefer;
}

std::optional<std::string> ietf::sys::ntp::NTPServer::getServerName() {
    return m_name;
}

// NTPSdbus derived class that contains dbus interface, NTP class with constructor file path /etc/ntp.conf
//"org.freedesktop.systemd1", "/org/freedesktop/systemd1", "org.freedesktop.systemd1.Manager", "Version", "RestartUnit"
ietf::sys::ntp::NTPDbus::NTPDbus() : NTP("/etc/ntp.conf"), ietf::sys::SdBus<std::string, std::string, std::string>("org.freedesktop.systemd1", "/org/freedesktop/systemd1", "org.freedesktop.systemd1.Manager", "RestartUnit", "Version") {};

void ietf::sys::ntp::NTPDbus::restartNTP() {
    this->exportToSdBus("ntp.service", "replace");
}

//NTPState class that manipulates and gets the state on ntp.servive enabled and disabled state
ietf::sys::ntp::NTPState::NTPState() {
    m_connection = sdbus::createSystemBusConnection();
    sdbus::ServiceName m_srvc_name = sdbus::ServiceName(M_DESTINATION);
    sdbus::ObjectPath m_obj_path = sdbus::ObjectPath(M_OBJ_PATH);
    m_proxy = sdbus::createProxy(*m_connection, m_srvc_name, m_obj_path);
};

void ietf::sys::ntp::NTPState::ntpSetState(bool state) {
    m_proxy->callMethod((state ? "Start" : "Stop")).onInterface(M_INTERFACE).withArguments(M_PARAM).dontExpectReply();
};

bool ietf::sys::ntp::NTPState::ntpGetState() {
    sdbus::Variant var;
    //M_INTERFACE is the interface as a parameter
    m_proxy->callMethod(M_GET_METHOD).onInterface(M_GET_INTERFACE).withArguments(M_INTERFACE, M_UNIT_STATE_METHOD).storeResultsTo(var);
    std::string active = var.get<std::string>();
    if (active == "active") {
        return true;
    }
    else return false;
};