#include "ros/ros.h"
#include "quad_service/QRoots.h"
#include <iostream>

int main(int argc, char **argv) {
    ros::init(argc,argv,"quad_roots_publisher");

    ros::NodeHandle n;
    ros::ServiceClient client=n.serviceClient<quad_service::QRoots>("quad_roots");
    quad_service::QRoots srv;

    while (ros::ok()) {

        int a,b,c;
        std::cout<<"input the A coefficient:";    
        std::cin>>a;
        std::cout<<"input the B coefficient:";    
        std::cin>>b;
        std::cout<<"input the C coefficient:";    
        std::cin>>c;

        srv.request.a = a;
        srv.request.b = b;
  	srv.request.c = c;

	float d = b * b - 4 * a * c;

        if (client.call(srv)) {

		if (d > 0) {
            		ROS_INFO("[%f %f]", srv.response.x[0], srv.response.x[1]);
		}
		if (d == 0) {
            		ROS_INFO("[%f]", srv.response.x[0]);
		}
		if (d < 0) {
            		ROS_INFO("[ ]");
		}
        }

        else {
            std::cout<<"Failed to call service"<<std::endl;
            return 1;
        }
    }

    return 0;
}
