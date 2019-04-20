#include <ros/ros.h>
#include <sphero_crash_server/server.hpp>
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Crash_server");
    sphero_crash_server::CrashDirectionService crsrv;
    while(ros::ok())
    {
        ros::spinOnce();
    }
    return 0;
}
