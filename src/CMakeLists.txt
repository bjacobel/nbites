###### project visionsim

cmake_minimum_required(VERSION 2.8.0)
project( visionsim )

###### dependencies

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

###### sources

set( sim_srcs main.cpp
)

###### subdirectories
add_subdirectory( gui )
add_subdirectory( model )

###### executable

add_executable(visionsim
  ${sim_srcs} )

target_link_libraries(
  visionsim
  gui
  model
)
