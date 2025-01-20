#ifndef PEARS_VEHICLE_COMPONENTS_VEHICLESTREAMEDINLISTENER_H
#define PEARS_VEHICLE_COMPONENTS_VEHICLESTREAMEDINLISTENER_H

#include "network.hpp"
#include "packet.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include <unordered_set>

namespace CustomVehicleComponents {
    struct VehicleStreamedInListener :
            SingleNetworkOutEventHandler, CoreEventHandler,
            PoolEventHandler<IPlayer>, PoolEventHandler<IVehicle> {
    public:
        static constexpr int kRpcId = 164;

        void onLoad(ICore* icore, IComponentList* components);
        void onUnload();
        void onFree(IComponent* component);

        // Inherited from SingleNetworkOutEventHandler
        bool onSend(IPlayer* peer, NetworkBitStream& bs) override;

        // Inherited from CoreEventHandler
        void onTick(Microseconds elapsed, TimePoint now) override;

        // Inherited from PoolEventHandler<IPlayer>
        void onPoolEntryDestroyed(IPlayer& player) override;

        // Inherited from PoolEventHandler<IVehicle>
        void onPoolEntryDestroyed(IVehicle& vehicle) override;

        ~VehicleStreamedInListener() = default;

    private:
        std::unordered_map<IPlayer*, std::unordered_set<IVehicle*>> wPlayers;
        ICore* core;
        IVehiclesComponent* vehicles;
    };
}

#endif //PEARS_VEHICLE_COMPONENTS_VEHICLESTREAMEDINLISTENER_H
