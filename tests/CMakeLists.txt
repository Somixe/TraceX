cmake_minimum_required(VERSION 3.16)

project(ExigenceTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Pour générer automatiquement les fichiers .moc nécessaires à Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(tst_exigence
    main.cpp
    tst_exigence.cpp
    ../../exigence.h
    ../../exigence.cpp
    tst_exigencesrs.cpp
    ../../exigencesrs.cpp
    tst_file.cpp
    ../../file.cpp
    tst_fileutils.cpp
    ../../FileUtils.cpp
    tst_rapport.cpp
    ../../rapport.cpp
    ../../rapportligne.cpp
    tst_sdd.cpp
    ../../sdd.cpp
    tst_srs.cpp
    ../../srs.cpp
    ../../sss.cpp
    tst_sss.cpp
    ../../style.cpp
    tst_style.cpp
    tst_stylefile.cpp
    ../../stylefile.cpp
    tst_tracabilite.cpp
    ../../tracabilite.cpp
    tst_xmlparserutils.cpp
    ../../xmlparserutils.cpp
    ../../../tracabilite/pugixml-1.15/pugixml-1.15/src/pugixml.hpp
    ../../pugixml-1.15/pugixml-1.15/src/pugixml.cpp
    tst_exigence.h
    tst_exigencesrs.h
    tst_file.h
    tst_fileutils.h
    tst_rapport.h
    tst_sdd.h
    tst_srs.h
    tst_sss.h
    tst_style.h
    tst_stylefile.h
    tst_tracabilite.h
    tst_xmlparserutils.h


)



# ⚠️ Important : déclarer comme une application console
set_target_properties(tst_exigence PROPERTIES WIN32_EXECUTABLE OFF)

# Inclure le dossier parent pour les headers
target_include_directories(tst_exigence PRIVATE ../)
find_package(Qt6 REQUIRED COMPONENTS Core Test Widgets)
target_link_libraries(tst_exigence PRIVATE Qt6::Core Qt6::Test Qt6::Widgets )

# Lier avec Qt Test



enable_testing()
add_test(NAME ExigenceTest COMMAND tst_exigence)

include(GNUInstallDirs)
install(TARGETS tst_exigence
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
