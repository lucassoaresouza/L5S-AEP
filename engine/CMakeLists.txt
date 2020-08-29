# Creating Variables

set(ENGINE_INCLUDE "${PROJECT_SOURCE_DIR}/engine/include")
set(ENGINE_SRC "${PROJECT_SOURCE_DIR}/engine/src")
file(GLOB_RECURSE SOURCES "${ENGINE_SRC}/*.cpp")

# Including headers
include_directories(${ENGINE})
include_directories(${ENGINE_INCLUDE})

add_library(engine STATIC ${SOURCES})
set_property(TARGET engine PROPERTY CXX_STANDARD 11)
