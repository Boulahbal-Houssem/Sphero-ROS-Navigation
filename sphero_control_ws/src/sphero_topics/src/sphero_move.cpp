#include <sphero_topics/sphero_topics.hpp>
#include <vector>
#include <cstdlib>
namespace sphero_topics
{
  /* Sphero Move class */
  SpheroMove::SpheroMove()
        {
            move_topic_     = n_.advertise<geometry_msgs::Twist>("/cmd_vel",1);
            linear_speed_   = 0.2;
            angular_speed_  = 0.5;
        }
  SpheroMove::SpheroMove(double ls,double as):linear_speed_(ls) , angular_speed_(as)
        {
          move_topic_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel",1);
        }
  void SpheroMove::setLinearSpeed(double ls) {linear_speed_=ls;}
  void SpheroMove::setAngularSpeed(double as){angular_speed_=as;}
  void SpheroMove::moveRobot(std::string direction)
  {
   if( direction == "forwards")
    {
      twist_.linear.x = linear_speed_;
      twist_.angular.z = 0.0;
    }
    else if (direction == "right")
    {
      twist_.linear.x = 0.0;
      twist_.angular.z = angular_speed_;
    }
    else if (direction == "left")
    {
      twist_.linear.x = 0.0;
      twist_.angular.z = -angular_speed_;
    }
    else if (direction == "backwards")
    {
      twist_.linear.x = -linear_speed_;
      twist_.angular.z = 0;
    }
    else if (direction == "stop")
    {
      twist_.linear.x = 0;
      twist_.linear.y = 0;
      twist_.linear.z = 0;
      twist_.angular.x = 0;
      twist_.angular.y = 0;
      twist_.angular.z = 0;
    }  
    move_topic_.publish(twist_);
  } 

  /* Odometrie topic class */
  OdomTopicReader::OdomTopicReader()
  {
      topic_name_ = "/odom";
      odom_topic_ = n_.subscribe(topic_name_, 1, &OdomTopicReader::odomTopicCallback, this);
  }
  OdomTopicReader::OdomTopicReader(std::string tn)
  {
      topic_name_ = tn;
      odom_topic_ = n_.subscribe(topic_name_, 1, &OdomTopicReader::odomTopicCallback, this);

  }
  nav_msgs::Odometry OdomTopicReader::getOdomData()
  {
      return odom_data_;
  }
  void OdomTopicReader::odomTopicCallback(const nav_msgs::Odometry::ConstPtr& msg)
  {
      odom_data_ = *msg;
  }

  /* Imu topic class definitions */

  ImuTopicReader::ImuTopicReader()
  {
      topic_name_ = "/sphero/imu/data3";
      threshhold_ = 7.00;
      imu_topic_  = n_.subscribe(topic_name_ , 1 , &ImuTopicReader::imuTopicCallback , this);
  }
  ImuTopicReader::ImuTopicReader(std::string tn)
  {
      topic_name_ = tn;
      threshhold_ = 7.00;
      imu_topic_  = n_.subscribe(topic_name_ , 1 , &ImuTopicReader::imuTopicCallback , this);
  }
  sensor_msgs::Imu ImuTopicReader::getImuData()
  {
      return imu_data_;
  }
  void ImuTopicReader::imuTopicCallback(const sensor_msgs::Imu::ConstPtr& msg)
  {
      imu_data_ = * msg;
   }
  std::string ImuTopicReader::four_sector_detection()
  {
    std::string returned_direction;
    std::vector<double> accel {imu_data_.linear_acceleration.x,imu_data_.linear_acceleration.y,imu_data_.linear_acceleration.z};
    unsigned int max_index;
    max_index = this->max_index(accel);
    bool significative_value = std::abs(accel[max_index]) > threshhold_;
    bool positive = accel[max_index] > 0;
    if (significative_value)
    {
        if(max_index == 0)
        {
            //ROS_INFO("the crash is on the x direction");
            if(positive)
            {
                returned_direction = "right";
            }
            else
            {
                returned_direction ="left";
            }
        }
        else if (max_index == 1)
        {
            //ROS_INFO("the crash is on the x direction");
            if(positive)
            {
                returned_direction = "front";
            }
            else
            {
                returned_direction ="back";
            }
        }
        else if (max_index == 2)
        {
            //ROS_INFO("the crash is on the z direction");
                returned_direction = "front";
        }
        else
        {
            //ROS_INFO("unknown direction");
            returned_direction = "unknown";
        }
    }
    else
    {
         returned_direction = "nothing";
    }
    return returned_direction;
  }
  unsigned int ImuTopicReader::max_index(std::vector<double> accel)
  {
      unsigned int max = std::abs(accel[0])>std::abs(accel[1]) ? 0:1 ;
      return       max = std::abs(accel[max]) > std::abs(accel[2])       ? max :2;
  }
} /* for name space */

int main(int argc , char ** argv)
{
  ros::init(argc, argv, "sphero_move");
  sphero_topics::SpheroMove sp;
  sphero_topics::OdomTopicReader tp;
  sphero_topics::ImuTopicReader im;
  while(ros::ok())
  {
    ros::spinOnce();
  }
  return 0;
}
