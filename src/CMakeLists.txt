add_library(enemy entities/enemy.cpp)
add_library(hero entities/hero.cpp)

target_link_libraries(enemy PRIVATE project_options)
target_link_libraries(hero PRIVATE project_options)

