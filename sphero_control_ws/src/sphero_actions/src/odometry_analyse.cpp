#include <sphero_actions/odometry_analyse.hpp>
namespace sphero_actions
{
OdometryAnalyse::OdometryAnalyse()
{

}

geometry_msgs::Vector3 OdometryAnalyse::create_vector(geometry_msgs::Point p1 ,geometry_msgs::Point p2)
{
    geometry_msgs::Vector3 distance_vector;
    distance_vector.x = p2.x - p1.x;
    distance_vector.y = p2.y - p1.y;
    distance_vector.z = p2.z - p1.z;
    return distance_vector;
}
double OdometryAnalyse::get_distance_moved(nav_msgs::Odometry odom_start ,nav_msgs::Odometry odom_end )
{
    geometry_msgs::Point start =  odom_start.pose.pose.position ;
    geometry_msgs::Point end   = odom_end.pose.pose.position ;
    geometry_msgs::Vector3 distance_vector= create_vector(start , end);
    double distance = calculate_length_vector(distance_vector);
    return distance;
}
double OdometryAnalyse::calculate_length_vector(geometry_msgs::Vector3 vec)
{
    return (std::sqrt(  std::pow(vec.x,2) +   std::pow(vec.y,2)  +std::pow(vec.z,2) ));
}

bool OdometryAnalyse::check_if_out_maze(double goal_distance, nav_msgs::Odometry odom_start ,nav_msgs::Odometry odom_end )
{
    double distance  = get_distance_moved(odom_start ,odom_end );
    return distance > goal_distance;
}


} /* for namesapce */
