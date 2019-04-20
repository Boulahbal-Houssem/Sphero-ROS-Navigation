#include <ros/ros.h>
#include <sphero_actions/record_odomAction.h>
#include <sphero_actions/record_odomActionFeedback.h>
#include <sphero_actions/record_odomActionResult.h>
#include <nav_msgs/Odometry.h>
#include <actionlib/client/simple_action_client.h>

void feedback_print()
{
    std::cout << "feedback" << std::endl;
}
void doneCb()
{
  ros::shutdown();
}

// Called once when the goal becomes active
void activeCb()
{
  std::cout << "Goal just went active \n";
}

void count_sec(int second)
{
    for(int i=0 ; i< second ;i++)
    {
        std::cout << "second passed " << i << std::endl;
        ros::Duration(1).sleep();
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc ,argv, "record_odom_action_client_node");
    actionlib::SimpleActionClient<sphero_actions::record_odomAction> ac("/rec_odom_as", true);
    ros::Rate rate(1);
    std::cout << "wating server \n";
    ac.waitForServer();
    std::cout << "Action server started, sending goal.\n";
    sphero_actions::record_odomGoal goal;
    ac.sendGoal(goal, &doneCb, &activeCb, &feedback_print);
    actionlib::SimpleClientGoalState state = ac.getState();

    //wait for the action to return
    while(state.toString() == "PENDING")
    {
    }
    std::cout << state.toString() << std::endl;

    return 0;
}

