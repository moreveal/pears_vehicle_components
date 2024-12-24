//
// Created by moreveal on 24.12.2024.
//
#include "VehicleStreamedInListener.h"
#include "CustomVehicleComponents.h"
#include "VehicleExtension.h"

#include <thread>
#include <chrono>

namespace CustomVehicleComponents {
    bool VehicleStreamedInListener::onSend(IPlayer *peer, NetworkBitStream &bs) {
        if (peer == nullptr) return true;
        auto* vehicles = PluginComponent::instance()->getVehicles();
        if (vehicles == nullptr) return true;

        bs.resetReadPointer();

        uint16_t vehicleid;
        bs.readUINT16(vehicleid);

        auto* vehicle = vehicles->get(vehicleid);
        if (vehicle == nullptr) return true;

        std::thread([peer, vehicle](){
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            if (!vehicle->isStreamedInForPlayer(*peer)) return;

            auto vehicleExtension = queryExtension<VehicleExtension>(vehicle);
            if (vehicleExtension == nullptr) return;

            const auto& custom_mods = vehicleExtension->getCustomComponents(*vehicle);
            for (size_t i = 0; i < MAX_VEHICLE_COMPONENT_SLOT; i++)
            {
                const auto mod = custom_mods[i];
                if (mod == INVALID_COMPONENT_ID) continue;

                NetworkBitStream send_bs;
                send_bs.writeUINT16(INVALID_PLAYER_ID); // PlayerID
                send_bs.writeUINT32(static_cast<uint32_t>(VehicleSCMEvent_AddComponent)); // EventType
                send_bs.writeUINT32(vehicle->getID()); // VehicleID
                send_bs.writeUINT32(mod); // Arg1
                send_bs.writeUINT32(0); // Arg2

                peer->sendRPC(96, Span<uint8_t>(send_bs.GetData(), send_bs.GetNumberOfBitsUsed()), OrderingChannel_SyncRPC);
            }
        }).detach();

        return true;
    }
}

