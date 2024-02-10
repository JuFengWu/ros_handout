#include "geometry_msgs/msg/twist.hpp"
#include "main_window.hpp"
#include "ui_my_ui.h"

void MainWindow::initial_ui_component(){
  connect(ui->pushButton, SIGNAL(clicked()),this,SLOT(click_speed_up_button()));
  connect(ui->pushButton_2, SIGNAL(clicked()),this,SLOT(click_speed_down_button()));
  connect(ui->pushButton_3, SIGNAL(clicked()),this,SLOT(click_set_speed_button()));
  connect(ui->pushButton_4, SIGNAL(clicked()),this,SLOT(click_speed_0_button()));
  connect(ui->pushButton_5, SIGNAL(clicked()),this,SLOT(click_rotation_up_button()));
  connect(ui->pushButton_6, SIGNAL(clicked()),this,SLOT(click_rotation_down_button()));
  connect(ui->pushButton_7, SIGNAL(clicked()),this,SLOT(click_set_rotation_button()));
  connect(ui->pushButton_8, SIGNAL(clicked()),this,SLOT(click_rotation_0_button()));
}
void MainWindow::initial_ros_thread_to_ui_page(){
  connect(rosPage.get(), SIGNAL(get_status(double,double)), this, SLOT(show_status(double,double)));
  connect(this, SIGNAL(send_message(std::string)),  rosPage.get(), SLOT(send_message(std::string)));
  connect(this,SIGNAL(send_speed(double)),  rosPage.get(), SLOT(send_speed(double)));
  //connect(this,SIGNAL(send_rotation(double)),  rosPage.get(), SLOT(send_rotation(double)));
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  initial_ui_component();
  rosPage = std::make_unique<RosPage>("my_ros_node");
  rosPage->start();
  initial_ros_thread_to_ui_page();
}
void MainWindow::show_status(double a,double b){
  ui->label->setText(QString::fromStdString(std::to_string(a)));
  ui->label_3->setText(QString::fromStdString(std::to_string(b)));
}

void MainWindow::click_speed_up_button(){
  speed +=0.1;
  send_speed(speed);
}
void MainWindow::click_speed_down_button(){
  speed -=0.1;
  send_speed(speed);
}
void MainWindow::click_set_speed_button(){
  std::string value = ui->lineEdit->text().toUtf8().constData();;
  speed = std::stod(value);
  try {
    speed = std::stod(value);
  } catch (...){
    std::cout<<"value is "<<value<<std::endl;
  }
  send_speed(speed);
}
void MainWindow::click_speed_0_button(){
  speed =0;
  send_speed(speed);
}
void MainWindow::click_rotation_up_button(){}
void MainWindow::click_rotation_down_button(){}
void MainWindow::click_set_rotation_button(){}
void MainWindow::click_rotation_0_button(){}

MainWindow::~MainWindow(){
  delete ui;
}
