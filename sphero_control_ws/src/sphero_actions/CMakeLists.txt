cmake_minimum_required(VERSION 2.8.3)
project(sphero_actions)

add_compile_options(-std=c++14)
find_package(catkin REQUIRED COMPONENTS
  actionlib_msgs
  nav_msgs
  sphero_topics
  actionlib
  )

find_package(Boost REQUIRED)
## Generate actions in the 'action' folder
add_action_files(
FILES
record_odom.action
)
## Generate added messages and services with any dependencies listed here
generate_messages(
DEPENDENCIES
actionlib_msgs
actionlib
nav_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES
  ${PROJECT_NAME}_core
  CATKIN_DEPENDS actionlib_msgs nav_msgs sphero_topics
  DEPENDS Boost
)
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

## Declare a C++ library
 add_library(${PROJECT_NAME}_core
   src/sphero_maze_out.cpp
   src/odometry_analyse.cpp
 )
add_executable(${PROJECT_NAME}_server nodes/server.cpp)
add_executable(${PROJECT_NAME}_client nodes/client.cpp)

add_dependencies(${PROJECT_NAME}_core
 ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(${PROJECT_NAME}_core
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)
add_dependencies(${PROJECT_NAME}_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(${PROJECT_NAME}_client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
 target_link_libraries(${PROJECT_NAME}_server
   ${catkin_LIBRARIES}
   ${PROJECT_NAME}_core
 )
## Specify libraries to link a library or executable target against
 target_link_libraries(${PROJECT_NAME}_client
   ${catkin_LIBRARIES}
   ${PROJECT_NAME}_core
 )

install(TARGETS ${PROJECT_NAME}_core
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
 install(TARGETS ${PROJECT_NAME}_server
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )
install(TARGETS ${PROJECT_NAME}_client
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

 install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.hpp"
   PATTERN ".svn" EXCLUDE

)
