#pragma once

#include <fstream>
#include <string>
#include <exception>
#include <vector>
#include <set>
#include <optional>
#include <sstream>
#include "plugin/sdbus.hpp"

namespace ietf::sys::ntp {

    enum NTPServerAssociationType {
        POOL,
        SERVER,
        PEER
    };

    enum NTPServerRemoveOpts {
        ALL_MATCHING,
        FIRST_MATCHING
    };

    class NTPServer {

    public:
        NTPServer(NTPServerAssociationType, const std::string&, bool, bool, const std::optional<std::string>&);

        // no default constructor;
        NTPServer() = delete;

        //NTPServer(const NTPServer&) = delete;
        //NTPServer(const NTPServer&&) = delete;

        NTPServerAssociationType getServerAssociationType();
        std::optional<std::string> getServerName();
        std::string getNTPServer();
        bool is_iburst();
        bool is_prefer();

        bool operator<(const NTPServer&)const;

        bool operator==(const NTPServer&)const;

        //strict comparation
        bool operator<=>(const NTPServer&)const;
    private:
        NTPServerAssociationType m_assoc_type;
        std::string m_server;
        bool m_iburst;
        bool m_prefer;
        std::optional<std::string> m_name;
    };

    class NtpFileException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error opening file!";
        }
    };

    class NtpEraseException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Failed to erase NTP server!";
        }
    };

    class NtpUnknownAssociationTypeException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Unknown NTP association type!";
        }
    };

    class NTP {

    public:
        NTP(const std::string&);

        //copy constructor is not permited
        NTP(const NTP&) = delete;

        //move constructor is not permited
        NTP(const NTP&&) = delete;

        void addServer(const NTPServer&);
        bool removeServer(const NTPServer&, NTPServerRemoveOpts);

        //this method will not apply changes if somewhere along the way error happens
        void raiseError();

        std::vector<NTPServer> getNTPServersList();

        static NTPServerAssociationType parseAssocFromString(const std::string&);
        static std::string parseAssocToString(NTPServerAssociationType);

        void clearServers();

        virtual ~NTP();

    private:

        void readServersFromFile();

        void applyChanges();

        std::fstream file;
        std::fstream temp_file;

        std::string path;
        std::string temp_filepath;

        std::vector<NTPServer> servers;

        bool error_flag;
    };

    // 

    class NTPDbus : public NTP, public ietf::sys::SdBus<std::string, std::string, std::string> {
    public:
        NTPDbus();        
        
        void restartNTP();
        
    };

}
