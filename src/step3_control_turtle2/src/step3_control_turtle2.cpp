#include "ros/ros.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/Twist.h"

/*
    需求1：换算出turtle1相对于turtle2的关系
    需求2：计算角速度与线速度并发布
*/

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "control_turtle2");
    ros::NodeHandle nh;

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);

    //1、创建发布对象
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 1000);

    ros::Rate rate(10);
    while (ros::ok())
    {
        try
        {
            geometry_msgs::TransformStamped tfs = buffer.lookupTransform("turtle2", "turtle1", ros::Time(0));
            ROS_INFO("turtle1相对于turtle2的信息:父级:%s,子级:%s,偏移量(%.2f, %.2f, %.2f)",
                                    tfs.header.frame_id.c_str(),//turtle2
                                    tfs.child_frame_id.c_str(),//turtle1
                                    tfs.transform.translation.x,
                                    tfs.transform.translation.y,
                                    tfs.transform.translation.z);
            //2、根据相对关系计算并组织速度信息
            geometry_msgs::Twist twist;
            /*
                组织速度，只需设置线速度的x与角速度的z
                            x = 系数 * (y*y + x*x)
                            z = 系数 * 反正切(对边/邻边)
            */
            twist.linear.x = 1 * sqrt(pow(tfs.transform.translation.x, 2) + pow(tfs.transform.translation.y, 2));
            twist.angular.z = 2 * atan2(tfs.transform.translation.y , tfs.transform.translation.x);

            pub.publish(twist);
        }
        catch(const std::exception& e)
        {
            ROS_INFO("异常信息:%s",e.what());
        }
        
        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}