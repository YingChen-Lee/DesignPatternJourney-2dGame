project (domain)

aux_source_directory(map_object/treasure TREASER_SRC)

add_library(${PROJECT_NAME} STATIC
            game.cc
            map.cc
            random_map_generator.cc
            map_object/map_object.cc
            map_object/character.cc
            map_object/monster.cc
            map_object/obstacle.cc
            map_object/role.cc
            map_object/treasure.cc
)


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})