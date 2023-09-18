cmake_minimum_required(VERSION 2.8.3)

project(autonomous_jeep_steering)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	rospy
	std_msgs
	gazebo_ros
	joint_state_publisher_gui
	joint_state_publisher
	robot_state_publisher
	rviz
	roslaunch
	geometry_msgs
)

catkin_package()


include_directories(
	${catkin_INCLUDE_DIRS}
)

find_package(roslaunch)

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)



add_executable(control_key src/teleop/control_key.cpp)

target_link_libraries(control_key ${catkin_LIBRARIES})
