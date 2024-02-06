#include "rclcpp/rclcpp.hpp"
#include "self_def_msg_srv/srv/add_many.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;// not recomend

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);


  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_client");
  rclcpp::Client<self_def_msg_srv::srv::AddMany>::SharedPtr client =
    node->create_client<self_def_msg_srv::srv::AddMany>("add_ints");

  auto request = std::make_shared<self_def_msg_srv::srv::AddMany::Request>();
  request->numbers.push_back(3);
  request->numbers.push_back(4);
  request->numbers.push_back(5);

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->result_value);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
  }

  rclcpp::shutdown();
  return 0;
}
