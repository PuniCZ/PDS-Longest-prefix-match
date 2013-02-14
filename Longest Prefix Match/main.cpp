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
#include "IPv4Trie.h"

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
    IPv4Trie trie;

    //asMgr.Load(fileName, trie);


    int addr[4] = {-1, -1, -1, -1};
    int prefix = -1;
    int asId = -1;


    sscanf_s("88.0.0.0/8 88", "%d.%d.%d.%d/%d %d", &addr[0], &addr[1], &addr[2], &addr[3], &prefix, &asId); trie.AddAddress(addr, prefix, asId);
    sscanf_s("88.0.0.1", "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]);
    asId = trie.FindAs(addr);


    sscanf_s("1.0.0.0/9 108", "%d.%d.%d.%d/%d %d", &addr[0], &addr[1], &addr[2], &addr[3], &prefix, &asId); trie.AddAddress(addr, prefix, asId);
    sscanf_s("1.64.0.0/16 6416", "%d.%d.%d.%d/%d %d", &addr[0], &addr[1], &addr[2], &addr[3], &prefix, &asId); trie.AddAddress(addr, prefix, asId);
    
    sscanf_s("1.0.0.1", "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]);
    asId = trie.FindAs(addr);

    sscanf_s("1.78.0.1", "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]);
    asId = trie.FindAs(addr);



    sscanf_s("192.168.0.0/17 1", "%d.%d.%d.%d/%d %d", &addr[0], &addr[1], &addr[2], &addr[3], &prefix, &asId); trie.AddAddress(addr, prefix, asId);
    sscanf_s("192.168.64.0/24 64", "%d.%d.%d.%d/%d %d", &addr[0], &addr[1], &addr[2], &addr[3], &prefix, &asId); trie.AddAddress(addr, prefix, asId);
    sscanf_s("192.168.128.0/24 128", "%d.%d.%d.%d/%d %d", &addr[0], &addr[1], &addr[2], &addr[3], &prefix, &asId); trie.AddAddress(addr, prefix, asId);
    sscanf_s("192.168.196.0/24 196", "%d.%d.%d.%d/%d %d", &addr[0], &addr[1], &addr[2], &addr[3], &prefix, &asId); trie.AddAddress(addr, prefix, asId);
    sscanf_s("192.168.224.0/24 224", "%d.%d.%d.%d/%d %d", &addr[0], &addr[1], &addr[2], &addr[3], &prefix, &asId); trie.AddAddress(addr, prefix, asId);


    sscanf_s("192.168.0.1", "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]);
    asId = trie.FindAs(addr);

    sscanf_s("192.168.64.1", "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]);
    asId = trie.FindAs(addr);

    sscanf_s("192.168.78.1", "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]);
    asId = trie.FindAs(addr);

    sscanf_s("192.168.247.1", "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]);
    asId = trie.FindAs(addr);




    getchar();

}



