#include "ui/gameui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameUi gameUi;
    gameUi.show();
    gameUi.setFocus();
    return a.exec();//start app
}
