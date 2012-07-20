
############ offline

project( network )
cmake_minimum_required(VERSION 2.6.0)

########### Dependencies

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

########### Sources

set( network_srcs 
	NetMon.cpp
	SocketReader.cpp
   )

set( network_headers 
	NetMon.h 
	SocketReader.h
   )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

############ Qt4 goodness

Qt4_wrap_cpp(network_headers_moc ${network_headers})
Qt4_wrap_ui(network_forms_headers ${network_forms})

add_library(network
    STATIC
    ${network_srcs}
    ${network_headers_moc}
    ${network_forms_headers} )

target_link_libraries(
  network
  viewer
  manpreloader
  ${QT_LIBRARIES}
  )

# Copy files from source directory to destination directory, substituting any
# variables.  Create destination directory if it does not exist.
# http://stackoverflow.com/questions/697560/how-to-copy-directory-from-source-tree-to-binary-tree

macro(copy_py_sources srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB_RECURSE templateFiles RELATIVE ${srcDir} ${srcDir}/*.py)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    @ONLY)
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(copy_py_sources)

add_dependencies( network man )

copy_py_sources( ${MAN_SRC_DIR} ${CMAKE_BINARY_DIR}/man )
