#ifndef SPHERO_MAZE_OUT_HPP
#define SPHERO_MAZE_OUT_HPP
#include <ros/ros.h>
#include <sphero_topics/sphero_topics.hpp>
#include <sphero_actions/record_odomAction.h>
#include <sphero_actions/record_odomActionFeedback.h>
#include <sphero_actions/record_odomActionResult.h>
#include <nav_msgs/Odometry.h>
#include <actionlib/server/simple_action_server.h>
#include <boost/cstdint.hpp>
#include <sphero_actions/odometry_analyse.hpp>

namespace sphero_actions
{
class RecordOdom
{
private:
    ros::NodeHandle n_;
    sphero_topics::OdomTopicReader odom_;
    sphero_actions::record_odomResult result_;
    std::string action_name_;
    float seconds_recording;
    double goal_distance;
public:
    actionlib::SimpleActionServer<sphero_actions::record_odomAction> as_;
    RecordOdom(std::string name ,double goal);
    void goal_callback();
    void clean_variables();
    bool reached_distance_goal();
};
} /* for namesapce */
#endif
