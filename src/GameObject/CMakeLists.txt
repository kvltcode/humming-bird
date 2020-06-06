project(gameobject)

add_library(${PROJECT_NAME}  
    GameObject.h
    
    Player.cpp
    Player.h
    
    Flower.cpp
    Flower.h
    
    BoundingRect.h

    Ground.cpp
    Ground.h

    Vine.cpp
    Vine.h

    BackgroundVine.cpp
    BackgroundVine.h

    ParticleGenerator.cpp
    ParticleGenerator.h
    Particle.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/resources)

target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} game)
target_link_libraries(${PROJECT_NAME} utility)