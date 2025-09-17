cmake_minimum_required(VERSION 3.16)

project(tracabilite VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tracabilite
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ../tracabilite/pugixml-1.15/pugixml-1.15/src/pugixml.cpp
        FileUtils.cpp

        StyleCharacteristics.h


        FileUtils.h
        style.h style.cpp

        style_exigence.h style_exigence.cpp style_exigence.ui
        Images.qrc
        exigence.h exigence.cpp
        exigencesrs.h exigencesrs.cpp
        file.h file.cpp
        sss.h sss.cpp
        stylefile.h stylefile.cpp
        srs.h srs.cpp
        sdd.h sdd.cpp
        nodeitem.h nodeitem.cpp
        linkitem.h linkitem.cpp
        graphe.h graphe.cpp
        TypeFile.h
        fenetregraphe.h fenetregraphe.cpp
        qlistwidget_custom.h qlistwidget_custom.cpp
        qtreewidget_custom.h qtreewidget_custom.cpp
        tracabilite.h tracabilite.cpp

        xmlparserutils.h xmlparserutils.cpp
        fenetrestatistiques.h fenetrestatistiques.cpp
        tracabilite.h tracabilite.cpp
        fenetreexigences.h fenetreexigences.cpp
        rapport.h rapport.cpp
        rapportligne.h rapportligne.cpp




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET tracabilite APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(tracabilite SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(tracabilite
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(tracabilite PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.tracabilite)
endif()
set_target_properties(tracabilite PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS tracabilite
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tracabilite)
endif()
