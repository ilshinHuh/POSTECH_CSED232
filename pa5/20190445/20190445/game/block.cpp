#include "block.h"

Block::Block(int value) : blockVal(value){}//constructor

int Block::getVal() const {return blockVal;}//wrapping function

void Block::setVal(int value){//set value
    blockVal = value;
}
