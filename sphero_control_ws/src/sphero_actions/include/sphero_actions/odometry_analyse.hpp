#ifndef ODOMETRY_ANALYSE_HPP
#define ODOMETRY_ANALYSE_HPP
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <sphero_topics/sphero_topics.hpp>
#include <geometry_msgs/Vector3.h>
#include <sphero_actions/record_odomAction.h>
#include <sphero_actions/record_odomActionFeedback.h>
#include <sphero_actions/record_odomActionResult.h>
#include <boost/bind.hpp>
namespace sphero_actions
{
class OdometryAnalyse
{

public:
    OdometryAnalyse();
    double get_distance_moved(nav_msgs::Odometry odom_start ,nav_msgs::Odometry odom_end );
    double calculate_length_vector(geometry_msgs::Vector3 vec);
    bool check_if_out_maze(double goal_distance, nav_msgs::Odometry odom_start ,nav_msgs::Odometry odom_end );
    geometry_msgs::Vector3 create_vector(geometry_msgs::Point p1 ,geometry_msgs::Point p2);


};
} /* for namespace */
#endif // ODOMETRY_ANALYSE_HPP
