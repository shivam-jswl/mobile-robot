#include<iostream>
// #include<conio.h>
#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

geometry_msgs::Twist control_ip;
float speed=0, steering=0;
char ch;
bool stop = 0;
int handBreak = 0;


void get_key(){
    struct termios oldt;
	struct termios newt;

	// setting backup
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	// Make changes and apply the settings

	newt.c_lflag &= ~(ICANON | ECHO);
	newt.c_iflag |= IGNBRK;
	newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
	newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
	newt.c_cc[VMIN] = 1;
	newt.c_cc[VTIME] = 0;
	tcsetattr(fileno(stdin), TCSANOW, &newt);

	// Get the current character
	ch = getchar();

	// restore old settings
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void speed_direction(){
    
    if(stop != 1){
        get_key();
    }
    else
        ch = ' ';

    if(ch == 'd' || ch == 'A'){
        if(control_ip.angular.z > 0)
            control_ip.angular.z = 0;
        else    
            control_ip.angular.z = -50;
    }
    else if(ch == 'a' || ch == 'A'){
        if(control_ip.angular.z < 0)
            control_ip.angular.z = 0;
        else    
            control_ip.angular.z = 50;
    }

    else if(ch == 'w' || ch == 'W'){
        control_ip.linear.x += 500;
    }

    else if(ch == 's' || ch == 'S'){
        control_ip.linear.x -= 500;
    }

    else if( ch == ' '){
        control_ip.angular.z = 0;
        control_ip.linear.x = 0;
    }



    else if(ch == 'q' || ch == 'Q'){
        stop = 1;
        std::cout<<std::endl<<"Teleop stopped."<<std::endl;
    }

    if (ch != 'a' && ch != 'A' && ch != 'd' && ch != 'D'){
        control_ip.angular.z = 0;
    }
}

int main(int argc, char **argv){

    control_ip.linear.x = 0;
    control_ip.linear.y = 0;
    control_ip.linear.z = 0;
    control_ip.angular.x = 0;
    control_ip.angular.y = 0;
    control_ip.angular.z = 0;

    ros::init(argc, argv, "teleop_control");
    ros::NodeHandle nh;
    ros::Rate sleepTime(100);

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/telop_input_cmd", 1);
    pub.publish(control_ip);

    std::cout<<"Use following keys"<<std::endl<<"'q/Q' -> stop teleop"<<std::endl<<std::endl<<"'w/W' -> accelerate"<<std::endl<<"'s/S' -> deaccelerate"<<std::endl<<std::endl<<"'a/A' -> turn left"<<std::endl<<"'d/D' -> turn right"<<std::endl<<std::endl<<"'<space key>' -> brakes"<<std::endl;
    

    while(ros::ok()){

        speed_direction();
        pub.publish(control_ip);
        
        ros::spinOnce();
        sleepTime.sleep();
    }
    return 0;

}