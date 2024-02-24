project (domain)

add_library(${PROJECT_NAME} STATIC
            game.cc
            map.cc
            random_map_generator.cc
            map_object/map_object.cc
            map_object/obstacle.cc
            map_object/treasure.cc
            map_object/role/role.cc
            map_object/role/character.cc
            map_object/role/monster.cc
            map_object/role/state/state.cc
            map_object/role/state/normal_state.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})