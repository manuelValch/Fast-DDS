// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file ServerAttributes.h
 *
 */

#ifndef _FASTDDS_SERVERATTRIBUTES_H_
#define _FASTDDS_SERVERATTRIBUTES_H_
#ifndef DOXYGEN_SHOULD_SKIP_THIS_PUBLIC

#include <fastdds/rtps/common/Guid.h>
#include <fastdds/rtps/common/LocatorList.hpp>

#include <algorithm>
#include <iterator>
#include <list>

namespace eprosima {

namespace fastrtps {
namespace rtps {
class ParticipantProxyData;
} // fastrtps
} // rtps

namespace fastdds {
namespace rtps {

/**
 * Class RemoteServerAttributes, to define the attributes of the Discovery Server Protocol.
 * @ingroup RTPS_ATTRIBUTES_MODULE
 */

class RemoteServerAttributes
{
public:

    FASTDDS_EXPORTED_API inline bool operator ==(
            const RemoteServerAttributes& r) const
    {
        return guidPrefix == r.guidPrefix
               && metatrafficUnicastLocatorList == r.metatrafficUnicastLocatorList
               && metatrafficMulticastLocatorList == r.metatrafficMulticastLocatorList;
    }

    FASTDDS_EXPORTED_API void clear()
    {
        guidPrefix = fastrtps::rtps::GuidPrefix_t::unknown();
        metatrafficUnicastLocatorList.clear();
        metatrafficMulticastLocatorList.clear();
        is_connected = false;
    }

    FASTDDS_EXPORTED_API fastrtps::rtps::GUID_t GetParticipant() const;

    FASTDDS_EXPORTED_API fastrtps::rtps::GUID_t GetPDPReader() const;
    FASTDDS_EXPORTED_API fastrtps::rtps::GUID_t GetPDPWriter() const;

    FASTDDS_EXPORTED_API inline bool ReadguidPrefix(
            const char* pfx)
    {
        return bool(std::istringstream(pfx) >> guidPrefix);
    }

    //!Metatraffic Unicast Locator List
    LocatorList metatrafficUnicastLocatorList;
    //!Metatraffic Multicast Locator List.
    LocatorList metatrafficMulticastLocatorList;

    //!Guid prefix
    fastrtps::rtps::GuidPrefix_t guidPrefix;

    // Whether connection has been established
    bool is_connected = false;

