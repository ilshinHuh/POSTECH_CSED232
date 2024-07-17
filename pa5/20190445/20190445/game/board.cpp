#include "board.h"

Board::Board() : score(0), noBuff(true){
    for(int x = 0; x < 4; ++x){//initialize all the blocks to zero
        for(int y = 0; y < 4; ++y){
            Block *block = new Block(0);
            blocks[y][x] = block;
        }
    }

    QRandomGenerator *gen = QRandomGenerator::global();
    int a = gen->bounded(4);//geneerate random numbers
    int b = gen->bounded(4);
    int c = gen->bounded(4);
    int d = gen->bounded(4);
    while(a == c && b == d){//if two coordinates are same, generate again
        c = gen->bounded(4);
        d = gen->bounded(4);
    }
    blocks[a][b]->setVal(2);//set blocks' value to 2
    blocks[c][d]->setVal(2);
    initState.append("INITIAL ");//append to initState in incrementing order of coordinates
    if(a < b){
        initState.append(QString::number(a + 1));
        initState.append(" ");
        initState.append(QString::number(b + 1));
        initState.append(" ");
        initState.append(QString::number(c + 1));
        initState.append(" ");
        initState.append(QString::number(d + 1));
    }
    else if(a > b){
        initState.append(QString::number(c + 1));
        initState.append(" ");
        initState.append(QString::number(d + 1));
        initState.append(" ");
        initState.append(QString::number(a + 1));
        initState.append(" ");
        initState.append(QString::number(b + 1));
    }
    else{
        if(b < d){
            initState.append(QString::number(a + 1));
            initState.append(" ");
            initState.append(QString::number(b + 1));
            initState.append(" ");
            initState.append(QString::number(c + 1));
            initState.append(" ");
            initState.append(QString::number(d + 1));
        }
        else{
            initState.append(QString::number(c + 1));
            initState.append(" ");
            initState.append(QString::number(d + 1));
            initState.append(" ");
            initState.append(QString::number(a + 1));
            initState.append(" ");
            initState.append(QString::number(b + 1));
        }
    }
}

Board::~Board(){//delete each blocks
    for(int y = 0; y < 4; ++y){
        for(int x = 0; x < 4; ++x){
            delete blocks[y][x];
        }
    }
}

Block* Board::getBlock(int x, int y) const{//get block pointer
    if(x >= 4 || x < 0 || y >= 4 || y < 0)
        return nullptr;
    return blocks[y][x];
}

void Board::setBlock(int x, int y, Block* block){//set block
    if(x < 4 && x >= 0 && y < 4 && y >= 0)
        blocks[y][x] = block;
}

bool Board::moveLeft(){
    QFile progress("progress.txt");//progress file
    QTextStream out(&progress);
    int row[4];//array to save a row
    bool moved = false;//indicate if anything was moved
    for(int y = 0; y < 4; ++y){
        for(int x = 0; x < 4; ++x){
            bufferBlock[y][x] = getBlock(x, y)->getVal();//save buffer
            row[x] = getBlock(x, y)->getVal();//get a row
        }
        if(row[0] == row[1] && row[0] != 0){//merge values
            score += row[1] + row[0];
            row[0] = row[1] + row[0];
            row[1] = 0;          
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(y + 1) << " " << QString::number(1) << " " << QString::number(row[0]) << Qt::endl << Qt::endl;
            progress.close();//write on progress.txt
        }
        if(row[1] == row[2] && row[1] != 0){
            score += row[2] + row[1];
            row[1] = row[2] + row[1];
            row[2] = 0;
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(y + 1) << " " << QString::number(2) << " " << QString::number(row[1]) << Qt::endl << Qt::endl;
            progress.close();
        }
        if(row[2] == row[3] && row[2] != 0){
            score += row[3] + row[2];
            row[2] = row[3] + row[2];
            row[3] = 0;
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(y + 1) << " " << QString::number(3) << " " << QString::number(row[2]) << Qt::endl << Qt::endl;
            progress.close();
        }
        int index = 0;
        for(int x = 0; x < 4; ++x){//puch to the left
            if(row[x] != 0){
                if(index != x){
                    moved = true;
                    noBuff = false;
                }
                row[index++] = row[x];
            }
        }
        for(; index < 4; ++index){//set the rest to zero
            row[index] = 0;
        }
        for(int x = 0; x < 4; ++x){//set block values
            getBlock(x, y)->setVal(row[x]);
        }
    }
    return moved;
}

