//
// Created by moreveal on 24.12.2024.
//

#include "CustomVehicleComponents.h"

namespace CustomVehicleComponents {
    void load(ICore* icore, IComponentList* components) {
        core = icore;

        { // Register Vehicle StreamedIn RPC Handler
            const auto& networks = core->getNetworks();
            for (auto* network : networks)
            {
                network->getPerRPCOutEventDispatcher().addEventHandler(&vehicleStreamedInListener, CustomVehicleComponents::VehicleStreamedInListener::kRpcId, EventPriority_Highest);
            }
        }

        vehicleStreamedInListener.onLoad(icore, components);
    }

    void unload() {
        if (core)
        {
            const auto& networks = core->getNetworks();
            for (auto* network : networks)
            {
                network->getPerRPCOutEventDispatcher().removeEventHandler(&vehicleStreamedInListener, CustomVehicleComponents::VehicleStreamedInListener::kRpcId);
            }
        }

        core = nullptr;
    }

    void unloadComponent(IComponent* component)
    {
        /* Nothing to do */
    }

    void setCustomComponentSlot(uint32_t component, int slot)
    {
        vehicleComponents[component] = slot;
    }

    int getCustomComponentSlot(uint32_t component)
    {
        if (const auto& slot = vehicleComponents.find(component); slot != vehicleComponents.cend())
            return slot->second;
        return -1;
    }
}