// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <stdio.h>

#include <yarp/String.h>
#include <yarp/sig/Image.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Property.h>
#include <yarp/os/Network.h>
#include <yarp/os/Time.h>
#include <yarp/os/Network.h>

using namespace yarp;
using namespace yarp::os;
using namespace yarp::sig;

int main(int argc, char *argv[]) {
    Network yarp;
    if (argc==1) {
        printf("This program checks the framerate of an output port\n");
        printf("Call as:\n");
        printf("   framerate --remote /port_name --local /local_name --prot protocol\n");
        printf("protocol can be for example tcp,udp,mcast\n");
        exit(0);
    }

    BufferedPort<Bottle> port;

    // get options
    Property opt;
    opt.fromCommand(argc,argv);

    // name port
    Value *val;
    Value *prot;
    String local = "/get_image";
    if (opt.check("local",val)) {
        local = val->asString().c_str();
    }
    port.open(local.c_str());

    // connect port
    if (opt.check("remote", val))
    {
        if (opt.check("prot", prot))
            Network::connect(val->asString(), local.c_str(), prot->asString().c_str());
        else
            Network::connect(val->asString(), local.c_str());
    }        
    // read
    double first = Time::now();
    double prev = 0;
    int ct = 0;
    bool spoke = false;
    while (true) {
        Bottle *bot = port.read(true);
        double now = Time::now()-first;
        ct++;
        if (now-prev>=2) {
            double period = (now-prev)/ct;
            printf("Period is %g ms per message, freq is %g (%d messages in %g seconds)\n",
                   period*1000, 1/period, ct, now-prev);
            ct = 0;
            prev = now;
            spoke = false;
        }
        if (bot!=NULL) {
            if (!spoke) {
                printf("Got something with %d top-level elements\n", bot->size());
                spoke = true;
            }
        }
    }
    return 0;
}

