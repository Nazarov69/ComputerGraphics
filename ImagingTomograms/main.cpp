#include "View.h"
#include <QtWidgets/QApplication>

#pragma comment (lib, "opengl32.lib")
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    View w(NULL);
    w.LoadData("..//data//FOURDIX-systolic.bin");
    w.show();
    return a.exec();

}




