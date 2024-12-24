#ifndef PEARS_VEHICLE_COMPONENTS_INTERFACE_H
#define PEARS_VEHICLE_COMPONENTS_INTERFACE_H

#include "CustomVehicleComponents.h"

namespace CustomVehicleComponents {
    struct IVehicleExtension : IExtension {
        PROVIDE_EXT_UID(0x880FBADD63BDD6C5);

        virtual bool addCustomComponent(IVehicle& vehicle, uint32_t component) = 0;
        virtual int getCustomComponentInSlot(int slot) = 0;
        virtual bool removeCustomComponent(IVehicle& vehicle, uint32_t component) = 0;
        virtual StaticArray<uint32_t, MAX_VEHICLE_COMPONENT_SLOT> getCustomComponents(IVehicle& vehicle) = 0;
    };
}

#endif //PEARS_VEHICLE_COMPONENTS_INTERFACE_H
