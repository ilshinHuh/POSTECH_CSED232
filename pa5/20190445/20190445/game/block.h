#ifndef BLOCK_H
#define BLOCK_H
#include <QLabel>

class Block : public QLabel
{
public:
    Block(int value = 0);//constructor

    int getVal() const;//value wrapping function
    void setVal(int value);//setting function

    ~Block(){}//destructor
private:
    int blockVal;//value of block
};

#endif // BLOCK_H
