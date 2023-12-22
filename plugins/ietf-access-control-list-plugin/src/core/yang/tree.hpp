#pragma once

#include <optional>
#include <string>

#include <libyang-cpp/DataNode.hpp>

namespace ly = libyang;

namespace ietf::acl {
namespace yang::tree {
    /**
     * sysrepo-plugin-generator: Generated yang tree function for path /ietf-access-control-list:acls
     *
     * @return Returns the first created node. If no nodes were created, returns std::nullopt.
     *
     */
    std::optional<ly::DataNode> createAclsContainer();

    /**
     * sysrepo-plugin-generator: Generated yang tree function for path /ietf-access-control-list:acls/attachment-points
     *
     * @param acls Parent of the node being created.
     *
     * @return Returns the first created node. If no nodes were created, returns std::nullopt.
     *
     */
    std::optional<ly::DataNode> createAttachmentPointsContainer(ly::DataNode& acls);

    /**
     * sysrepo-plugin-generator: Generated yang tree function for path /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']
     *
     * @param attachment_points Parent of the node being created.
     * @param interface_id Key value for key interface-id.
     *
     * @return Returns the first created node. If no nodes were created, returns std::nullopt.
     *
     */
    std::optional<ly::DataNode> createInterfaceList(ly::DataNode& attachment_points, const std::string& interface_id);

    /**
     * sysrepo-plugin-generator: Generated yang tree function for path /ietf-access-control-list:acls/acl[name='%s']
     *
     * @param acls Parent of the node being created.
     * @param name Key value for key name.
     *
     * @return Returns the first created node. If no nodes were created, returns std::nullopt.
     *
     */
    std::optional<ly::DataNode> createAclList(ly::DataNode& acls, const std::string& name);

}
}