#include "ros/ros.h"
#include "my_service/QuadRoots.h"
#include <cmath>

bool roots(my_service::QuadRoots::Request &req,
	my_service::QuadRoots::Response &res) {

	float d = req.b * req.b - 4 * req.a * req.c;

	ROS_INFO("request: a=%f, b=%f, c=%f", req.a, req.b, req.c);

	if (d > 0) {

    		res.x1 = ((-req.b) + sqrt(d)) / (2 * req.a);
    		res.x2 = ((-req.b) - sqrt(d)) / (2 * req.a);
    		ROS_INFO("response: %f and %f", res.x1, res.x2);
  	}

  	if (d == 0) {

   		res.x1 = -(req.b / (2 * req.a));
		res.x2 = res.x1;
    		ROS_INFO("response: %f", res.x1);
  	}

  	if (d < 0) {

		// оба корня выведутся как нули, но в сервисе будет следующее сообщение:
    		ROS_INFO("response: no real roots");
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

