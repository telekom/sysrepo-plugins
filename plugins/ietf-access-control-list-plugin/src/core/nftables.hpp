#pragma once

#include <nlohmann/json.hpp>
#include <nftables/libnftables.h>
#include <exception>
#include <string>

class NFTablesCommandExecException : public std::exception {
    public:
        NFTablesCommandExecException(const std::string what){
            this->m_what = what;
        }
        const char* what(){
            return m_what.c_str();
        }
    private:
        std::string m_what;
};

class NFTables {

    public:
    NFTables();

    std::string dumpJSON();

    ~NFTables();

    private:
    nft_ctx* m_ctx;
};
