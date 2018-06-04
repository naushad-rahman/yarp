/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include <yarp/os/NullConnectionReader.h>


bool yarp::os::NullConnectionReader::expectBlock(const char *data, size_t len)
{
    YARP_UNUSED(data);
    YARP_UNUSED(len);
    return false;
}

std::string yarp::os::NullConnectionReader::expectText(int terminatingChar)
{
    YARP_UNUSED(terminatingChar);
    return "";
}

std::int8_t yarp::os::NullConnectionReader::expectInt8()
{
    return 0;
}

std::int16_t yarp::os::NullConnectionReader::expectInt16()
{
    return 0;
}

std::int32_t yarp::os::NullConnectionReader::expectInt32()
{
    return 0;
}

std::int64_t yarp::os::NullConnectionReader::expectInt64()
{
    return 0;
}

yarp::conf::float32_t yarp::os::NullConnectionReader::expectFloat32()
{
    return 0.0f;
}

yarp::conf::float64_t yarp::os::NullConnectionReader::expectFloat64()
{
    return 0.0;
}

bool yarp::os::NullConnectionReader::pushInt(int x)
{
    YARP_UNUSED(x);
    return false;
}
bool yarp::os::NullConnectionReader::isTextMode() const
{
    return false;
}

bool yarp::os::NullConnectionReader::convertTextMode()
{
    return false;
}

size_t yarp::os::NullConnectionReader::getSize()
{
    return 0;
}

yarp::os::ConnectionWriter *yarp::os::NullConnectionReader::getWriter()
{
    return nullptr;
}

yarp::os::Bytes yarp::os::NullConnectionReader::readEnvelope()
{
    return Bytes(nullptr, 0);
}

yarp::os::Portable *yarp::os::NullConnectionReader::getReference()
{
    return nullptr;
}

yarp::os::Contact yarp::os::NullConnectionReader::getRemoteContact()
{
    return Contact();
}

yarp::os::Contact yarp::os::NullConnectionReader::getLocalContact()
{
    return Contact();
}

bool yarp::os::NullConnectionReader::isValid()
{
    return false;
}

bool yarp::os::NullConnectionReader::isActive()
{
    return false;
}

bool yarp::os::NullConnectionReader::isError()
{
    return true;
}

void yarp::os::NullConnectionReader::requestDrop()
{
}

yarp::os::Searchable& yarp::os::NullConnectionReader::getConnectionModifiers()
{
    return blank;
}
