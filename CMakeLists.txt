cmake_minimum_required(VERSION 3.14)

project(PolygonsMap VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "/home/hryapusek/lib/qtbuild")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets REQUIRED)

message(STATUS "Including FetchContent")
include(FetchContent)

message(STATUS "Loading jsoncpp")
FetchContent_Declare(
  jsoncpp
  GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
  GIT_TAG        master
)

message(STATUS "Making jsoncpp available")
FetchContent_MakeAvailable(jsoncpp)
message(STATUS "jsoncpp added successfully")

set(PROJECT_SOURCES
        src/main.cpp
        resources/qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PolygonsMap
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PolygonsMap APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PolygonsMap SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PolygonsMap
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(PolygonsMap
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(PolygonsMap
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Widgets jsoncpp_lib)

set_target_properties(PolygonsMap PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(PolygonsMap)
    qt_finalize_executable(PolygonsMap)
endif()

target_include_directories(PolygonsMap
    PRIVATE
    ./include/public
    )

target_sources(PolygonsMap
    PUBLIC

    include/public/shapes/DraggableEllipse.h
    src/shapes/DraggableEllipse.cpp

    include/public/shapes/PolygonItem.h
    src/shapes/PolygonItem.cpp

    include/public/models/PolygonPointModel.h
    src/model/PolygonPointModel.cpp

    include/public/scene/CustomScene.h
    src/scene/CustomScene.cpp

    include/public/scene/SceneItem.h
    src/scene/SceneItem.cpp

    include/public/geometry/Geometry.h
    src/geometry/Geometry.cpp

    include/public/shapes/PolygonBuilder.h
    src/shapes/PolygonBuilder.cpp

    include/public/json/JsonUtils.h
    src/json/JsonUtils.cpp

    include/public/json/Serialization.h

    src/main.cpp
)
