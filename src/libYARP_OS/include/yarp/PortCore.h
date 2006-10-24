// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

#ifndef _YARP2_PORTCORE_
#define _YARP2_PORTCORE_

#include <yarp/ThreadImpl.h>
#include <yarp/SemaphoreImpl.h>
#include <yarp/Carriers.h>
#include <yarp/Address.h>
#include <yarp/PortManager.h>
#include <yarp/Readable.h>
#include <yarp/Writable.h>
#include <yarp/PortCorePacket.h>

#include <ace/Vector_T.h>

namespace yarp {
    class PortCore;
    class PortCoreUnit;
}

/**
 * This is the heart of a yarp port.  It is the thread manager.
 * All other port components are insulated from threading
 * It maintains a collection of incoming and
 * outgoing connections.  Data coming from incoming connections is
 * directed to the handler set with setReadHandler().  Calls to send()
 * result in data begin sent to all the outgoing connections.
 */
class yarp::PortCore : public ThreadImpl, public PortManager, public Readable {
public:

    PortCore() : stateMutex(1), packetMutex(1), connectionChange(1),
                 log("port",Logger::get()) {
        // dormant phase
        listening = false;
        running = false;
        starting = false;
        closing = false;
        finished = false;
        finishing = false;
        autoHandshake = true;
        waitBeforeSend = waitAfterSend = true;
        connectionListeners = 0;
        events = 0;
        face = NULL;
        reader = NULL;
        readableCreator = NULL;
    }

    virtual ~PortCore();

    // configure core
    bool listen(const Address& address);

    bool isWriting();

    void setReadHandler(Readable& reader);

    void setReadCreator(ReadableCreator& creator);

    void setAutoHandshake(bool autoHandshake) {
        this->autoHandshake = autoHandshake;
    }

    void setWaitBeforeSend(bool waitBeforeSend) {
        this->waitBeforeSend = waitBeforeSend;
    }

    void setWaitAfterSend(bool waitAfterSend) {
        this->waitAfterSend = waitAfterSend;
    }

    virtual bool read(ConnectionReader& reader) {
        // does nothing by default
        return true;
    }

    // start up core
    virtual bool start();

    // use port as output
    void send(Writable& writer, Readable *reader = NULL);

    // shut down and deconfigure core
    virtual void close();

    // main manager thread
    virtual void run();

    // useful for stress-testing
    int getEventCount();

    const Address& getAddress() const {
        return address;
    }

    ReadableCreator *getReadCreator() {
        return readableCreator;
    }

    void notifyCompletion(void *tracker);

public:

    // PortManager interface, exposed to inputs

    virtual void addOutput(const String& dest, void *id, OutputStream *os);
    virtual void removeOutput(const String& dest, void *id, OutputStream *os);
    virtual void removeInput(const String& dest, void *id, OutputStream *os);
    virtual void describe(void *id, OutputStream *os);
    virtual void readBlock(ConnectionReader& reader, void *id, OutputStream *os);

private:

    // internal maintenance of sub units

    ACE_Vector<PortCoreUnit *> units;

    // only called in "finished" phase
    void closeUnits();

    // called anytime, garbage collects terminated units
    void cleanUnits();

    // only called by the manager
    void reapUnits();

    // only called in "running" phase
    void addInput(InputProtocol *ip);

    void addOutput(OutputProtocol *op);

    bool removeUnit(const Route& route, bool synch = false);

private:

    // main internal PortCore state and operations
    SemaphoreImpl stateMutex, packetMutex, connectionChange;
    Logger log;
    Face *face;
    String name;
    Address address;
    Readable *reader;
    ReadableCreator *readableCreator;
    bool listening, running, starting, closing, finished, autoHandshake;
    bool finishing;
    bool waitBeforeSend, waitAfterSend;
    int events;
    int connectionListeners;
    PortCorePackets packets;

    void closeMain();

    bool isUnit(const Route& route);
};

#endif
