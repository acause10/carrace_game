#include <QApplication>
#include <iostream>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   //define stylesheet for the application
   a.setStyleSheet("QPushButton { "
                       "background-image: url(:/resources/images/BackgroundButtons.png);"
                       "border-top: 4px solid black;"
                       "border-bottom: 4px solid black;"
                       "border-right: 4px solid black;"
                       "border-left: 4px solid black;"
                       "border-radius: 16px;"
                       "color: white;"
                       "font-family: times;"
                       "font-size: 28px;"
                       "padding: 8px; }"
                   "QPushButton:hover {"
                       "background-image: url(:/resources/images/backgroundMainwindow.png);}"
                   "QLabel { "
                      "border-top: 4px solid transparent;"
                      "border-bottom: 4px solid transparent;"
                      "border-right: 4px solid transparent;"
                      "border-left: 4px solid transparent;"
                      "border-radius: 8px;"
                      "color: black;"
                      "font-family: times;"
                      "font-size: 20px;"
                      "padding: 8px;"
                      "background-color: rgba(12, 199, 197, 0.8); }"
                   "QMenuBar {"
                      "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                      "stop:0 lightgray, stop:1 darkgray);"
                      "padding: 8px;"
                      "font-size: 20px;"
                      "spacing: 3px;}"
                   "QMenuBar::item {"
                      "padding: 8px;"
                      "background: transparent;"
                      "border-radius: 8px;}"
                   "QMenuBar::item:selected {"
                      "background: rgba(215, 249, 252, 1);}"
                   "QGraphicsView {"
                      "background-image: url(:/resources/images/backgroundMainwindow.png);}"
                   "QDialog {"
                      "background: rgba(169, 7, 46, 60);}"
                   "QLineEdit {"
                      "background-color: rgba(215, 249, 252, 1);"
                      "font-size: 20px;"
                      "padding: 8px;"
                      "border-radius: 8px;}"
                   "QComboBox {"
                       "border: 3px solid gray;"
                       "border-radius: 8px;"
                       "padding: 4px;"
                       "font-size: 20px; }"
                   "QComboBox::drop-down:editable {"
                       "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                               "stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
                                               "stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
                   "};");

   MainWindow carRacingGame;
   carRacingGame.show();

   return a.exec();
}
