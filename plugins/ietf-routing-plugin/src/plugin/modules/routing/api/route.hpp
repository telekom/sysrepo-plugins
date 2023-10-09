#pragma once

#include <string>

namespace ietf::rt {
class RoutingInformationBase;

class Route {
public:
private:
    Route(std::string name) { }

    friend RoutingInformationBase;
};
}
