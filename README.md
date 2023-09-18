# mobile-robot
<h3>Author: Shivam Jaiswal<br>
    Connect: https://shivamjaiswal.free.nf
</h3>
ROS packages containing various operations on wheeled mobile robot.

<h2>1. Teleop motion</h2>
<h3>Concerning directory 1: <i>mobile_robot</i></h3>
Controls a 4 wheeled mobile robot using <i><b>mobile_robot/src/control_key.cpp</b></i> node. Steering of the wheels is based on differential drive.
It contains URDF model of the robot in <i><b>mobile_robot/urdf</b></i> directory and its launch file in <i><b>mobile_robot/launch</b></i> directory.

<h3>Concerning directory 2: <i>autonomous_jeep_steering</i></h3>
Controls a 4 wheeled mobile jeep-robot with lidar and camera using <i><b>autonomous_jeep_steering/src/teleop/control_key.cpp</b></i> node. Steering of the wheels is based on differential drive. It contains URDF model of the robot in <i><b>autonomous_jeep_steering/urdf</b></i> directory and its launch file in <i><b>autonomous_jeep_steering/launch</b></i> directory. Future: autonomous behaviour using Bug algorithm.


<h2>Notes</h2>
Copy and paste each package in your ${catkin workspace}/src
