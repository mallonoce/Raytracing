#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#-------------------------------------------------------------------------------
#	SOURCE CODE
#-------------------------------------------------------------------------------


# .h files
list(APPEND HEADER_FILES
	include/header.h
	include/camera.h
	include/ray.h
	include/hittable.h
	include/stb/stb_image.h
	include/stb/stb_image_write.h
	include/stb/stb_image_resize.h
)

# .cpp files
list(APPEND SOURCE_FILES
src/main.cpp
src/source.cpp
)

# include dir
list(APPEND INCLUDE_DIRS
include
)


# on windows, append headers to source so they show up in visual studio
if(WIN32)
	LIST(APPEND SOURCE_FILES ${HEADER_FILES})
endif()

#-------------------------------------------------------------------------------
#	PROJECT SETTINGS
#-------------------------------------------------------------------------------

set(TARGET_NAME raytracing-in-a-weekend)

# Use git branch as project name if clones from git
find_package(Eigen3)

# Set the project name
PROJECT(${PROJECT_NAME})

#-------------------------------------------------------------------------------
#	RESOURCES
#-------------------------------------------------------------------------------

#list(APPEND RESOURCES
#resources/resources.rc
#)

#-------------------------------------------------------------------------------
#	COMPILE FLAGS
#-------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
	add_compile_options(/MP)
	add_compile_options(/std:c++17)
elseif(CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(-std=c++17)
endif(MSVC)

#-------------------------------------------------------------------------------
#	CONFIGURATION
#-------------------------------------------------------------------------------

set(APPLICATION_NAME ${TARGET_NAME})
set(APPLICATION_VERSION ${VERSION})
set(APPLICATION_ORGANIZATION "Antonio Tammaro")
set(APPLICATION_ORGANIZATION_DOMAIN "https://github.com/mallonoce/")

configure_file(src/appinfo.h.in appinfo.h @ONLY NEWLINE_STYLE UNIX)

#-------------------------------------------------------------------------------
#	SOURCE GROUPS
#-------------------------------------------------------------------------------

source_group(generated REGULAR_EXPRESSION ".*_automoc.cpp")
source_group(resources REGULAR_EXPRESSION ".*[.][q]?rc")
source_group(source REGULAR_EXPRESSION ".*[.]cpp")
source_group(headers REGULAR_EXPRESSION ".*[.]h")
source_group(continuous-integration REGULAR_EXPRESSION ".*[.]yml")

#-------------------------------------------------------------------------------
#	ADDITIONAL LIBRARIES
#-------------------------------------------------------------------------------

# list(APPEND LIBRARIES
# 
# )
# 
# # Remove duplicate library dependencies. 
# list(REMOVE_DUPLICATES LIBRARIES)

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------


# Generate the executable
add_executable(${TARGET_NAME} ${SOURCE_FILES} ${RESOURCES})

# Set additional include directories
target_include_directories(${TARGET_NAME} PUBLIC ${INCLUDE_DIRS})

# link libraries
target_link_libraries(${TARGET_NAME} PUBLIC  Eigen3::Eigen) #${LIBRARIES}

# Use the automatically determined RPATH values
set_target_properties(${TARGET_NAME} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)


#INSTALL(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin)
#INCLUDE(InstallRequiredSystemLibraries)
