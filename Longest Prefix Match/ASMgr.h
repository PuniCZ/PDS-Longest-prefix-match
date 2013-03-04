#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdint.h>


#include "IPv4Trie.h"
#include "IPv6Trie.h"


using namespace std;

vector<string> split(const string& s, const string& delim, const bool keep_empty = true);

class ASMgr
{
public:
    ASMgr(void);
    ~ASMgr();

    bool Load(string sourceFile);

    int Find(string address);

    static void StringToIPv6(string& str, int addr6[8], int &prefix, int &asId);
    static void StringToIPv6(string& str, int addr6[8])
    {
        int prefix, asId;
        StringToIPv6(str, addr6, prefix, asId);

    }

private:

    IPv4Trie ipv4Trie;
    IPv6Trie ipv6Trie;

};

