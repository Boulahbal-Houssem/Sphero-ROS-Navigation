#include <sphero_crash_server/server.hpp>
namespace  sphero_crash_server{

CrashDirectionService::CrashDirectionService()
{
    service_name_  = "/crash_direction_service";
    crash_service_ = n_.advertiseService(service_name_, &CrashDirectionService::serverCallback,this);

}
CrashDirectionService::CrashDirectionService(std::string st)
{
    service_name_ = st;
    crash_service_ = n_.advertiseService(service_name_, &CrashDirectionService::serverCallback,this);

}
bool CrashDirectionService::serverCallback(std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res)
{
    std::string message = imu_.four_sector_detection();
    res.success = hasCrashed();
    res.message = message;
    return true;
}
bool CrashDirectionService::hasCrashed()
{
    if (imu_.four_sector_detection() == "nothing") {
        return false;
    }
    else {
        return true;
    }
}
} /* for namespace */

