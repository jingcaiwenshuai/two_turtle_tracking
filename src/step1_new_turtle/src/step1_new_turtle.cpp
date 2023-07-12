#include "ros/ros.h"
#include "turtlesim/Spawn.h"


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "new_turtle");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");

    client.waitForExistence();

    turtlesim::Spawn spawn;
    spawn.request.name = "turtle2";
    spawn.request.x = 5;
    spawn.request.y = 5;
    spawn.request.theta= 0;

    bool flag = client.call(spawn);
    if(flag)
    {
        ROS_INFO("%s创建成功!", spawn.response.name.c_str());
    }
    else
        ROS_INFO("%s创建失败~", spawn.response.name.c_str());
    return 0;
}