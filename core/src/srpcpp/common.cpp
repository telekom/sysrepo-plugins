#include "common.hpp"

#include <regex>

namespace srpc {
/**
 * @brief Extracts the key from the list XPath.
 *
 * @param list List name.
 * @param key Key name.
 * @param xpath XPath of the list.
 * @return std::string Key value.
 */
const std::string extractListKeyFromXPath(const std::string& list, const std::string& key, const std::string& xpath)
{
    std::string value;

    std::stringstream ss;

    ss << list << "\\[" << key << "='([^']*)'\\]";

    const auto& xpath_expr = ss.str();

    std::regex re(xpath_expr);
    std::smatch xpath_match;

    if (std::regex_search(xpath, xpath_match, re)) {
        value = xpath_match[1];
    } else {
        throw std::runtime_error("Failed to extract key from XPath.");
    }

    return value;
}

/**
 * @brief Extracts all the keys from the list XPath by list name.
 *
 * @param list List name.
 * @param xpath XPath of the list.
 * @return std::unordered_map<std::string, std::string> Key values.
 */
std::unordered_map<std::string, std::string> extractListKeysFromXpath(const std::string& list, const std::string& xpath)
{
    std::unordered_map<std::string, std::string> keys_map;

    int starting_point = xpath.find(list + "[");
    
    std::string chunk(xpath.begin() + starting_point, xpath.end());
    
    int ending_point = chunk.find("]/");

    if(ending_point == std::string::npos){
        //this means it can be last
        ending_point = chunk.find_last_of(']');
    }
    
    chunk.erase(chunk.begin() + ending_point + 1, chunk.end());
    
    int begin = chunk.find('[');
    int end = chunk.find(']');
    // list is found, continue

    while (begin != std::string::npos || end != std::string::npos) {

        std::string mapstr(++chunk.begin() + begin, chunk.begin() + end);
        chunk.erase(begin, ++end - begin);

        // now split it by '=' in key value

        int eq_pos = mapstr.find('=');

        if (eq_pos == std::string::npos) {
            throw std::runtime_error("Failed to parse '=' sympol");
        }

        std::string key(mapstr.begin(), mapstr.begin() + eq_pos);
        // value shrink by one place begin to end to eliminate ' '
        std::string value(mapstr.begin() + eq_pos + 2, --mapstr.end());

        keys_map.insert(std::make_pair(key, value));

        begin = chunk.find('[');
        end = chunk.find(']');
    }

    return keys_map;
}

/**
 * @brief Get meta value.
 *
 * @param meta Meta collection object.
 * @param name Meta name.
 * @return std::string Meta value.
 */
const std::string getMetaValue(const ly::MetaCollection& meta, const std::string& name)
{
    for (const auto& m : meta) {
        if (m.name() == name) {
            return m.valueStr();
        }
    }
    throw std::runtime_error("Failed to get meta value.");
}

/**
 * @brief Convert meta values list to a hash.
 *
 * @param meta Meta collection object.
 * @return std::map<std::string, std::string> Meta values hash.
 */
std::map<std::string, std::string> getMetaValuesHash(const ly::MetaCollection meta)
{
    std::map<std::string, std::string> hash;

    for (const auto& m : meta) {
        hash[m.name()] = m.valueStr();
    }

    return hash;
}
} // namespace srpc
