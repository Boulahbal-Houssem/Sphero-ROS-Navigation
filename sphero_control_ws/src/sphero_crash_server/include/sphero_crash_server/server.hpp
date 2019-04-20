#ifndef SHERPO_SERVER_HPP
#define SHERPO_SERVER_HPP
#include <ros/ros.h>
#include <sphero_topics/sphero_topics.hpp>
#include <std_srvs/Trigger.h>
namespace  sphero_crash_server{


class CrashDirectionService
{
private:
    sphero_topics::ImuTopicReader imu_ ;
    std::string service_name_;
    ros::ServiceServer crash_service_;
    ros::NodeHandle n_;
public:
    CrashDirectionService();
    CrashDirectionService(std::string st);
    bool serverCallback(std_srvs::Trigger::Request& reg , std_srvs::Trigger::Response& res);
    bool hasCrashed();
    std::string directionToMove();
};


}/* for namespace } */
#endif
