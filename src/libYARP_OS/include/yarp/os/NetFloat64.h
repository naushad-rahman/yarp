// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

#ifndef _YARP2_NETFLOAT64_
#define _YARP2_NETFLOAT64_

#include <yarp/os/NetInt32.h>

namespace yarp {
    namespace os {


#ifdef YARP2_LINUX
        typedef double NetFloat64;
#else
#  ifdef YARP2_WINDOWS
        typedef double NetFloat64;
#else
#  ifdef YARP2_CYGWIN
        typedef double NetFloat64;
#  else
#    ifdef YARP2_OSX


        /* OSX begins*/
#ifndef YARP_LITTLE_ENDIAN
#define YARP_ACTIVE_DOUBLE
        typedef double RawNetFloat64;
        union UnionNetFloat64 {
            double d;
            unsigned char c[8];
        };
        class NetFloat64 {
        private:
            double raw_value;
            double swap(double x) const {
                UnionNetFloat64 in, out;
                in.d = x;
                for (int i=0; i<8; i++) {
                    out.c[i] = in.c[7-i];
                }
                return out.d;
            }
            RawNetFloat64 get() const {
                return (double)swap((double)raw_value);
            }
            void set(RawNetFloat64 v) {
                raw_value = (double)swap((double)v);
            }
        public:
            NetFloat64() {
            }
            NetFloat64(RawNetFloat64 val) {
                set(val);
            }
            operator RawNetFloat64() const {
                return get();
            }
            RawNetFloat64 operator+(RawNetFloat64 v) const {
                return get()+v;
            }
            RawNetFloat64 operator-(RawNetFloat64 v) const {
                return get()-v;
            }
            RawNetFloat64 operator*(RawNetFloat64 v) const {
                return get()*v;
            }
            RawNetFloat64 operator/(RawNetFloat64 v) const {
                return get()/v;
            }
            void operator+=(RawNetFloat64 v) {
                set(get()+v);
            }
            void operator-=(RawNetFloat64 v) {
                set(get()-v);
            }
            void operator*=(RawNetFloat64 v) {
                set(get()*v);
            }
            void operator/=(RawNetFloat64 v) {
                set(get()/v);
            }
        };
#else
        typedef double NetFloat64; // random assumption
#endif
        /* OSX ends*/


#    else
        typedef double NetFloat64; // random assumption
#    endif
#  endif
#endif
#endif

    }
}

#endif /* _YARP2_NETFLOAT64_ */



