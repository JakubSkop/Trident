cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    Trident
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# ---- Declare library ----

add_library(
    Trident_lib OBJECT
    source/lib.cpp
    source/Graphics/Arrow.cpp
    source/Engine/Geometry/Shapes.cpp
)

target_include_directories(
    Trident_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(Trident_lib PUBLIC cxx_std_23)

##find_package(blaze CONFIG REQUIRED)
target_link_libraries(Trident_lib PRIVATE SFML::Graphics)

# ---- Declare executable ----

add_executable(Trident_exe source/main.cpp)
add_executable(Trident::exe ALIAS Trident_exe)

set_property(TARGET Trident_exe PROPERTY OUTPUT_NAME Trident)

target_compile_features(Trident_exe PRIVATE cxx_std_20)

target_link_libraries(Trident_exe PRIVATE Trident_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT Trident_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of Trident"
  )
endif()

include(cmake/dev-mode.cmake)
