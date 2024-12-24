#include <Server/Components/Pawn/Impl/pawn_natives.hpp>
#include "CustomVehicleComponents.h"
#include "VehicleExtension.h"

namespace CustomVehicleComponents {
    SCRIPT_API(AddVehicleCustomComponent, void(IVehicle& vehicle, uint32_t component)) {
        auto vehicleExtension = queryExtension<VehicleExtension>(&vehicle);
        if (vehicleExtension == nullptr) {
            return vehicle.addComponent(static_cast<int>(component));
        }
        vehicleExtension->addCustomComponent(vehicle, component);
    }

    SCRIPT_API(RemoveVehicleCustomComponent, void(IVehicle& vehicle, uint32_t component)) {
        auto vehicleExtension = queryExtension<VehicleExtension>(&vehicle);
        if (vehicleExtension != nullptr) {
            vehicleExtension->removeCustomComponent(vehicle, component);
        }
        vehicle.removeComponent(static_cast<int>(component));
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

    SCRIPT_API(SetVehicleCustomComponentType, void(uint32_t component, int slot)) {
        return setCustomComponentSlot(component, slot);
    }

    SCRIPT_API(IsVehicleCustomComponent, bool(uint32_t component)) {
        return getCustomComponentSlot(component) != VehicleComponent_None;
    }
}