/*****************************************************************************
** Includes
*****************************************************************************/
#include "main_window.hpp"
#include <QApplication>

/*****************************************************************************
** Main
*****************************************************************************/
int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  qRegisterMetaType<std::string>("std::string");
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  
  return a.exec();
}
