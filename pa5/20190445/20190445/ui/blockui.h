#ifndef BLOCKUI_H
#define BLOCKUI_H

#include "../game/block.h"

class BlockUi : public QLabel
{
public:
    BlockUi(QLabel* parent, Block *block);//constructor
    void update(Block *block);//update block ui
    ~BlockUi(){}//destructor
};

#endif // BLOCKUI_H
