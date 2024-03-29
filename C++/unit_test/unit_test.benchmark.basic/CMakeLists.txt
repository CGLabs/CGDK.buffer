#*****************************************************************************
#*                                                                           *
#*                               CGDK::buffer                                *
#*                       ver 3.03 / release 2023.10.17                       *
#*                                                                           *
#*               CMake - CGDK.buffer.unit_test.benchbmark.basic              *
#*                                                                           *
#*                                                                           *
#*                                                                           *
#*                                                                           *
#*  programmed by Cho SangHyun. sangduck@cgcii.com                           *
#*                                                                           *
#*                          http://www.CGCII.co.kr                           *
#*                                                                           *
#*****************************************************************************

#-----------------------------------------------------------------------------
# setting
#-----------------------------------------------------------------------------
# 1) build version
CMAKE_MINIMUM_REQUIRED ( VERSION 3.20 )
CMAKE_POLICY( VERSION 3.20 )

# 2) project version
SET ( PROJECT_VERSION_MAJOR 10 )
SET ( PROJECT_VERSION_MINOR 0 )
SET ( PROJECT_VERSION_PATCH 100 )
SET ( PROJECT_VERSION_TWEAK 1 )

# 3) project name
PROJECT ( "CGDK.buffer.unit_test.benchbmark.basic" )

# 4) default BUILD_TYPE
IF (NOT DEFINED CMAKE_BULD_TYPE)
	SET (CMAKE_BULD_TYPE "Debug")
ENDIF()

# 5) directories
SET ( CMAKE_RUNTIME_OTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../execute )
SET ( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../execute )

# 6) compile options
set ( CMAKE_CXX_STANDARD 20)
set ( CMAKE_CXX_STANDARD_REQUIRED ON)
SET ( CMAKE_CXX_FLAGS "-DC_FLAGS -fexceptions -std=c++20" )
SET ( CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -g3 -Wall -Wextra" )
SET ( CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -Wall -Wextra" )

# 7) include directories
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/../../include/
	/snap/flatbuffers/current/include/
	./
	${GTEST_INCLUDE_DIRS}
)

# 8) library directories
LINK_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/../execute/
	/snap/flatbuffers/current/lib/
)

# 9) requires
FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(Protobuf REQUIRED)


#-----------------------------------------------------------------------------
# source files
#-----------------------------------------------------------------------------
SET (SRC_FILES
#pre-compiled header
pch.cpp

#test
common_data.cpp
test_cgdk.cpp
test_flatbuffers.cpp
test_protobuf.cpp
protobuf/messages_test.pb.cc
)

# compile IDL
ADD_SUBDIRECTORY(protobuf)
ADD_SUBDIRECTORY(flatbuffers)


#-----------------------------------------------------------------------------
# compile
#-----------------------------------------------------------------------------
# 1) set variable
IF (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	SET (BUILD_MESSAGE "Debug")
	SET (BUILD_TYPE "Debug")
ELSEIF (${CMAKE_BUILD_TYPE} MATCHES "Release")
	SET (BUILD_MESSAGE "Release")
	SET (BUILD_TYPE "Release")
ELSE ()
	MESSAGE (SEND_ERROR "'CMAKE_BUILD_TYPE' is not mathed")
ENDIF ()

# 2) messages
MESSAGE (STATUS "compile ${PROJECT_NAME}")
MESSAGE (STATUS "  - configure['${BUILD_MESSAGE}']")

# 3) executable
ADD_EXECUTABLE(${PROJECT_NAME}.${BUILD_TYPE} ${SRC_FILES})

# 4) link
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}.${BUILD_TYPE}
	${GTEST_LIBRARIES}
	${GTEST_MAIN_LIBRARIES}
	protobuf
	flatbuffers
	rt
	pthread
)
