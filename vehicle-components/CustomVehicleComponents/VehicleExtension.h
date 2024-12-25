#ifndef PEARS_VEHICLE_COMPONENTS_VEHICLEEXTENSION_H
#define PEARS_VEHICLE_COMPONENTS_VEHICLEEXTENSION_H

#include "interface.h"

namespace CustomVehicleComponents {
    struct VehicleExtension : IVehicleExtension {
    private:
        StaticArray<uint32_t, MAX_VEHICLE_COMPONENT_SLOT> mods{};
        IVehicle* vehicle = nullptr;
    public:
        VehicleExtension() = default;
        VehicleExtension(IVehicle* vehicle_) : vehicle(vehicle_) {}
        virtual ~VehicleExtension() = default;

        bool addCustomComponent(uint32_t component) override;
        int getCustomComponentInSlot(int slot) override;
        bool removeCustomComponent(uint32_t component) override;
        StaticArray<uint32_t, MAX_VEHICLE_COMPONENT_SLOT> getCustomComponents() override;

        // Inherited from IExtension
        void freeExtension() override;
        void reset() override;
    };
}


#endif //PEARS_VEHICLE_COMPONENTS_VEHICLEEXTENSION_H
