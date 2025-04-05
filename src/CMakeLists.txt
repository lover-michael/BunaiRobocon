add_library(module
    SHARED
        cobs.cpp
        controller.cpp
        communication.cpp
)

target_include_directories(
    module
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)