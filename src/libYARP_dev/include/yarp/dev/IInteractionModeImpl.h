// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright: 2014 iCub Facility - Istituto Italiano di Tecnologia
 * Authors: Alberto Cardellino <alberto.cardellino@iit.it>
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#ifndef IINTERACTION_MODE_IMPL_H
#define IINTERACTION_MODE_IMPL_H

#include <yarp/dev/api.h>
#include <yarp/dev/IInteractionMode.h>

namespace yarp {
    namespace dev {
        class ImplementInteractionMode;
        class ImplementInteractionModeRaw;
        class StubImplInteractionModeRaw;
    }
}

/**
 * @ingroup dev_iface_motor
 *
 * Interface settings the way the robot interacts with the environment: basic interaction types are Stiff and Compliant.
 * This setting is intended to work in conjunction with other settings like position or velocity control.
 */
class YARP_dev_API yarp::dev::ImplementInteractionMode : public yarp::dev::IInteractionMode
{
protected:
    yarp::dev::IInteractionModeRaw *iInteraction;
    void    *helper;                                // class controlBoardHelper, to handle axis map and conversion unit, where needed
    int     *temp_int;                              // to convert axis number
    yarp::dev::InteractionModeEnum *temp_modes;     // helper for all joints methods

    /**
     * Initialize the internal data and alloc memory, smaller version.
     * @param size is the number of controlled axes the driver deals with.
     * @param amap is a lookup table mapping axes onto physical drivers.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *amap);

    /**
     * Initialize the internal data and alloc memory.
     * @param size is the number of controlled axes the driver deals with.
     * @param amap is a lookup table mapping axes onto physical drivers.
     * @param enc is an array containing the encoder to angles conversion factors.
     * @param zos is an array containing the zeros of the encoders.
     *  respect to the control/output values of the driver.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *amap, const double *enc, const double *zos);


    /**
     * Clean up internal data and memory.
     * @return true if uninitialization is executed, false otherwise.
     */
    bool uninitialize ();


public:
    /**
     * Constructor.
     * @param Class_p is the pointer to the class instance inheriting from this
     *  implementation.
     */
    ImplementInteractionMode(yarp::dev::IInteractionModeRaw *Class_p);

    /**
     * Destructor. Perform uninitialize if needed.
     */
    virtual ~ImplementInteractionMode();

    // Methods are documented in the <yarp/dev/IInteractionMode.h> file
    virtual bool getInteractionMode(int axis, yarp::dev::InteractionModeEnum* mode);
    virtual bool getInteractionModes(int n_joints, int *joints, yarp::dev::InteractionModeEnum* modes);
    virtual bool getInteractionModes(yarp::dev::InteractionModeEnum* modes);

    virtual bool setInteractionMode(int axis, yarp::dev::InteractionModeEnum mode);
    virtual bool setInteractionModes(int n_joints, int *joints, yarp::dev::InteractionModeEnum* modes);
    virtual bool setInteractionModes(yarp::dev::InteractionModeEnum* modes);
};


/**
 * Stub implementation of IInteractionMode interface.
 * Inherit from this class if you want a stub implementation
 * of methods in IInteractionModeRaw. This class allows to
 * gradually implement an interface; you just have to implement
 * functions that are useful for the underlying device.
 * Another way to see this class is as a means to convert
 * compile time errors in runtime errors.
 *
 * If you use this class please be aware that the device
 * you are wrapping might not function properly because you
 * missed to implement useful functionalities.
 *
 */
class yarp::dev::StubImplInteractionModeRaw : public yarp::dev::IInteractionModeRaw
{
protected:
    /**
     * Helper for printing error message, see below.
     * Implemented in ControlBoardInterfacesImpl.cpp.
     */
    bool NOT_YET_IMPLEMENTED(const char *func=0)
    {
        if (func)
            fprintf(stderr, "%s:", func);
        else
            fprintf(stderr, "Function ");

        fprintf(stderr, "not yet implemented\n");

        return false;
    }


public:
    /**
     * Destructor.
     */
    virtual ~StubImplInteractionModeRaw() {}

    virtual bool getInteractionModeRaw(int axis, yarp::dev::InteractionModeEnum* mode)
    {
        return NOT_YET_IMPLEMENTED("getInteractionModeRaw");
    }

    virtual bool getInteractionModesRaw(int n_joints, int *joints, yarp::dev::InteractionModeEnum* modes)
    {
        return NOT_YET_IMPLEMENTED("getInteractionModesRaw");
    }

    virtual bool getInteractionModesRaw(yarp::dev::InteractionModeEnum* modes)
    {
        return NOT_YET_IMPLEMENTED("getInteractionModesRaw");
    }

    virtual bool setInteractionModeRaw(int axis, yarp::dev::InteractionModeEnum mode)
    {
        return NOT_YET_IMPLEMENTED("setInteractionModeRaw");
    }

    virtual bool setInteractionModesRaw(int n_joints, int *joints, yarp::dev::InteractionModeEnum* modes)
    {
        return NOT_YET_IMPLEMENTED("setInteractionModesRaw");
    }

    virtual bool setInteractionModesRaw(yarp::dev::InteractionModeEnum* modes)
    {
        return NOT_YET_IMPLEMENTED("setInteractionModesRaw");
    }
};

#endif /* IINTERACTION_MODE_IMPL_H */


