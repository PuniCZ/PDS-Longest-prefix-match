#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdint.h>


#include "IPv4Trie.h"


using namespace std;

vector<string> split(const string& s, const string& delim, const bool keep_empty = true);

class ASMgr
{
public:
    ASMgr(void);
    ~ASMgr();

    bool Load(string sourceFile, IPv4Trie& tree);

    static void StringToIPv6(string& str, int addr6[8], int &prefix, int &asId);

private:

    IPv4Trie ipv4Trie;

};

