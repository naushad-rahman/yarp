/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "geometry_msgs/AccelWithCovariance" msg definition:
//   # This expresses acceleration in free space with uncertainty.
//   
//   Accel accel
//   
//   # Row-major representation of the 6x6 covariance matrix
//   # The orientation parameters use a fixed-axis representation.
//   # In order, the parameters are:
//   # (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
//   float64[36] covariance
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_geometry_msgs_AccelWithCovariance_h
#define YARP_ROSMSG_geometry_msgs_AccelWithCovariance_h

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>
#include <yarp/rosmsg/geometry_msgs/Accel.h>

namespace yarp {
namespace rosmsg {
namespace geometry_msgs {

class AccelWithCovariance : public yarp::os::idl::WirePortable
{
public:
    yarp::rosmsg::geometry_msgs::Accel accel;
    std::vector<yarp::os::NetFloat64> covariance;

    AccelWithCovariance() :
            accel(),
            covariance()
    {
        covariance.resize(36, 0.0);
    }

    void clear()
    {
        // *** accel ***
        accel.clear();

        // *** covariance ***
        covariance.clear();
        covariance.resize(36, 0.0);
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** accel ***
        if (!accel.read(connection)) {
            return false;
        }

        // *** covariance ***
        int len = 36;
        covariance.resize(len);
        if (len > 0 && !connection.expectBlock((char*)&covariance[0], sizeof(yarp::os::NetFloat64)*len)) {
            return false;
        }

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(2)) {
            return false;
        }

        // *** accel ***
        if (!accel.read(connection)) {
            return false;
        }

        // *** covariance ***
        if (connection.expectInt() != (BOTTLE_TAG_LIST|BOTTLE_TAG_DOUBLE)) {
            return false;
        }
        int len = connection.expectInt();
        covariance.resize(len);
        for (int i=0; i<len; i++) {
            covariance[i] = (yarp::os::NetFloat64)connection.expectDouble();
        }

        return !connection.isError();
    }

    using yarp::os::idl::WirePortable::read;
    bool read(yarp::os::ConnectionReader& connection) override
    {
        return (connection.isBareMode() ? readBare(connection)
                                        : readBottle(connection));
    }

    bool writeBare(yarp::os::ConnectionWriter& connection) override
    {
        // *** accel ***
        if (!accel.write(connection)) {
            return false;
        }

        // *** covariance ***
        if (covariance.size()>0) {
            connection.appendExternalBlock((char*)&covariance[0], sizeof(yarp::os::NetFloat64)*covariance.size());
        }

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) override
    {
        connection.appendInt(BOTTLE_TAG_LIST);
        connection.appendInt(2);

        // *** accel ***
        if (!accel.write(connection)) {
            return false;
        }

        // *** covariance ***
        connection.appendInt(BOTTLE_TAG_LIST|BOTTLE_TAG_DOUBLE);
        connection.appendInt(covariance.size());
        for (size_t i=0; i<covariance.size(); i++) {
            connection.appendDouble((double)covariance[i]);
        }

        connection.convertTextMode();
        return !connection.isError();
    }

    using yarp::os::idl::WirePortable::write;
    bool write(yarp::os::ConnectionWriter& connection) override
    {
        return (connection.isBareMode() ? writeBare(connection)
                                        : writeBottle(connection));
    }

    // This class will serialize ROS style or YARP style depending on protocol.
    // If you need to force a serialization style, use one of these classes:
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::geometry_msgs::AccelWithCovariance> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::geometry_msgs::AccelWithCovariance> bottleStyle;

    // Give source text for class, ROS will need this
    static yarp::os::ConstString typeText()
    {
        return yarp::os::ConstString("\
# This expresses acceleration in free space with uncertainty.\n\
\n\
Accel accel\n\
\n\
# Row-major representation of the 6x6 covariance matrix\n\
# The orientation parameters use a fixed-axis representation.\n\
# In order, the parameters are:\n\
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)\n\
float64[36] covariance\n\
") + yarp::os::ConstString("\n\
================================================================================\n\
MSG: geometry_msgs/Accel\n\
") + yarp::rosmsg::geometry_msgs::Accel::typeText();
    }

    yarp::os::ConstString getTypeText() const
    {
        return yarp::rosmsg::geometry_msgs::AccelWithCovariance::typeText();
    }

    // Name the class, ROS will need this
    yarp::os::Type getType() override
    {
        yarp::os::Type typ = yarp::os::Type::byName("geometry_msgs/AccelWithCovariance", "geometry_msgs/AccelWithCovariance");
        typ.addProperty("md5sum", yarp::os::Value("f10cf81eab8fdd6514341a13d3e782b5"));
        typ.addProperty("message_definition", yarp::os::Value(getTypeText()));
        return typ;
    }
};

} // namespace geometry_msgs
} // namespace rosmsg
} // namespace yarp

#endif // YARP_ROSMSG_geometry_msgs_AccelWithCovariance_h