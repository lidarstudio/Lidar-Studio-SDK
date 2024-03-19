project(LcPluginSample)

#find lib
find_path(SDK_ROOT
        HINTS "${SDK_ROOT}" "$ENV{SDK_ROOT}"
   )

#find qt
find_path(QT_ROOT
        HINTS "${QT_ROOT}" "$ENV{QT_ROOT}"
   )
  
set(CMAKE_AUTOMOC ON) 

if(EXISTS ${QT_ROOT})
   find_package(Qt5 COMPONENTS Widgets REQUIRED)
endif()

add_definitions (${QT_DEFINITIONS})

file(GLOB_RECURSE  SrcHpp *.h)
file(GLOB_RECURSE  SrcCpp *.cpp)
source_group("Include" FILES ${SrcHpp})
source_group("Source" FILES ${SrcCpp})

include_directories(${SDK_ROOT}/include)

add_library(${PROJECT_NAME} SHARED ${SrcHpp} ${SrcCpp} )

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core)
target_link_libraries(${PROJECT_NAME} optimized "${SDK_ROOT}/lib/LcPluginsSDK.lib")

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../bin) 