#include <ros/ros.h>
#include <std_srvs/Trigger.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Crash_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<std_srvs::Trigger>("/crash_direction_service");
    std_srvs::Trigger srv;
    if (client.call(srv))
    {
        std::cout <<" Message " << srv.response.message << "\nsuccess "<<srv.response.success << std::endl;
    }
    return 0;
}

