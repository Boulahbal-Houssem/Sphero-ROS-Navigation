cmake_minimum_required(VERSION 2.8.3)
project(sphero_crash_server)

add_compile_options(-std=c++14)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sphero_topics
  std_srvs
)
catkin_package(
  INCLUDE_DIRS
  include
  LIBRARIES $
  {PROJECT_NAME}_core
  CATKIN_DEPENDS
  roscpp sphero_topics std_srvs
#  DEPENDS system_lib
)

include_directories(
     include                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}_core
    src/server.cpp
    )

add_executable(${PROJECT_NAME}_server nodes/main.cpp)
add_dependencies(${PROJECT_NAME}_core  ${catkin_EXPORTED_TARGETS})
add_dependencies(${PROJECT_NAME}_server ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_server
   ${catkin_LIBRARIES}
    ${PROJECT_NAME}_core
  )
target_link_libraries(${PROJECT_NAME}_core
   ${catkin_LIBRARIES}
  )
#add_executable(${PROJECT_NAME}_client src/client.cpp)
#add_dependencies(${PROJECT_NAME}_client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(${PROJECT_NAME}_client
#   ${catkin_LIBRARIES}
#  )

install(TARGETS  ${PROJECT_NAME}_server
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
 install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.hpp"
   PATTERN ".svn" EXCLUDE
 )
