#include "ros/ros.h"
#include "quad_service/QRoots.h"
#include <cmath>
#include <cstdlib>

bool roots(quad_service::QRoots::Request &req,
  quad_service::QRoots::Response &res) {

  float d = req.b * req.b - 4 * req.a * req.c;

  ROS_INFO("request: a=%f, b=%f, c=%f", req.a, req.b, req.c);

  if (d > 0) {
    
    	res.x.resize(2);
    
        res.x[0] = ((-req.b) + sqrt(d)) / (2 * req.a);
        res.x[1] = ((-req.b) - sqrt(d)) / (2 * req.a);
        ROS_INFO("[x1 = %f, x2 = %f]", res.x[0], res.x[1]);
    }

    if (d == 0) {
    
    	res.x.resize(1);
        res.x[0] = -(req.b / (2 * req.a));
        ROS_INFO("x = [%f]", res.x[0]);
    }

    if (d < 0) {
	res.x.resize(0);
        ROS_INFO("no real roots");
  }

  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "quad_roots_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("quad_roots", roots);
  ROS_INFO("Ready to find roots");
  ros::spin();

  return 0;
}
