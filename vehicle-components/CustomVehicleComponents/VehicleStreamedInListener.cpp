//
// Created by moreveal on 24.12.2024.
//
#include "VehicleStreamedInListener.h"
#include "CustomVehicleComponents.h"
#include "VehicleExtension.h"

namespace CustomVehicleComponents {
    bool VehicleStreamedInListener::onSend(IPlayer *peer, NetworkBitStream &bs) {
        if (peer == nullptr) return true;
        if (vehicles == nullptr) return true;

        bs.resetReadPointer();

        uint16_t vehicleid;
        bs.readUINT16(vehicleid);

        auto* vehicle = vehicles->get(vehicleid);
        if (vehicle == nullptr) return true;

        wPlayers[peer].insert(vehicle);
        return true;
    }

    void VehicleStreamedInListener::onTick(Microseconds elapsed, TimePoint now) {
        for (auto it = wPlayers.begin(); it != wPlayers.end(); ) {
            auto* peer = it->first;
            auto& peer_vehicles = it->second;

            for (auto vehicle : peer_vehicles) {
                auto vehicleExtension = queryExtension<VehicleExtension>(vehicle);
                if (vehicleExtension == nullptr || !vehicle->isStreamedInForPlayer(*peer)) {
                    continue;
                }

                const auto& custom_mods = vehicleExtension->getCustomComponents();
                for (const auto mod : custom_mods) {
                    if (mod == INVALID_COMPONENT_ID) continue;

                    NetworkBitStream send_bs;
                    send_bs.writeUINT16(INVALID_PLAYER_ID); // PlayerID
                    send_bs.writeUINT32(static_cast<uint32_t>(VehicleSCMEvent_AddComponent)); // EventType
                    send_bs.writeUINT32(vehicle->getID()); // VehicleID
                    send_bs.writeUINT32(mod); // Arg1
                    send_bs.writeUINT32(0); // Arg2

                    peer->sendRPC(96, Span<uint8_t>(send_bs.GetData(), send_bs.GetNumberOfBitsUsed()), OrderingChannel_SyncRPC);
                }
            }

            it = wPlayers.erase(it);
        }
    }

    void VehicleStreamedInListener::onPoolEntryDestroyed(IVehicle &vehicle) {
        for (auto it = wPlayers.begin(); it != wPlayers.end(); ) {
            auto& peer_vehicles = it->second;

            peer_vehicles.erase(&vehicle);

            if (peer_vehicles.empty()) {
                it = wPlayers.erase(it);
            } else {
                ++it;
            }
        }
    }

    void VehicleStreamedInListener::onPoolEntryDestroyed(IPlayer &player) {
        auto it = wPlayers.find(&player);
        if (it != wPlayers.end())
        {
            wPlayers.erase(it);
        }
    }

    void VehicleStreamedInListener::onLoad(ICore *icore, IComponentList *components) {
        core = icore;

        vehicles = components->queryComponent<IVehiclesComponent>();
        if (vehicles)
        {
            vehicles->getPoolEventDispatcher().addEventHandler(this);
        }

        core->getEventDispatcher().addEventHandler(this);
        core->getPlayers().getPoolEventDispatcher().addEventHandler(this);
    }

    void VehicleStreamedInListener::onUnload() {
        if (core)
        {
            core->getPlayers().getPoolEventDispatcher().removeEventHandler(this);
            core->getEventDispatcher().removeEventHandler(this);
        }
        core = nullptr;
    }

    void VehicleStreamedInListener::onFree(IComponent *component) {
        if (component == vehicles) {
            vehicles->getPoolEventDispatcher().removeEventHandler(this);
            vehicles = nullptr;
        }
    }
}

