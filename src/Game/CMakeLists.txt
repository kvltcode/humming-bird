project(game)

add_library(${PROJECT_NAME}  Game.cpp
    Game.h
    Global.h

    Foreground.h
    Foreground.cpp

    Background.h
    Background.cpp

    Screen.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} gameobject)