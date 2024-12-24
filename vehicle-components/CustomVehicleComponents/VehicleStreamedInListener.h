#ifndef PEARS_VEHICLE_COMPONENTS_VEHICLESTREAMEDINLISTENER_H
#define PEARS_VEHICLE_COMPONENTS_VEHICLESTREAMEDINLISTENER_H

#include "network.hpp"
#include "packet.hpp"

namespace CustomVehicleComponents {
    struct VehicleStreamedInListener : SingleNetworkOutEventHandler {
        static constexpr int kRpcId = 164;

        bool onSend(IPlayer* peer, NetworkBitStream& bs) override;
    };
}

#endif //PEARS_VEHICLE_COMPONENTS_VEHICLESTREAMEDINLISTENER_H
