// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
 * @file ReaderAttributes.h
 *
 */

#ifndef _FASTDDS_RTPS_ATTRIBUTES_READERATTRIBUTES_H_
#define _FASTDDS_RTPS_ATTRIBUTES_READERATTRIBUTES_H_

#include <fastdds/dds/core/policy/QosPolicies.hpp>
#include <fastdds/rtps/attributes/EndpointAttributes.h>
#include <fastdds/rtps/attributes/ThreadSettings.hpp>
#include <fastdds/rtps/common/Time_t.h>
#include <fastdds/utils/collections/ResourceLimitedContainerConfig.hpp>

namespace eprosima {
namespace fastrtps {
namespace rtps {

/**
 * Class ReaderTimes, defining the times associated with the Reliable Readers events.
 * @ingroup RTPS_ATTRIBUTES_MODULE
 */
class ReaderTimes
{
public:

    ReaderTimes()
    {
        initialAcknackDelay.nanosec = 70 * 1000 * 1000;
        heartbeatResponseDelay.nanosec = 5 * 1000 * 1000;
    }

    virtual ~ReaderTimes()
    {
    }

    bool operator ==(
            const ReaderTimes& b) const
    {
        return (this->initialAcknackDelay == b.initialAcknackDelay)  &&
               (this->heartbeatResponseDelay == b.heartbeatResponseDelay);
    }

    //!Initial AckNack delay. Default value 70ms.
    Duration_t initialAcknackDelay;
    //!Delay to be applied when a HEARTBEAT message is received, default value 5ms.
    Duration_t heartbeatResponseDelay;
};

/**
 * Class ReaderAttributes, to define the attributes of a RTPSReader.
 * @ingroup RTPS_ATTRIBUTES_MODULE
 */
class ReaderAttributes
{
public:

    ReaderAttributes()
        : liveliness_kind_(fastdds::dds::LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS)
        , liveliness_lease_duration(TIME_T_INFINITE_SECONDS, TIME_T_INFINITE_NANOSECONDS)
        , expectsInlineQos(false)
        , disable_positive_acks(false)
    {
        endpoint.endpointKind = READER;
        endpoint.durabilityKind = VOLATILE;
        endpoint.reliabilityKind = BEST_EFFORT;
    }

    virtual ~ReaderAttributes()
    {
    }

    //!Attributes of the associated endpoint.
    EndpointAttributes endpoint;

    //!Times associated with this reader (only for stateful readers)
    ReaderTimes times;

    //! Liveliness kind
    fastdds::dds::LivelinessQosPolicyKind liveliness_kind_;

    //! Liveliness lease duration
    Duration_t liveliness_lease_duration;

    //!Indicates if the reader expects Inline qos, default value 0.
    bool expectsInlineQos;

    //! Disable positive ACKs
    bool disable_positive_acks;

    //! Define the allocation behaviour for matched-writer-dependent collections.
    ResourceLimitedContainerConfig matched_writers_allocation;

    //! Thread settings for the data-sharing listener thread
    fastdds::rtps::ThreadSettings data_sharing_listener_thread;
};

} /* namespace rtps */
} /* namespace fastrtps */
} /* namespace eprosima */

#endif /* _FASTDDS_RTPS_ATTRIBUTES_READERATTRIBUTES_H_ */
