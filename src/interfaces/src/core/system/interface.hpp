#pragma once

#include <string>
#include <stdexcept>
#include <netlink/route/link.h>
#include "IPV4.hpp"

// all previous headers in case something is missing
/*
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <netlink/netlink.h>
#include <netlink/route/link.h>
#include <netlink/route/addr.h>
#include <netlink/route/neighbour.h>
#include <linux/if.h>
*/

class Interface {
private:
    int ifindex;

public:
    // creation of a new interface
    static void create(std::string name, std::string type, bool enabled = true);
    // disable copy and move constructors
    Interface();

    Interface(const Interface&);

    // Disable move constructor
    Interface(Interface&&);

    Interface(int ifindex);

    std::string getName();

    bool getEnabled();

    std::string getType();

    IPV4 getIPV4();

    void setMTU(unsigned int mtu);

    int getMTU();

    void setEnabled(bool enabled);

    void setName(std::string name);

    void setType(std::string type);

    void remove();

    int getOperStatus();
};

int getIfindexFromName(std::string name);

std::vector<int> getInterfaces();