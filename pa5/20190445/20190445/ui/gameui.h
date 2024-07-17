#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QKeyEvent>
#include <QObject>
#include <QMessageBox>
#include <QApplication>
#include "blockui.h"
#include "../game/game.h"

class GameUi : public QWidget
{
   Q_OBJECT//macro for input

public:
    GameUi(QWidget *parent = nullptr);//constructor
    virtual ~GameUi();//destructor
    void keyPressEvent(QKeyEvent* event) override;//keyPress
    void updateUi();//update board
    void showExit();//show exit message
    void showRestore();//show restore message
private:
    QGridLayout *mainLayout;//main layout
    QGridLayout *board;//gmae layout
    QLabel *scoreLabel;
    QPushButton *exitButton;
    QPushButton *restoreButton;
    Game* game;
    BlockUi*** gameBoard;//for giving blocks ui
    int restoreCount;//restore tracker
};

#endif // GAMEUI_H
