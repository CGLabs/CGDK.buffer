#*****************************************************************************
#*                                                                           *
#*                      Cho sanghyun's Game Classes II                       *
#*                      Ver 10.0 / release 2019.12.11                        *
#*                                                                           *
#*                        CMake - flatbuffer compile                         *
#*                                                                           *
#*                                                                           *
#*                                                                           *
#*                                                                           *
#*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
#*  Best for Game Developement and Optimized for Game Developement.          *
#*                                                                           *
#*                (c) 2003. Cho Sanghyun. All right reserved.                *
#*                          http://www.CGCII.co.kr                           *
#*                                                                           *
#*****************************************************************************

#-----------------------------------------------------------------------------
# flatbuffers
#-----------------------------------------------------------------------------
EXECUTE_PROCESS(COMMAND flatc -c messages_test_1.fbs
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

EXECUTE_PROCESS(COMMAND flatc -c messages_test_2.fbs
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

EXECUTE_PROCESS(COMMAND flatc -c messages_test_3.fbs
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

EXECUTE_PROCESS(COMMAND flatc -c messages_test_4.fbs
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

EXECUTE_PROCESS(COMMAND flatc -c messages_test_5.fbs
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
