#pragma once

#include "CustomVehicleComponents/CustomVehicleComponents.h"

inline void componentsLoad(ICore *core, IComponentList* components) {
    CustomVehicleComponents::load(core, components);
}

inline void componentsUnloadComponent(IComponent* component) {
    CustomVehicleComponents::unloadComponent(component);
}

inline void componentsUnload() {
    CustomVehicleComponents::unload();
}