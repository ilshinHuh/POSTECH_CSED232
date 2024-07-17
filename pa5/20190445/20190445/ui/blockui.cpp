#include "blockui.h"

BlockUi::BlockUi(QLabel* parent, Block* block) : QLabel(parent)
{
    setFixedSize(250, 250);//set size
    update(block);//update block
}

void BlockUi::update(Block *block){
    switch(block->getVal()) {//set style according to value
    case 0:
        setStyleSheet("QLabel { background: rgb(255, 255, 255); color: black; border-style: solid; font: 70pt; font: bold; }" );
        setText("");//set value to blank
        return;
    case 2:
        setStyleSheet("QLabel { background: rgb(187, 173, 160); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    case 4:
        setStyleSheet("QLabel { background: rgb(237, 224, 200); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    case 8:
        setStyleSheet("QLabel { background: rgb(242, 177, 121); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    case 16:
        setStyleSheet("QLabel { background: rgb(245, 149, 99); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    case 32:
        setStyleSheet("QLabel { background: rgb(246, 126, 95); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    case 64:
        setStyleSheet("QLabel { background: rgb(246, 94, 59); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    case 128:
        setStyleSheet("QLabel { background: rgb(237, 207, 114); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    case 256:
        setStyleSheet("QLabel { background: rgb(237, 204, 97); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    case 512:
        setStyleSheet("QLabel { background: rgb(237, 200, 80); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    case 1024:
        setStyleSheet("QLabel { background: rgb(237, 197, 63); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    case 2048:
        setStyleSheet("QLabel { background: rgb(237, 194, 46); color: black; border-style: solid; font: 70pt; font: bold; }");
        break;
    }
    setText(QString::number(block->getVal()));//set value to value
}
