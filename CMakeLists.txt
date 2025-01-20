cmake_minimum_required(VERSION 3.20)
project(pears_vehicle_components VERSION 0.0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
endif ()

add_library(pears_vehicle_components SHARED
        plugin.def
        PluginComponent.cpp
        vehicle-components/CustomVehicleComponents/natives.cpp
        vehicle-components/CustomVehicleComponents/CustomVehicleComponents.cpp
        vehicle-components/CustomVehicleComponents/CustomVehicleComponents.h
        vehicle-components/vehicle-components.h
        vehicle-components/CustomVehicleComponents/interface.h
        vehicle-components/CustomVehicleComponents/VehicleExtension.cpp
        vehicle-components/CustomVehicleComponents/VehicleExtension.h
        vehicle-components/CustomVehicleComponents/VehicleStreamedInListener.cpp
        vehicle-components/CustomVehicleComponents/VehicleStreamedInListener.h
)

add_subdirectory(third-party/open.mp-sdk)
add_subdirectory(third-party/open.mp-network)

add_compile_definitions(
        PLUGIN_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
        PLUGIN_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
        PLUGIN_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
        PLUGIN_VERSION_TWEAK=${CMAKE_PROJECT_VERSION_TWEAK}
        PLUGIN_NAME="${PROJECT_NAME}"
        HAVE_STDINT_H=1
        HAVE_ALLOCA_H=0
        PAWN_CELL_SIZE=32
)

target_include_directories(${PROJECT_NAME} PRIVATE
        third-party
        third-party/open.mp-network
        third-party/open.mp-sdk
        third-party/pawn/source
        third-party/pawn/include
        third-party/pawn/source/linux
	.
)
target_link_libraries(${PROJECT_NAME} PRIVATE OMP-SDK OMP-Network)
