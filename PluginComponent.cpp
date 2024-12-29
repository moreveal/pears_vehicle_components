#include "PluginComponent.h"

#include "Server/Components/Pawn/Impl/pawn_natives.hpp"
#include "Server/Components/Pawn/Impl/pawn_impl.hpp"

#include "vehicle-components/CustomVehicleComponents/VehicleExtension.h"
#include "vehicle-components/vehicle-components.h"

StringView PluginComponent::componentName() const {
    return PLUGIN_NAME;
}

SemanticVersion PluginComponent::componentVersion() const {
    return {PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_PATCH, PLUGIN_VERSION_TWEAK};
}

void PluginComponent::onLoad(ICore *c) {
    core = c;
    setAmxLookups(core);
}

void PluginComponent::onInit(IComponentList *components) {
    pawnComponent = components->queryComponent<IPawnComponent>();
    if (pawnComponent == nullptr) return;

    pawnComponent->getEventDispatcher().addEventHandler(this);
    setAmxFunctions(pawnComponent->getAmxFunctions());
    setAmxLookups(components);

    vehicles_ = components->queryComponent<IVehiclesComponent>();
    if (vehicles_)
    {
        vehicles_->getPoolEventDispatcher().addEventHandler(this);
    }

    componentsLoad(core, components);
}

void PluginComponent::onAmxLoad(IPawnScript& script) {
    pawn_natives::AmxLoad(script.GetAMX());
}

void PluginComponent::onAmxUnload(IPawnScript &script) {
    /* Nothing to do */
}

void PluginComponent::onFree(IComponent *component) {
    if (component == pawnComponent) {
        pawnComponent = nullptr;
        setAmxFunctions();
        setAmxLookups();
    } else if (component == vehicles_) {
      vehicles_ = nullptr;
    }
    componentsUnloadComponent(component);
}

void PluginComponent::reset() {
    /* Nothing to do */
}

void PluginComponent::free() {
    componentsUnload();
    if (vehicles_) vehicles_->getPoolEventDispatcher().removeEventHandler(this);
    if (pawnComponent) pawnComponent->getEventDispatcher().removeEventHandler(this);
}

PluginComponent *PluginComponent::instance() {
    static PluginComponent component;
    return &component;
}

void PluginComponent::onPoolEntryCreated(IVehicle &vehicle) {
    using namespace CustomVehicleComponents;
    vehicle.addExtension(new VehicleExtension(vehicle), true);
}

COMPONENT_ENTRY_POINT() { return PluginComponent::instance(); }