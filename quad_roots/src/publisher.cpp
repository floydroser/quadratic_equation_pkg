
#include "ros/ros.h"
#include "my_service/QuadRoots.h"
#include <iostream>

int main(int argc, char **argv) {
    ros::init(argc,argv,"quad_roots_publisher");

    ros::NodeHandle n;
    ros::ServiceClient client=n.serviceClient<my_service::QuadRoots>("quad_roots");
    my_service::QuadRoots srv;

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

        if (client.call(srv)) {
            std::cout<<"roots: "<<srv.response.x1<<" and "<<srv.response.x2<<std::endl;
        }

        else {
            std::cout<<"Failed to call service"<<std::endl;
            return 1;
        }
    }

    return 0;
}

