# CMakeList.txt : CMake project for Subproject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.18)

project (oht VERSION ${ohtest_VERSION})

set (PROJ_PATH "${CMAKE_SOURCE_DIR}")

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/config/config.h.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/config/config.h" @ONLY)

add_executable (${PROJECT_NAME})
target_sources (${PROJECT_NAME}
PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

target_include_directories (${PROJECT_NAME}
PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${OPENHOLO_ROOT_DIR}/include"
    ${CUDAToolkit_INCLUDE_DIRS}
)

target_link_libraries (${PROJECT_NAME}
    ${OPENHOLO_ROOT_DIR}/lib/libfftw*.lib
    "${CUDAToolkit_LIBRARY_DIR}/cudart.lib"
)
target_link_libraries (${PROJECT_NAME} optimized
    "${OPENHOLO_ROOT_DIR}/lib/openholo.lib"
    "${OPENHOLO_ROOT_DIR}/lib/ophgen.lib"
    "${OPENHOLO_ROOT_DIR}/lib/ophrec.lib"
    "${OPENHOLO_ROOT_DIR}/lib/ophsig.lib"
)
target_link_libraries (${PROJECT_NAME} debug
    ${OPENHOLO_ROOT_DIR}/lib/*_d.lib
)

if (WIN32)
    target_compile_definitions (${PROJECT_NAME}
    PUBLIC
        _CRT_SECURE_NO_WARNINGS
        ${PROJECT_NAME}_DLLEXPORT
    )
endif()

# Copy dll
file (GLOB OPENHOLO_DLLS "${OPENHOLO_ROOT_DIR}/dll/*.dll")
list (APPEND ${PROJECT_NAME}_LINK_DLLS ${OPENHOLO_DLLS})

foreach(dll ${${PROJECT_NAME}_LINK_DLLS})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${dll} "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
endforeach()

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copy openholo.dll to ${PROJECT_NAME} exe directory"
)

# Define install patterns (library project need install target)
# Install binaries
install (
    TARGETS ${PROJECT_NAME}
    CONFIGURATIONS Debug Release
    RUNTIME DESTINATION "bin"
    PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_EXECUTE GROUP_READ GROUP_WRITE WORLD_EXECUTE WORLD_READ
)