    // Check if there are specific transport locators associated
    // the template parameter is the locator kind (e.g. LOCATOR_KIND_UDPv4)
    template<int kind> bool requires_transport() const
    {
        return metatrafficUnicastLocatorList.has_kind<kind>() ||
               metatrafficMulticastLocatorList.has_kind<kind>();
    }

};

typedef std::list<RemoteServerAttributes> RemoteServerList_t;

template<class charT>
struct server_ostream_separators
{
    FASTDDS_EXPORTED_API static const charT* list_separator;
    FASTDDS_EXPORTED_API static const charT* locator_separator;
};

#ifndef _MSC_VER
template<> const char* server_ostream_separators<char>::list_separator;
template<> const wchar_t* server_ostream_separators<wchar_t>::list_separator;

template<> const char* server_ostream_separators<char>::locator_separator;
template<> const wchar_t* server_ostream_separators<wchar_t>::locator_separator;
#endif // _MSC_VER

template<class charT>
std::basic_ostream<charT>& operator <<(
        std::basic_ostream<charT>& output,
        const RemoteServerAttributes& sa)
{
    typename std::basic_ostream<charT>::sentry s(output);
    output << sa.guidPrefix;
    if (!sa.metatrafficUnicastLocatorList.empty())
    {
        output << server_ostream_separators<charT>::locator_separator << sa.metatrafficUnicastLocatorList;
    }
    if (!sa.metatrafficMulticastLocatorList.empty())
    {
        output << server_ostream_separators<charT>::locator_separator << sa.metatrafficMulticastLocatorList;
    }
    return output;
}

template<class charT>
std::basic_ostream<charT>& operator <<(
        std::basic_ostream<charT>& output,
        const RemoteServerList_t& list)
{
    typename std::basic_ostream<charT>::sentry s(output);
    std::ostream_iterator<RemoteServerAttributes> os_iterator(output, server_ostream_separators<charT>::list_separator);
    std::copy(list.begin(), list.end(), os_iterator);
    return output;
}

// port used if the ros environment variable doesn't specify one
constexpr uint16_t DEFAULT_ROS2_SERVER_PORT = 11811;
// default server base guidPrefix
const char* const DEFAULT_ROS2_SERVER_GUIDPREFIX = "44.53.00.5f.45.50.52.4f.53.49.4d.41";
// port used by default for tcp transport
constexpr uint16_t DEFAULT_TCP_SERVER_PORT = 42100;

/* Environment variable to specify a semicolon-separated list of UDPv4 locators (ip:port) that define remote server
 * locators.
 * The position in the list is used as a "server id" to extrapolate the server's GUID prefix.
 * For the variable to take any effect, the following pre-conditions must be met:
 *    1. The server's GUID prefix must be compliant with the schema
 *       "44.53.<server_id_in_hex>.5f.45.50.52.4f.53.49.4d.41", which is the schema followed by the prefixes generated
 *        when creating server using fastdds cli, being DEFAULT_ROS2_SERVER_GUIDPREFIX the prefix for ID=0.
 *    1. The discovery protocol must be either SIMPLE or SERVER.
 *       1. In the case of SIMPLE, the participant is created as a CLIENT instead.
 *       1. In the case of SERVER, the participant is created as a SERVER, using the DEFAULT_ROS2_MASTER_URI list to
 *          expand the list of remote servers.
 */
const char* const DEFAULT_ROS2_MASTER_URI = "ROS_DISCOVERY_SERVER";

/* Environment variable to transform a SIMPLE participant in a SUPER CLIENT.
 * If the participant is not SIMPLE, the variable doesn't have any effects.
 * The variable can assume the following values:
 *    - FALSE, false, False, 0
 *    - TRUE, true, True, 1
 * If the variable is not set, the program will behave like the variable is set to false.
 */
const char* const ROS_SUPER_CLIENT = "ROS_SUPER_CLIENT";

/**
 * Retrieves a semicolon-separated list of locators from a string, and
 * populates a RemoteServerList_t mapping list position to default guid.
 * @param[in] list servers listening locator list.
 * @param[out] attributes reference to a RemoteServerList_t to populate.
 * @return true if parsing succeeds, false otherwise (or if the list is empty)
 */
FASTDDS_EXPORTED_API bool load_environment_server_info(
        const std::string& list,
        RemoteServerList_t& attributes);

/**
 * Retrieves a semicolon-separated list of locators from DEFAULT_ROS2_MASTER_URI environment variable, and
 * populates a RemoteServerList_t mapping list position to default guid.
 *
 * The environment variable can be read from an environment file (which allows runtime modification of the remote
 * servers list) or directly from the environment.
 * The value contained in the file takes precedence over the environment value (if both are set).
 * This is to avoid conflicts because only new servers can be added to the list (containing thus all the previously
 * known servers).
 *
 * @param[out] attributes reference to a RemoteServerList_t to populate.
 * @return true if parsing succeeds, false otherwise
 */
FASTDDS_EXPORTED_API bool load_environment_server_info(
        RemoteServerList_t& attributes);

/**
 * Get the value of environment variable DEFAULT_ROS2_MASTER_URI
 * @return The value of environment variable DEFAULT_ROS2_MASTER_URI. Empty string if the variable is not defined.
 */
FASTDDS_EXPORTED_API const std::string& ros_discovery_server_env();

/**
 * Get the value of environment variable ROS_SUPER_CLIENT
 * @return The value of environment variable ROS_SUPER_CLIENT. False if the variable is not defined.
 */
FASTDDS_EXPORTED_API bool ros_super_client_env();

/**
 * Returns the guidPrefix associated to the given server id
 * @param[in] id of the default server whose guidPrefix we want to retrieve
 * @param[out] guid reference to the guidPrefix to modify
 * @return true if the server guid can be delivered
 */
FASTDDS_EXPORTED_API bool get_server_client_default_guidPrefix(
        int id,
        fastrtps::rtps::GuidPrefix_t& guid);

} // namespace rtps
} // namespace fastdds

// keep former namespace references available
namespace fastrtps {
namespace rtps {

using fastdds::rtps::RemoteServerAttributes;
using fastdds::rtps::RemoteServerList_t;
using fastdds::rtps::DEFAULT_ROS2_SERVER_PORT;
using fastdds::rtps::DEFAULT_ROS2_SERVER_GUIDPREFIX;
using fastdds::rtps::DEFAULT_ROS2_MASTER_URI;
using fastdds::rtps::ROS_SUPER_CLIENT;
using fastdds::rtps::load_environment_server_info;
using fastdds::rtps::ros_discovery_server_env;
using fastdds::rtps::get_server_client_default_guidPrefix;
using fastdds::rtps::ros_super_client_env;

} // fastrtps
} // rtps

} // namespace eprosima

#endif // DOXYGEN_SHOULD_SKIP_THIS_PUBLIC
#endif /* _FASTDDS_SERVERATTRIBUTES_H_ */
