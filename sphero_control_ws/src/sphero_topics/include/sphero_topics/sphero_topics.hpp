#ifndef SPHERO_TOPICS_HPP
#define SPHERO_TOPICS_HPP
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Imu.h>
#include <string>
#include <nav_msgs/Odometry.h>
namespace sphero_topics {

class SpheroMove 
{
  private : 
    double linear_speed_,angular_speed_;
    ros::NodeHandle n_;
    ros::Publisher move_topic_;
    geometry_msgs::Twist twist_;
  public :
    SpheroMove();
    SpheroMove(double ls,double as);
    void setLinearSpeed(double ls);
    void setAngularSpeed(double fs);
    void moveRobot(std::string direction);
};
class OdomTopicReader
{
  private:
    ros::NodeHandle n_;
    std::string topic_name_;
    ros::Subscriber odom_topic_;
    nav_msgs::Odometry odom_data_;
  public:
    OdomTopicReader();
    OdomTopicReader(std::string tn);
    void odomTopicCallback(const nav_msgs::Odometry::ConstPtr& msg);
    nav_msgs::Odometry getOdomData();
};
class ImuTopicReader
{
  private:
    ros::NodeHandle n_;
    std::string topic_name_;
    sensor_msgs::Imu imu_data_;
    ros ::Subscriber imu_topic_;
    double threshhold_;
    unsigned int max_index(std::vector<double> accel);
  public:
    ImuTopicReader();
    ImuTopicReader(std::string tn);
    void imuTopicCallback(const sensor_msgs::Imu::ConstPtr& msg);
    sensor_msgs::Imu getImuData();
    std::string four_sector_detection();
};
}/* for name space */
#endif
