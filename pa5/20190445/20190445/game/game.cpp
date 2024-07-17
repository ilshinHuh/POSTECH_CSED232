#include "game.h"

Game::Game(){
    board = new Board();//dyanamically allocate board
    QFile progress("progress.txt");
    progress.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&progress);
    out << board->getInit() << Qt::endl << Qt::endl;
    progress.close();//write on progress.txt
}

Game::~Game(){
    delete board;
}

Board* Game::getBoard(){//wrapping function
    return board;
}

int Game::isGameOver(){
    for(int x = 0; x < 4; ++x){
        for(int y = 0; y < 4; ++y){
            if(board->getBlock(x, y)->getVal() == 2048)
                return 0;//win!
        }
    }
    if(!board->moveAble())
        return 1;//lose...
    else
        return 2;//continue
}
