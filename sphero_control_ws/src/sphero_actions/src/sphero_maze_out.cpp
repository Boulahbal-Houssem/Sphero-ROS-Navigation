#include <sphero_actions/sphero_maze_out.hpp>
namespace sphero_actions
{

RecordOdom::RecordOdom(std::string name , double goal):action_name_(name), as_(n_, name,false)
  {
    as_.registerGoalCallback(boost::bind(&RecordOdom::goal_callback, this));
    goal_distance = goal;
    seconds_recording = 120;
    as_.start();
  }
void RecordOdom::goal_callback()
{
    std::cout << "goal feedback \n";
    bool success = true;
    ros::Rate rate(1);
    for (int i = 0 ; i<seconds_recording ; i++)
    {
        std::cout << "i" << i << std::endl;

        if(as_.isPreemptRequested())
        {
            std::cout << "first if \n";
            as_.setPreempted();
            success = false;
            break;
        }
        else
        {
            std::cout << "first if \n";

          if (!reached_distance_goal())
          {
              std::cout << "2nd if \n";
              result_.result_odom_array.push_back(odom_.getOdomData());
          }
          else {
              success = true;
              std::cout << "reached goal " << std::endl;
              break;
          }

        }
    rate.sleep();
    }
//if (success)
        as_.setSucceeded(result_);
    clean_variables();
}
void RecordOdom::clean_variables()
{
    result_ = record_odomResult();
}
bool RecordOdom::reached_distance_goal()
{
    if (result_.result_odom_array.size()>1)
    {
        OdometryAnalyse om;
        nav_msgs::Odometry odom_start  = result_.result_odom_array[0];
        nav_msgs::Odometry odom_end    = result_.result_odom_array[result_.result_odom_array.size() -1];
        return om.check_if_out_maze(goal_distance,odom_start,odom_end);
    }
    else {
        return false;
    }
}
}/* for namespace */

