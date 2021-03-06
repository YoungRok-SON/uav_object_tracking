#ifndef __EXTRACT_LANE_H__
#define __EXTRACT_LANE_H__

#include <ros/ros.h>
#include <ros/spinner.h>
#include <Eigen/Dense>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Point.h>
#include <uav_msgs/CarState.h>
#include <uav_msgs/PolyfitLane.h>
#include <uav_msgs/PolyfitLaneData.h>
#include <nav_msgs/Odometry.h>
#include "uav_msgs/Roi.h"
#include "off_board_control/utils.h"

struct Euler {
    double r;
    double p;
    double y;
};

class ExtractLane{
private:
    ros::NodeHandle m_nh;
    offboard::Utils m_utils;
    
public:
    ExtractLane();
    virtual ~ExtractLane();

private:
    // Subscriber
	ros::Subscriber m_desired_waypoints_sub;
    ros::Subscriber m_uav_state_sub;
	// publisher
    ros::Publisher m_roi_box_pub;
	ros::Publisher m_roi_lane_pub;
    ros::Publisher m_poly_fit_lane_pub;
    ros::Publisher m_evaulation_pub;

    // Param
    double m_roi_front_param;
    double m_roi_rear_param;
    double m_roi_lateral_param;
    double m_roi_vertical_param;
    std::string m_vehicle_name_param;

    //
    uav_msgs::PolyfitLane m_roi_lane;
    uav_msgs::PolyfitLaneData m_poly_lane;
    geometry_msgs::PointStamped m_curr_uav_position;
    uav_msgs::Roi m_roi_msg;

    void SetParam();
    void UavStateCallback(const nav_msgs::Odometry::ConstPtr odm_ptr);
    void DesiredWaypointsCallback(const geometry_msgs::PoseArray::ConstPtr pose_array_ptr);
    bool Evaluation(const geometry_msgs::PoseArray::ConstPtr lane_ptr);
    
    bool ExtractRegionOfInterest(const geometry_msgs::PoseArray::ConstPtr lane_ptr);
    void PolyfitLane();
};

#endif // __EXTRACT_LANE_H__
