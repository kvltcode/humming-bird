project(HummingBird)

add_executable(${PROJECT_NAME} main.cpp
                            
                        ${CMAKE_SOURCE_DIR}/resources/flower1.png
                        ${CMAKE_SOURCE_DIR}/resources/flower2.png
                        ${CMAKE_SOURCE_DIR}/resources/flower3.png
                        ${CMAKE_SOURCE_DIR}/resources/flower4.png
                        ${CMAKE_SOURCE_DIR}/resources/flower5.png
                        ${CMAKE_SOURCE_DIR}/resources/ground.png
                        ${CMAKE_SOURCE_DIR}/resources/vine.png
                        ${CMAKE_SOURCE_DIR}/resources/background-vine.png
                        ${CMAKE_SOURCE_DIR}/resources/bird.png
                        ${CMAKE_SOURCE_DIR}/resources/icon.png
                        ${CMAKE_SOURCE_DIR}/resources/particle.png
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)


target_link_libraries(${PROJECT_NAME} game)
target_link_libraries(${PROJECT_NAME} gameobject)

add_subdirectory(Game)
add_subdirectory(GameObject)
add_subdirectory(Utility)


add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/resources/
                $<TARGET_FILE_DIR:HummingBird>/resources
                COMMENT "Moving images to target"
                VERBATIM)