#ifndef PEARS_VEHICLE_COMPONENTS_CUSTOMVEHICLECOMPONENTS_H
#define PEARS_VEHICLE_COMPONENTS_CUSTOMVEHICLECOMPONENTS_H

#include "PluginComponent.h"
#include "VehicleStreamedInListener.h"

namespace CustomVehicleComponents {
    enum VehicleComponentSlot
    {
        VehicleComponent_None = -1,
        VehicleComponent_Spoiler = 0,
        VehicleComponent_Hood = 1,
        VehicleComponent_Roof = 2,
        VehicleComponent_SideSkirt = 3,
        VehicleComponent_Lamps = 4,
        VehicleComponent_Nitro = 5,
        VehicleComponent_Exhaust = 6,
        VehicleComponent_Wheels = 7,
        VehicleComponent_Stereo = 8,
        VehicleComponent_Hydraulics = 9,
        VehicleComponent_FrontBumper = 10,
        VehicleComponent_RearBumper = 11,
        VehicleComponent_VentRight = 12,
        VehicleComponent_VentLeft = 13,
        VehicleComponent_FrontBullbar = 14,
        VehicleComponent_RearBullbar = 15,
    };

    void load(ICore *icore, IComponentList* components);
    void unload();
    void unloadComponent(IComponent* component);

    inline ICore *core = nullptr;
    inline std::unordered_map<uint32_t, int> vehicleComponents;

    void setCustomComponentSlot(uint32_t component, int slot);
    int getCustomComponentSlot(uint32_t component);

    inline VehicleStreamedInListener vehicleStreamedInListener;
}


#endif //PEARS_VEHICLE_COMPONENTS_CUSTOMVEHICLECOMPONENTS_H
