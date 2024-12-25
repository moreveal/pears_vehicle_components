#include <Server/Components/Pawn/Impl/pawn_natives.hpp>
#include "CustomVehicleComponents.h"
#include "VehicleExtension.h"

namespace CustomVehicleComponents {
    SCRIPT_API(AddVehicleCustomComponent, bool(IVehicle& vehicle, uint32_t component)) {
        auto vehicleExtension = queryExtension<VehicleExtension>(&vehicle);
        if (vehicleExtension == nullptr) {
            vehicle.addComponent(static_cast<int>(component));
        } else {
            vehicleExtension->addCustomComponent(component);
        }
        return true;
    }

    SCRIPT_API(RemoveVehicleCustomComponent, bool(IVehicle& vehicle, uint32_t component)) {
        auto vehicleExtension = queryExtension<VehicleExtension>(&vehicle);
        if (vehicleExtension != nullptr) {
            vehicleExtension->removeCustomComponent(component);
        }
        vehicle.removeComponent(static_cast<int>(component));
        return true;
    }

    SCRIPT_API(GetVehicleCustomComponentInSlot, int(IVehicle& vehicle, int slot)) {
        auto vehicleExtension = queryExtension<VehicleExtension>(&vehicle);
        if (vehicleExtension == nullptr) {
            return vehicle.getComponentInSlot(slot);
        }
        return vehicleExtension->getCustomComponentInSlot(slot);
    }

    SCRIPT_API(GetVehicleCustomComponentType, int(uint32_t component)) {
        return getCustomComponentSlot(component);
    }

    SCRIPT_API(SetVehicleCustomComponentType, bool(uint32_t component, int slot)) {
        setCustomComponentSlot(component, slot);
        return true;
    }

    SCRIPT_API(IsVehicleCustomComponent, bool(uint32_t component)) {
        return getCustomComponentSlot(component) != VehicleComponent_None;
    }
}