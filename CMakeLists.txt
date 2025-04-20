cmake_minimum_required(VERSION 3.16)

project(SMI-Code-Checker VERSION 0.1 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "C:/Qt/6.9.0/mingw_64/lib/cmake")

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64/lib/cmake/Qt6" ${CMAKE_PREFIX_PATH})
set(CMAKE_C_COMPILER "C:/Qt/Tools/mingw1310_64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Qt/Tools/mingw1310_64/bin/g++.exe")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${Qt${QT_VERSION_MAJOR}_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

qt_add_executable(SMI-Code-Checker
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    projectpage.h projectpage.cpp projectpage.ui
    report.h report.cpp report.ui
    SourceCodeFile.h SourceCodeFile.cpp
    StaticAnalysisTools.h StaticAnalysisTools.cpp
    AnalysisResult.h AnalysisResult.cpp
    Vulnerability.h Vulnerability.cpp
    ReportGenerator.h ReportGenerator.cpp
)

target_link_libraries(SMI-Code-Checker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SMI-Code-Checker)
endif()
set_target_properties(SMI-Code-Checker PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SMI-Code-Checker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SMI-Code-Checker)
endif()