bool Board::moveRight(){
    QFile progress("progress.txt");
    QTextStream out(&progress);
    int row[4];
    bool moved = false;
    for(int y = 0; y < 4; ++y){
        for(int x = 0; x < 4; ++x){
            bufferBlock[y][x] = getBlock(x, y)->getVal();
            row[x] = getBlock(x, y)->getVal();
        }
        if(row[2] == row[3] && row[2] != 0){
            score += row[3] + row[2];
            row[3] = row[3] + row[2];
            row[2] = 0;
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(y + 1) << " " << QString::number(4) << " " << QString::number(row[3]) << Qt::endl << Qt::endl;
            progress.close();
        }
        if(row[1] == row[2] && row[1] != 0){
            score += row[2] + row[1];
            row[2] = row[2] + row[1];
            row[1] = 0;
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(y + 1) << " " << QString::number(3) << " " << QString::number(row[2]) << Qt::endl << Qt::endl;
            progress.close();
        }
        if(row[0] == row[1] && row[0] != 0){
            score += row[1] + row[0];
            row[1] = row[1] + row[0];
            row[0] = 0;
            moved = true;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(y + 1) << " " << QString::number(2) << " " << QString::number(row[1]) << Qt::endl << Qt::endl;
            progress.close();
            noBuff = false;
        }       
        int index = 3;
        for(int x = 3; x >= 0; --x){
            if(row[x] != 0){
                if(index != x){
                    noBuff = false;
                    moved = true;
                }
                row[index--] = row[x];
            }
        }
        for(; index >= 0; --index){
            row[index] = 0;
        }
        for(int x = 0; x < 4; ++x){
            getBlock(x, y)->setVal(row[x]);
        }
    }
    return moved;
}

bool Board::moveUp(){
    QFile progress("progress.txt");
    QTextStream out(&progress);
    int col[4];
    bool moved = false;
    for(int x = 0; x < 4; ++x){
        for(int y = 0; y < 4; ++y){
            bufferBlock[y][x] = getBlock(x, y)->getVal();
            col[y] = getBlock(x, y)->getVal();
        }
        if(col[0] == col[1] && col[0] != 0){
            score += col[1] + col[0];
            col[0] = col[1] + col[0];
            col[1] = 0;
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(1) << " " << QString::number(x + 1) << " " << QString::number(col[0]) << Qt::endl << Qt::endl;
            progress.close();
        }
        if(col[1] == col[2] && col[1] != 0){
            score += col[2] + col[1];
            col[1] = col[2] + col[1];
            col[2] = 0;
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(2) << " " << QString::number(x + 1) << " " << QString::number(col[1]) << Qt::endl << Qt::endl;
            progress.close();
        }
        if(col[2] == col[3] && col[2] != 0){
            score += col[3] + col[2];
            col[2] = col[3] + col[2];
            col[3] = 0;
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(3) << " " << QString::number(x + 1) << " " << QString::number(col[2]) << Qt::endl << Qt::endl;
            progress.close();
        }
        int index = 0;
        for(int y = 0; y < 4; ++y){
            if(col[y] != 0){
                if(index != y){
                    moved = true;
                    noBuff = false;
                }
                col[index++] = col[y];
            }
        }
        for(; index < 4; ++index){
            col[index] = 0;
        }
        for(int y = 0; y < 4; ++y){
            getBlock(x, y)->setVal(col[y]);
        }
    }
    return moved;
}

