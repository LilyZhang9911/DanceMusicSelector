#include <ctime>
#include <iostream>
#include "src/PlayList.h"
using namespace std;

// compiler option: add -lwinmm


int main() {
    PlayList p;
    char cmd;
    p.menu();
    do{
        cin >> cmd;
    } while (p.process_cmd(cmd));
    return 0;
}
