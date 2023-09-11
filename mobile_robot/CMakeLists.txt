cmake_minimum_required(VERSION 2.8.3)

project(mobile_robot)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	rospy
	std_msgs
	controller_manager
	joint_state_controller
	robot_state_publisher
	geometry_msgs
)

catkin_package(
	CATKIN_DEPENDS controller_manager joint_state_controller robot_state_publisher
)
include_directories(
	${catkin_INCLUDE_DIRS}
)


add_executable(control_key src/control_key.cpp)

target_link_libraries(control_key
	${catkin_LIBRARIES}
)

find_package(roslaunch)

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)
