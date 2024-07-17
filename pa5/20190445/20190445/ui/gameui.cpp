#include "gameui.h"

GameUi::GameUi(QWidget *parent) : QWidget(parent), restoreCount(3)
{
    //dynamically allocate member variables
    mainLayout = new QGridLayout(this);
    game = new Game();
    board = new QGridLayout(this);
    gameBoard = new BlockUi**[4];

    for(int x = 0; x < 4; ++x){
        gameBoard[x] = new BlockUi*[4];
        for(int y = 0; y < 4; ++y){
            QLabel *label = new QLabel(this);
            gameBoard[x][y] = new BlockUi(label, game->getBoard()->getBlock(x, y));//set ui for block
            board->addWidget(gameBoard[x][y], y, x);//put to board
        }
    }
    //set gui as required
    board->setSpacing(10);
    QWidget* gridBoard = new QWidget;
    gridBoard->setLayout(board);
    mainLayout->addWidget(gridBoard, 0, 0, 3, 1);

    scoreLabel = new QLabel("Score: 0", this);
    mainLayout->addWidget(scoreLabel, 0, 1, 1, 1, Qt::AlignTop | Qt::AlignLeft);

    exitButton = new QPushButton("Exit", this);
    exitButton->setFixedSize(300, 200);
    exitButton->setFont(QFont("Arial", 20));
    mainLayout->addWidget(exitButton, 1, 1, 1, 1);

    restoreButton = new QPushButton("Restore", this);
    restoreButton->setFixedSize(300, 200);
    restoreButton->setFont(QFont("Arial", 20));
    mainLayout->addWidget(restoreButton, 2, 1, 1, 1);

    connect(exitButton, &QPushButton::clicked, this, &GameUi::showExit);
    connect(restoreButton, &QPushButton::clicked, this, &GameUi::showRestore);

    setLayout(mainLayout);
    resize(1300, 1000);
}

GameUi::~GameUi(){//destructor
    delete mainLayout;
    delete board;
    delete scoreLabel;
    delete exitButton;
    delete restoreButton;
    delete game;
    for(int i = 0; i< 4; ++i){
        for(int j = 0; j < 4; ++j){
            delete gameBoard[i][j];
        }
        delete[] gameBoard[i];
    }
    delete[] gameBoard;
    //delete every dynamically allocated elements
}

void GameUi::keyPressEvent(QKeyEvent* event){
    QFile progress("progress.txt");
    QTextStream out(&progress);//prepare for writing on preogress.txt
    switch(event->key()){
    case Qt::Key_Left:{//move left!
        progress.open(QIODevice::Append | QIODevice::Text);
        out << "LEFT" << Qt::endl << Qt::endl;
        progress.close();//write LEFT

        if(game->getBoard()->moveLeft()){//if anything was moved
            game->getBoard()->genRandBlock();//generate new block

            progress.open(QIODevice::Append | QIODevice::Text);
            out << "SCORE " << QString::number(game->getBoard()->getScore()) << Qt::endl << Qt::endl;
            progress.close();//write what was generated
        }
        break;
    }
    case Qt::Key_Right:{
        progress.open(QIODevice::Append | QIODevice::Text);
        out << "RIGHT" << Qt::endl << Qt::endl;
        progress.close();

        if(game->getBoard()->moveRight()){
            game->getBoard()->genRandBlock();

            progress.open(QIODevice::Append | QIODevice::Text);
            out << "SCORE " << QString::number(game->getBoard()->getScore()) << Qt::endl << Qt::endl;
            progress.close();
        }
        break;
    }
    case Qt::Key_Up:{
        progress.open(QIODevice::Append | QIODevice::Text);
        out << "UP" << Qt::endl << Qt::endl;
        progress.close();

        if(game->getBoard()->moveUp()){
            game->getBoard()->genRandBlock();

            progress.open(QIODevice::Append | QIODevice::Text);
            out << "SCORE " << QString::number(game->getBoard()->getScore()) << Qt::endl << Qt::endl;
            progress.close();
        }
        break;
    }
    case Qt::Key_Down:{
        progress.open(QIODevice::Append | QIODevice::Text);
        out << "DOWN" << Qt::endl << Qt::endl;
        progress.close();

        if(game->getBoard()->moveDown()){
            game->getBoard()->genRandBlock();

            progress.open(QIODevice::Append | QIODevice::Text);
            out << "SCORE " << QString::number(game->getBoard()->getScore()) << Qt::endl << Qt::endl;
            progress.close();
        }
        break;
    }
    }
    updateUi();//update gui
}

void GameUi::updateUi(){
    for(int x = 0; x < 4; ++x){
        for(int y = 0; y < 4; ++y){
            gameBoard[x][y]->update(game->getBoard()->getBlock(x, y));//update each block
        }
    }
    scoreLabel->setText("Score: " + QString::number(game->getBoard()->getScore()));//update score ui
    switch(game->isGameOver()){
        case 0://win
            QMessageBox::information(this, "Win", "Congratulation!\n\nScore: " + QString::number(game->getBoard()->getScore()));
            QApplication::quit();
            break;
        case 1://lose
            QMessageBox::information(this, "Lose", "You lose...\n\nScore: " + QString::number(game->getBoard()->getScore()));
            QApplication::quit();
            break;
    }
}

void GameUi::showExit(){//exit button pressed
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit", "Are you sure to quit?", QMessageBox::Yes | QMessageBox::No);;//ask again
    if(reply == QMessageBox::Yes)//ansewr is yes
        QApplication::quit();//quit application
}

void GameUi::showRestore(){
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Restore",//ask again with info
        "Restore the game board to its previous state?\n\nRemaining chances: " + QString::number(restoreCount), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes && restoreCount > 0 && !game->getBoard()->noBuff){//restoreable!
        QMessageBox::information(this, "Restore", "The board has been restored to its previous state!");
        game->getBoard()->restore();//restore
        --restoreCount;//erase one chance
        game->getBoard()->noBuff = true;//no buffer!
        updateUi();//update interface

        QFile progress("progress.txt");
        progress.open(QIODevice::Append | QIODevice::Text);
        QTextStream out(&progress);
        out << "RESTORE " << QString::number(restoreCount) << Qt::endl << Qt::endl;
        progress.close();//write on progress.txt
    }
    else if(reply == QMessageBox::Yes && game->getBoard()->noBuff){//no buffer
        QMessageBox::information(this, "Restore", "There is no previously saved board in the buffer.");
    }
    else if(reply == QMessageBox::Yes && restoreCount == 0){//no chance left
        QMessageBox::information(this, "Restore", "No more chance to restore the board to its previous state.");
    }
}
