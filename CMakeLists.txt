cmake_minimum_required(VERSION 3.16)

project(FlagsQuizII VERSION 2.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")

find_package(Qt6 COMPONENTS Quick REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Network REQUIRED)

qt_add_executable(appFlagsQuizII
    main.cpp classsetupflags.cpp classsetupflags.h  classgamequiz.cpp classgamequiz.h
    ${APP_ICON_RESOURCE_WINDOWS}
)

qt_add_qml_module(appFlagsQuizII
    URI FlagsQuizII
    VERSION 2.0
    QML_FILES
        main.qml
        FButton.qml
        FAnimButton.qml
        FAppMenu.qml
        FDownloadPage.qml
        FMessageBox.qml
        GameMenu.qml
        FQuestionBox.qml
        FGamePage.qml
    RESOURCES
        images/Joker50.png
        images/JokerTel.png
        images/JokerPub.png
        images/IconAppFlags.png
        images/IconAppFlags.svg
        images/3Points.svg
        images/Info.svg
        images/Settings.svg
)

set_target_properties(appFlagsQuizII PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appFlagsQuizII
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appFlagsQuizII
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Core
    PRIVATE Qt6::Network
)
