# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(TridentTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(Trident_test source/Trident_test.cpp)
target_link_libraries(
    Trident_test PRIVATE
    Trident_lib
    Catch2::Catch2WithMain
)
target_compile_features(Trident_test PRIVATE cxx_std_20)

catch_discover_tests(Trident_test)

# ---- End-of-file commands ----

add_folders(Test)
