#ifndef PEARS_VEHICLE_COMPONENTS_VEHICLEEXTENSION_H
#define PEARS_VEHICLE_COMPONENTS_VEHICLEEXTENSION_H

#include "interface.h"

namespace CustomVehicleComponents {
    struct VehicleExtension : IVehicleExtension {
    private:
        StaticArray<uint32_t, MAX_VEHICLE_COMPONENT_SLOT> mods{};
    public:
        VehicleExtension();
        bool addCustomComponent(IVehicle& vehicle, uint32_t component) override;
        int getCustomComponentInSlot(int slot) override;
        bool removeCustomComponent(IVehicle& vehicle, uint32_t component) override;
        StaticArray<uint32_t, MAX_VEHICLE_COMPONENT_SLOT> getCustomComponents(IVehicle& vehicle) override;

        // Inherited from IExtension
        void freeExtension() override;
        void reset() override;
    };
}


#endif //PEARS_VEHICLE_COMPONENTS_VEHICLEEXTENSION_H
