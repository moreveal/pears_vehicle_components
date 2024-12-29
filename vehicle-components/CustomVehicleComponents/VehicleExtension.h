#ifndef PEARS_VEHICLE_COMPONENTS_VEHICLEEXTENSION_H
#define PEARS_VEHICLE_COMPONENTS_VEHICLEEXTENSION_H

#include "interface.h"

namespace CustomVehicleComponents {
    struct VehicleExtension : IVehicleExtension {
    private:
        StaticArray<uint32_t, MAX_VEHICLE_COMPONENT_SLOT> mods{};
        IVehicle& vehicle;
    public:
        VehicleExtension(IVehicle& vehicle_) : vehicle(vehicle_) {
          mods.fill(0);
        }

        bool addCustomComponent(uint32_t component) override;
        int getCustomComponentInSlot(int slot) override;
        bool removeCustomComponent(uint32_t component) override;
        const StaticArray<uint32_t, MAX_VEHICLE_COMPONENT_SLOT>& getCustomComponents() const override;

        // Inherited from IExtension
        void freeExtension() override;
        void reset() override;
    };
}


#endif //PEARS_VEHICLE_COMPONENTS_VEHICLEEXTENSION_H
