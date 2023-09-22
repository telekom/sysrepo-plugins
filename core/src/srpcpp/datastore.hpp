#pragma once

#include <sysrepo-cpp/Session.hpp>

namespace srpc
{
class IAssignedPaths
{
  public:
    /**
     * @brief Get the paths which the checker/applier is assigned for.
     *
     * @return Assigned paths.
     */
    virtual std::list<std::string> getPaths() = 0;
};

/**
 * @brief Interface used for applying datastore content to the system.
 */
class IDatastoreApplier : public IAssignedPaths
{
  public:
    /**
     * @brief Apply datastore content from the provided session to the system.
     *
     * @param session Session to use for retreiving datastore data.
     */
    virtual void applyDatastoreValues(sysrepo::Session &session) = 0;
};

/**
 * @brief Enum used for receiving comparison status between datastore values and values found on the system.
 */
enum class DatastoreValuesCheckStatus
{
    Equal,      ///< Values on the system are equal to those in the sysrepo datastore.
    Partial,    ///< Values on the system are partially equal to those in the sysrepo datastore. There are more values
                ///< contained on the system but all values from the datastore are contained on the system.
    NonExistant ///< Values from the datastore do not exist on the system.
};

/**
 * @brief Datastore values checking interface. Each class implementing this interface must check for datastore values on
 * the system and return the status code or throw an exception.
 */
class IDatastoreChecker : public IAssignedPaths
{
  public:
    /**
     * @brief Check for the datastore values on the system.
     *
     * @param session Sysrepo session used for retreiving datastore values.
     *
     * @return Enum describing the output of values comparison.
     */
    virtual DatastoreValuesCheckStatus checkDatastoreValues(sysrepo::Session &session) = 0;
};

/**
 * @brief Datastore checker concept for determining a valid datastore checker.
 */
template <typename T>
concept DatastoreValueApplier = std::is_base_of<IDatastoreApplier, T>::value;

/**
 * @brief Datastore checker concept for determining a valid datastore checker.
 */
template <typename T>
concept DatastoreValueChecker = std::is_base_of<IDatastoreChecker, T>::value;
} // namespace srpc
