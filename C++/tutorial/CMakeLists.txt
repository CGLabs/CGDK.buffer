#*****************************************************************************
#*                                                                           *
#*                      Cho sanghyun's Game Classes II                       *
#*                      Ver 10.0 / release 2019.12.11                        *
#*                                                                           *
#*                         CMake - tutorial.buffer                           *
#*                                                                           *
#*                                                                           *
#*                                                                           *
#*                                                                           *
#*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
#*  Best for Game Developement and Optimized for Game Developement.          *
#*                                                                           *
#*                (c) 2016 Cho Sanghyun All right reserved.                  *
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
set ( DEFAULT_BUILD_TYPE Debug )

# 3) project name
PROJECT ( "CGDK.tutorial.buffer" )

#-----------------------------------------------------------------------------
# compile
#-----------------------------------------------------------------------------
# 1) basic
ADD_SUBDIRECTORY (buffer.01.basic)

# 2) append_extract
ADD_SUBDIRECTORY (buffer.02.buffer_operator)

# 3) struct_serialize
ADD_SUBDIRECTORY (buffer.03.struct_serialize)

# 4) Ibuffer_serializable
ADD_SUBDIRECTORY (buffer.04.Ibuffer_serializable)

# 4) static_buffer
ADD_SUBDIRECTORY (buffer.06.static_buffer)
