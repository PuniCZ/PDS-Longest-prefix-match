/*
 ============================================================================
 Project     : Longest-prefix match
 Predmet     : PDS - Prenos dat, pocitacove site a protokoly
 File        : main.cpp
 Author      : Filip Zapletal (xzaple27@stud.fit.vutbr.cz)
 ============================================================================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

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
        cerr << "Bad params" << endl;
        return -1;
    }
    
    ASMgr asMgr;

#ifdef DEBUG
    cerr << "Loading..." << endl;
    int start = clock();
#endif

    //load AS definition and build tries
    if (!asMgr.Load(fileName))
    {
        cerr << "Input AS file cannot be loaded." << endl;
        return -1;
    }

#ifdef DEBUG
    cerr << "Loaded in " << (clock() - start) << endl;    
    cerr << "Working..." << endl;
    start = clock();
#endif

    //read input data form stdin
    string line;
    while (cin.good())
    {
        getline(cin, line);
        if (line != "")
        {
            int result = asMgr.Find(line);
            
            if (result == -1)
                cout << "-" << endl;
            else
                cout << result << endl;
        }
    }

#ifdef DEBUG
    cerr << "Finished in " << (clock() - start) << endl;  
#endif
}



