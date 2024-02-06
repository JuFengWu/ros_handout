#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "self_def_msg_srv/msg/error_code.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      subscription_ = this->create_subscription<self_def_msg_srv::msg::ErrorCode>(
      "error", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const self_def_msg_srv::msg::ErrorCode::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "error code is '%d'", msg->error_code);
      
      RCLCPP_INFO(this->get_logger(), "error message is " + msg->error_msg);
    }
    rclcpp::Subscription<self_def_msg_srv::msg::ErrorCode>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
