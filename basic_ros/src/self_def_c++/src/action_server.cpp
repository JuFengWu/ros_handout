#include <functional>
#include <memory>
#include <thread>

#include "self_def_msg_srv/action/my_action.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"


class MyActionServer : public rclcpp::Node
{
public:
  using MyAction = self_def_msg_srv::action::MyAction;
  using GoalHandleMyAction = rclcpp_action::ServerGoalHandle<MyAction>;

  
  explicit MyActionServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
  : Node("my_action_server", options)
  {
    using namespace std::placeholders;

    this->action_server_ = rclcpp_action::create_server<MyAction>(
      this,
      "my_action",
      std::bind(&MyActionServer::handle_goal, this, _1, _2),
      std::bind(&MyActionServer::handle_cancel, this, _1),
      std::bind(&MyActionServer::handle_accepted, this, _1));
  }

private:
  rclcpp_action::Server<MyAction>::SharedPtr action_server_;

  rclcpp_action::GoalResponse handle_goal(
    const rclcpp_action::GoalUUID ,
    std::shared_ptr<const MyAction::Goal> goal)
  {
    RCLCPP_INFO(this->get_logger(), "start_selection is %d", goal->start_selection);
    
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse handle_cancel(
    const std::shared_ptr<GoalHandleMyAction> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void)goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void handle_accepted(const std::shared_ptr<GoalHandleMyAction> goal_handle)
  {
    using namespace std::placeholders;
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&MyActionServer::execute, this, _1), goal_handle}.detach();
  }

  void execute(const std::shared_ptr<GoalHandleMyAction> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(1);
    const auto goal = goal_handle->get_goal();
    auto feedback = std::make_shared<MyAction::Feedback>();
    auto & sequence = feedback->value;
    
    auto result = std::make_shared<MyAction::Result>();
    
    
    for(int i=0;i<10;i++){
    
      feedback->value=i+0.1;
      RCLCPP_INFO(this->get_logger(), "feed back is %f", feedback->value);
      if (goal_handle->is_canceling()) {
        result->success_or_not = false;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal canceled");
        return;
      }
      goal_handle->publish_feedback(feedback);
      loop_rate.sleep();
    }
    
     if (rclcpp::ok()) {
      result->success_or_not = true;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    } else {
    
      result->success_or_not = false;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal failed");
    }
    
  }
};  

int main(int argc, char **argv){
  rclcpp::init(argc, argv);
  auto action_server = std::make_shared<MyActionServer>();
  rclcpp::spin(action_server);
  rclcpp::shutdown();
  return 0;
}
