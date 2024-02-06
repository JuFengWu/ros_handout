#include "main_window.hpp"

RosPage::RosPage(std::string nodeName)
{
  node = rclcpp::Node::make_shared(nodeName);

  publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  
  feedBackStatusSubscription = node->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&RosPage::feedback_states_callback, this, std::placeholders::_1));
}
RosPage::~RosPage(){
  rclcpp::shutdown();
  RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"), "call ~RosPage");
}
void RosPage::run(){

  rclcpp::spin(node);
}
void RosPage::feedback_states_callback(nav_msgs::msg::Odometry::SharedPtr msg){
  
  get_status(msg->pose.pose.position.x,msg->pose.pose.position.y,msg->pose.pose.orientation);
}
void RosPage::send_message(double v, double rotation){
  
  auto message = geometry_msgs::msg::Twist();

  message.linear.x = v;
  message.angular.z = rotation;
  
  publisher->publish(message);
 
}
