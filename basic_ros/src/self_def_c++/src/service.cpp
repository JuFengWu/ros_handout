#include "rclcpp/rclcpp.hpp"
#include "self_def_msg_srv/srv/add_many.hpp"

#include <memory>

void add(const std::shared_ptr<self_def_msg_srv::srv::AddMany::Request> request,
          std::shared_ptr<self_def_msg_srv::srv::AddMany::Response>      response)
{
  for(int i=0;i<request->numbers.size();i++){
    response->result_value += request->numbers[i];
  }

  
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->result_value);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

  rclcpp::Service<self_def_msg_srv::srv::AddMany>::SharedPtr service =
    node->create_service<self_def_msg_srv::srv::AddMany>("add_ints", &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}
