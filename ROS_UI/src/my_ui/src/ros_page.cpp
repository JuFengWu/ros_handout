#include "main_window.hpp"

RosPage::RosPage(std::string nodeName)
{
  node = rclcpp::Node::make_shared(nodeName);
  feedBackStatusSubscription = node->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&RosPage::feedback_states_callback, this, std::placeholders::_1));
  publisher = node->create_publisher<std_msgs::msg::String>("topic", 10);
}
RosPage::~RosPage(){
  rclcpp::shutdown();
  RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"), "call ~RosPage");
}
void RosPage::run(){

  rclcpp::spin(node);
}
void RosPage::feedback_states_callback(std_msgs::msg::String::SharedPtr msg){
  
  get_status(msg->data);
}
void RosPage::send_message(std::string msg){
  
  auto message = std_msgs::msg::String();
  
  message.data = msg;
  
  publisher->publish(message);
 
}
