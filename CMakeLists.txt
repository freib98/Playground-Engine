cmake_minimum_required(VERSION 3.6)

project(PEngine, VERSION 0.1.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ------------------------------------------------------------
# Add glad
# ------------------------------------------------------------
add_subdirectory(dep/glad)

set_target_properties(glad PROPERTIES FOLDER dep)
set_target_properties(glad-generate-files PROPERTIES FOLDER dep)

# ------------------------------------------------------------
# Add playground engine
# ------------------------------------------------------------
add_subdirectory(pengine)

# ------------------------------------------------------------
# Add samples
# ------------------------------------------------------------
add_subdirectory(samples)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sample)