bool Board::moveDown(){
    QFile progress("progress.txt");
    QTextStream out(&progress);
    int col[4];
    bool moved = false;
    for(int x = 0; x < 4; ++x){
        for(int y = 0; y < 4; ++y){
            bufferBlock[y][x] = getBlock(x, y)->getVal();
            col[y] = getBlock(x, y)->getVal();
        }
        if(col[2] == col[3] && col[2] != 0){
            score += col[3] + col[2];
            col[3] = col[3] + col[2];
            col[2] = 0;
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(4) << " " << QString::number(x + 1) << " " << QString::number(col[3]) << Qt::endl << Qt::endl;
            progress.close();
        }
        if(col[1] == col[2] && col[1] != 0){
            score += col[2] + col[1];
            col[2] = col[2] + col[1];
            col[1] = 0;
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(3) << " " << QString::number(x + 1) << " " << QString::number(col[2]) << Qt::endl << Qt::endl;
            progress.close();
        }
        if(col[0] == col[1] && col[0] != 0){
            score += col[1] + col[0];
            col[1] = col[1] + col[0];
            col[0] = 0;
            moved = true;
            noBuff = false;
            progress.open(QIODevice::Append | QIODevice::Text);
            out << "MERGE " << QString::number(2) << " " << QString::number(x + 1) << " " << QString::number(col[1]) << Qt::endl << Qt::endl;
            progress.close();
        }              
        int index = 3;
        for(int y = 3; y >= 0; --y){
            if(col[y] != 0){
                if(index != y){
                    noBuff = false;
                    moved = true;
                }
                col[index--] = col[y];
            }
        }
        for(; index >= 0; --index){
            col[index] = 0;
        }
        for(int y = 0; y < 4; ++y){
            getBlock(x, y)->setVal(col[y]);
        }
    }
    return moved;
}

bool Board::moveAble() const{
    for(int y = 0; y < 4; ++y){
        for(int x = 0; x < 4; ++x){
            if(getBlock(x, y)->getVal() == 0)
                return true;//moveable if any value is zero
            if(x < 3 && getBlock(x, y)->getVal() == getBlock(x + 1, y)->getVal())
                return true;//moveable if any adjacent value is equal
            if(y < 3 && getBlock(x, y)->getVal() == getBlock(x, y + 1)->getVal())
                return true;
        }
    }
    return false;
}

void Board::genRandBlock(){
    int empCount = 0;//number of empty blocks
    for(int y = 0; y < 4; ++y){
        for(int x = 0; x < 4; ++x){
            if(getBlock(x, y)->getVal() == 0){
                ++empCount;
            }
        }
    }
    int randIndex = QRandomGenerator::global()->bounded(empCount);//get random index

    int indexCount = 0;
    for(int y = 0; y < 4; ++y){
        for(int x = 0; x < 4; ++x){
            if(getBlock(x, y)->getVal() == 0){
                if(indexCount == randIndex){
                    int randVal = (QRandomGenerator::global()->bounded(5) == 0) ? 4 : 2;
                    getBlock(x, y)->setVal(randVal);//randomly initialize value

                    QFile progress("progress.txt");
                    progress.open(QIODevice::Append | QIODevice::Text);
                    QTextStream out(&progress);
                    out << "GENERATE " << QString::number(y + 1) <<
                        " " << QString::number(x + 1) <<
                        " " << QString::number(randVal) <<
                        Qt::endl << Qt::endl;
                    progress.close();//write on progress.txt

                    return;
                }
                indexCount++;
            }
        }
    }
}

int Board::getScore(){//wrapping function
    return score;
}

QString Board::getInit(){//wrapping function
    return initState;
}

void Board::restore(){
    for(int x = 0; x < 4; ++x){
        for(int y = 0; y < 4; ++y){
            getBlock(x, y)->setVal(bufferBlock[y][x]);//initilaize each block with buffer array
        }
    }
}
