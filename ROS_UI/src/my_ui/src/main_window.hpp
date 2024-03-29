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
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr feedBackStatusSubscription;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
  void feedback_states_callback(std_msgs::msg::String::SharedPtr msg);
  
signals:
  void get_status(std::string msg);
private slots:
  void send_message(std::string msg);
  
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  std::unique_ptr<RosPage> rosPage;
  void initial_ros_thread_to_ui_page();
  void initial_ui_component();
  
signals:
  void send_message(std::string msg);

private slots:
  void show_status(std::string msg);
  void click_button();

};
#endif // MAINWINDOW_H

