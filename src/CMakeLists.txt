include("${_build_cmake_local}")

message("Adding library: ${PISUBMARINE_MODULE_NAME}")
add_library(${PISUBMARINE_MODULE_NAME} INTERFACE
        "../public/PiSubmarine/Telemetry/Api/ISource.h"
        "../public/PiSubmarine/Telemetry/Api/Snapshot.h")
target_include_directories(${PISUBMARINE_MODULE_NAME} INTERFACE "../public")
PiSubmarineInitTarget(${PISUBMARINE_MODULE_NAME})

PiSubmarineAddDependency("https://github.com/PiSubmarine/Error.Api.git" "")
target_link_libraries(${PISUBMARINE_MODULE_NAME} INTERFACE PiSubmarine.Error.Api)

PiSubmarineAddDependency("https://github.com/PiSubmarine/Motor.Telemetry.Api.git" "")
target_link_libraries(${PISUBMARINE_MODULE_NAME} INTERFACE PiSubmarine.Motor.Telemetry.Api)

PiSubmarineAddDependency("https://github.com/PiSubmarine/Battery.Telemetry.Api.git" "")
target_link_libraries(${PISUBMARINE_MODULE_NAME} INTERFACE PiSubmarine.Battery.Telemetry.Api)

PiSubmarineAddDependency("https://github.com/PiSubmarine/Units.git" "")
target_link_libraries(${PISUBMARINE_MODULE_NAME} INTERFACE PiSubmarine.Units)
