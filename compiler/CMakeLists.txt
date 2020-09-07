find_package(BISON)
find_package(FLEX)

set(COMPILER_INCLUDE "${PROJECT_SOURCE_DIR}/compiler")
set(COMPILER_SRC "${PROJECT_SOURCE_DIR}/compiler")
file(GLOB_RECURSE SOURCES "${COMPILER_SRC}/*.cpp")

BISON_TARGET(l5sParser parser.yy ${COMPILER_SRC}/parser.cpp)
FLEX_TARGET(l5sScanner scanner.ll ${COMPILER_SRC}/parser.yy)
ADD_FLEX_BISON_DEPENDENCY(l5sScanner l5sParser)

include_directories(${COMPILER})
include_directories(${COMPILER_SRC})

add_library(compiler
STATIC ${SOURCES}
${BISON_l5sParser_OUTPUTS}
${FLEX_l5sScanner_OUTPUTS}
)
set_property(TARGET compiler PROPERTY CXX_STANDARD 11)
