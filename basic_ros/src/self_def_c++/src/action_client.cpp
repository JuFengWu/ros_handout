#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>

#include "self_def_msg_srv/action/my_action.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"



class MyActionClient : public rclcpp::Node
{
public:
  using MyAction = self_def_msg_srv::action::MyAction;
  using GoalHandleAction = rclcpp_action::ClientGoalHandle<MyAction>;

  explicit MyActionClient(const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
  : Node("my_action_client", options)
  {
    this->client_ptr_ = rclcpp_action::create_client<MyAction>(
      this,
      "my_action");

    this->timer_ = this->create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&MyActionClient::send_goal, this));
  }

  void send_goal()
  {
    using namespace std::placeholders;

    this->timer_->cancel();

    if (!this->client_ptr_->wait_for_action_server()) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
      rclcpp::shutdown();
    }

    auto goal_msg = MyAction::Goal();
    goal_msg.start_selection = 1;

    RCLCPP_INFO(this->get_logger(), "Sending goal");

    auto send_goal_options = rclcpp_action::Client<MyAction>::SendGoalOptions();
    send_goal_options.goal_response_callback =
      std::bind(&MyActionClient::goal_response_callback, this, _1);
    send_goal_options.feedback_callback =
      std::bind(&MyActionClient::feedback_callback, this, _1, _2);
    send_goal_options.result_callback =
      std::bind(&MyActionClient::result_callback, this, _1);
    this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
  }

private:
  rclcpp_action::Client<MyAction>::SharedPtr client_ptr_;
  rclcpp::TimerBase::SharedPtr timer_;

  void goal_response_callback(std::shared_future<GoalHandleAction::SharedPtr> future)
  {
    auto goal_handle = future.get();
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
    }
  }

  void feedback_callback(
    GoalHandleAction::SharedPtr,
    const std::shared_ptr<const MyAction::Feedback> feedback)
  {
    
    RCLCPP_INFO(this->get_logger(), "feedback value is %f", feedback->value);
     client_ptr_->async_cancel_all_goals(); // this will cancel 
  }

  void result_callback(const GoalHandleAction::WrappedResult & result)
  {
    RCLCPP_INFO(this->get_logger(), "result is %d", result.result->success_or_not);
    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        break;
      case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
        return;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
        return;
      default:
        RCLCPP_ERROR(this->get_logger(), "Unknown result code");
        return;
    }
    
    rclcpp::shutdown();
  }
}; 

int main(int argc, char **argv){
  rclcpp::init(argc, argv);
  auto action_client = std::make_shared<MyActionClient>();
  rclcpp::spin(action_client);
  rclcpp::shutdown();
  return 0;
}
