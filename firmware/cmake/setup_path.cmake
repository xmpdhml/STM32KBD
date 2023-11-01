include_directories(
    ${CMSIS_PATH}/Include
    ${DEVICE_PATH}/Include
    ${HAL_PATH}/Inc
    ${HAL_PATH}/Inc/Legacy
    ${CMAKE_SOURCE_DIR}/code/include
)

file(GLOB SOURCES
    ${DEVICE_PATH}/Source/Templates/*.c
    ${HAL_PATH}/Src/*.c
    ${CMAKE_SOURCE_DIR}/code/src/*.c
)

foreach(SOURCE ${SOURCES})
    if(SOURCE MATCHES ".*_template\\.c")
        list(REMOVE_ITEM SOURCES ${SOURCE})
    endif()
endforeach()
