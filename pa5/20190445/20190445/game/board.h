#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QRandomGenerator>
#include <QFile>
#include "block.h"

class Board
{
public:
    Board();//constructor
    Block* getBlock(int x, int y) const;//block wrapping function
    void setBlock(int x, int y, Block *block);//set block function
    //moving functions
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    bool moveAble() const;//if moveable function
    void genRandBlock();//generating random block
    int getScore();//get game score
    void restore();//restore to prev step
    QString getInit();// get initial condition in QString
    bool noBuff;//buffer empty indicator

    ~Board();//destructor

private:
    Block *blocks[4][4];//blocks
    int bufferBlock[4][4];//buffer
    int score;//game score
    QString initState;//initial state
};

#endif // BOARD_H
