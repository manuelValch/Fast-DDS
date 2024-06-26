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

/*!
 * @file relative_path_include.hpp
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifndef _FAST_DDS_GENERATED_RELATIVE_PATH_INCLUDE_HPP_
#define _FAST_DDS_GENERATED_RELATIVE_PATH_INCLUDE_HPP_

#include <cstdint>
#include <utility>
#include "../IDL/helpers/basic_inner_types.hpp"

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(RELATIVE_PATH_INCLUDE_SOURCE)
#define RELATIVE_PATH_INCLUDE_DllAPI __declspec( dllexport )
#else
#define RELATIVE_PATH_INCLUDE_DllAPI __declspec( dllimport )
#endif // RELATIVE_PATH_INCLUDE_SOURCE
#else
#define RELATIVE_PATH_INCLUDE_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define RELATIVE_PATH_INCLUDE_DllAPI
#endif // _WIN32

/*!
 * @brief This class represents the structure RelativePathIncludeStruct defined by the user in the IDL file.
 * @ingroup relative_path_include
 */
class RelativePathIncludeStruct
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport RelativePathIncludeStruct()
    {
    }

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~RelativePathIncludeStruct()
    {
    }

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object RelativePathIncludeStruct that will be copied.
     */
    eProsima_user_DllExport RelativePathIncludeStruct(
            const RelativePathIncludeStruct& x)
    {
                    m_value = x.m_value;

    }

    /*!
     * @brief Move constructor.
     * @param x Reference to the object RelativePathIncludeStruct that will be copied.
     */
    eProsima_user_DllExport RelativePathIncludeStruct(
            RelativePathIncludeStruct&& x) noexcept
    {
        m_value = x.m_value;
    }

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object RelativePathIncludeStruct that will be copied.
     */
    eProsima_user_DllExport RelativePathIncludeStruct& operator =(
            const RelativePathIncludeStruct& x)
    {

                    m_value = x.m_value;

        return *this;
    }

    /*!
     * @brief Move assignment.
     * @param x Reference to the object RelativePathIncludeStruct that will be copied.
     */
    eProsima_user_DllExport RelativePathIncludeStruct& operator =(
            RelativePathIncludeStruct&& x) noexcept
    {

        m_value = x.m_value;
        return *this;
    }

    /*!
     * @brief Comparison operator.
     * @param x RelativePathIncludeStruct object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const RelativePathIncludeStruct& x) const
    {
        return (m_value == x.m_value);
    }

    /*!
     * @brief Comparison operator.
     * @param x RelativePathIncludeStruct object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const RelativePathIncludeStruct& x) const
    {
        return !(*this == x);
    }

    /*!
     * @brief This function sets a value in member value
     * @param _value New value for member value
     */
    eProsima_user_DllExport void value(
            InnerEnumHelper _value)
    {
        m_value = _value;
    }

    /*!
     * @brief This function returns the value of member value
     * @return Value of member value
     */
    eProsima_user_DllExport InnerEnumHelper value() const
    {
        return m_value;
    }

    /*!
     * @brief This function returns a reference to member value
     * @return Reference to member value
     */
    eProsima_user_DllExport InnerEnumHelper& value()
    {
        return m_value;
    }



private:

    InnerEnumHelper m_value{InnerEnumHelper::ENUM_VALUE_1};

};

#endif // _FAST_DDS_GENERATED_RELATIVE_PATH_INCLUDE_HPP_


