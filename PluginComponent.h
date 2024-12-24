#ifndef PEARS_VEHICLE_COMPONENTS_PLUGINCOMPONENT_H
#define PEARS_VEHICLE_COMPONENTS_PLUGINCOMPONENT_H

#include "component.hpp"
#include "Server/Components/Pawn/pawn.hpp"
#include "Impl/pool_impl.hpp"
#include "bitstream.hpp"
#include "packet.hpp"

class PluginComponent final : public IComponent, public PawnEventHandler, public PoolEventHandler<IVehicle> {
private:
    ICore* core = nullptr;
    IVehiclesComponent* vehicles_ = nullptr;
    IPawnComponent *pawnComponent = nullptr;

public:
    PROVIDE_UID(0xD746DE6D9857E871);

    // Inherited from IComponent
    [[nodiscard]] StringView componentName() const override;
    [[nodiscard]] SemanticVersion componentVersion() const override;
    void onLoad(ICore *c) override;
    void onInit(IComponentList *components) override;
    void onFree(IComponent *component) override;
    void reset() override;
    void free() override;

    // Inherited from PawnEventHandler
    void onAmxLoad(IPawnScript &script) override;
    void onAmxUnload(IPawnScript &script) override;

    // Inherited from PoolEventHandler<IVehicle>
    void onPoolEntryCreated(IVehicle& vehicle) override;

    IVehiclesComponent* getVehicles();

    static PluginComponent *instance();

    ~PluginComponent();
};

#endif //PEARS_VEHICLE_COMPONENTS_PLUGINCOMPONENT_H
