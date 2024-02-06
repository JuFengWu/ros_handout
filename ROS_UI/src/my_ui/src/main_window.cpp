#include "main_window.hpp"
#include "ui_my_ui.h"

void MainWindow::initial_ui_component(){
  connect(ui->pushButton, SIGNAL(clicked()),this,SLOT(click_button()));
}
void MainWindow::initial_ros_thread_to_ui_page(){
  connect(rosPage.get(), SIGNAL(get_status(std::string)), this, SLOT(show_status(std::string)));
  connect(this, SIGNAL(send_message(std::string)),  rosPage.get(), SLOT(send_message(std::string)));
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
void MainWindow::show_status(std::string msg){
  ui->label->setText(QString::fromStdString(msg));
}
void MainWindow::click_button(){
  std::cout<<"b"<<std::endl;
  send_message("hello world");
}
MainWindow::~MainWindow(){
  delete ui;
}
