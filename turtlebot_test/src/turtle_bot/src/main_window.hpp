/*****************************************************************************
** Ifdefs
*****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include <string>

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>


/*****************************************************************************
** Namespaces
*****************************************************************************/
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*****************************************************************************
** Class
*****************************************************************************/
class RosPage : public QThread {
 Q_OBJECT
 
public:
  RosPage(std::string nodeName);
  ~RosPage();
  void run();

private:
  rclcpp::Node::SharedPtr node;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr feedBackStatusSubscription;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
  void feedback_states_callback(nav_msgs::msg::Odometry::SharedPtr msg);
  
signals:
  void get_status(double vx, double vy);
  
private slots:
  void send_message(double v, double rotation);
  void send_speed(double);
  
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  double speed = 0 ;
  std::unique_ptr<RosPage> rosPage;
  void initial_ros_thread_to_ui_page();
  void initial_ui_component();
  
signals:
  void send_message(double v, double rotation);
  void send_speed(double);

private slots:
  void show_status(double vx, double vy);
  void click_speed_up_button();
  void click_speed_down_button();
  void click_set_speed_button();
  void click_speed_0_button();
  void click_rotation_up_button();
  void click_rotation_down_button();
  void click_set_rotation_button();
  void click_rotation_0_button();

};
#endif // MAINWINDOW_H

