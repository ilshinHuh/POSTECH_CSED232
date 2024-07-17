#ifndef GAME_H
#define GAME_H

#include <QTextStream>
#include "board.h"

class Game : public QWidget{
public:
    Game();//constructor
    ~Game();//deconstructor
    Board* getBoard();//wrapping function
    int isGameOver();//is game over?
private:
    Board* board;
};

#endif // GAME_H
