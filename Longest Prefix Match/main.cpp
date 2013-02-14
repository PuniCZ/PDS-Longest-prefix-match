// Longest Prefix Match.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <csignal>

#include "ASMgr.h"

using namespace std;

int main(int argc, char **argv) {   
    
    string fileName;

    if (argc == 3 && string(argv[1]) == "-i")
    {
        fileName = string(argv[2]);
    }
    else
    {
        cout << "Bad params";
    }

    cout << fileName;

    ASMgr asMgr;

    asMgr.Load(fileName);


    getchar();

}



