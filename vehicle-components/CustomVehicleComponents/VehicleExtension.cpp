#include "VehicleExtension.h"

namespace CustomVehicleComponents {
    void VehicleExtension::freeExtension() {
        delete this;
    }

    void VehicleExtension::reset() {
        /* Nothing to do */
    }

    bool VehicleExtension::addCustomComponent(IVehicle& vehicle, uint32_t component) {
        int slot = getCustomComponentSlot(component);
        if (slot == VehicleComponent_None) return false;

        mods[slot] = component;

        NetworkBitStream bs;
        bs.writeUINT16(INVALID_PLAYER_ID); // PlayerID
        bs.writeUINT32(static_cast<uint32_t>(VehicleSCMEvent_AddComponent)); // EventType
        bs.writeUINT32(vehicle.getID()); // VehicleID
        bs.writeUINT32(component); // Arg1
        bs.writeUINT32(0); // Arg2

        for (auto* peer : vehicle.streamedForPlayers())
        {
            peer->sendRPC(96, Span<uint8_t>(bs.GetData(), bs.GetNumberOfBitsUsed()), OrderingChannel_SyncRPC);
        }

        return true;
    }

    int VehicleExtension::getCustomComponentInSlot(int slot) {
        if (slot < 0 || slot >= MAX_VEHICLE_COMPONENT_SLOT)
        {
            return INVALID_COMPONENT_ID;
        }
        return mods[slot];
    }

    bool VehicleExtension::removeCustomComponent(IVehicle& vehicle, uint32_t component) {
        int slot = getCustomComponentSlot(component);
        if (slot == VehicleComponent_None) return false;

        if (mods[slot] == component)
        {
            mods[slot] = VehicleComponent_None;
        }

        NetworkBitStream bs;
        bs.writeUINT16(vehicle.getID());
        bs.writeUINT16(component);
        for (auto* peer : vehicle.streamedForPlayers())
        {
            peer->sendRPC(57, Span<uint8_t>(bs.GetData(), bs.GetNumberOfBitsUsed()), OrderingChannel_SyncRPC);
        }

        return true;
    }

    StaticArray<uint32_t, MAX_VEHICLE_COMPONENT_SLOT> VehicleExtension::getCustomComponents(IVehicle &vehicle) {
        return mods;
    }

    VehicleExtension::VehicleExtension() {
        for (auto& mod : mods) mod = INVALID_COMPONENT_ID;
    }
}