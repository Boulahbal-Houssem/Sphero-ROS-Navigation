#include <ros/ros.h>
#include <sphero_actions/sphero_maze_out.hpp>
int main(int argc, char **argv )
{
    ros::init(argc ,argv, "record_odom_action_server_node");
    sphero_actions::RecordOdom rod("/rec_odom_as",2.0);
    rod.as_.start();
    ros::Rate rate(1);
    ros::spin();
    return 0;
}
