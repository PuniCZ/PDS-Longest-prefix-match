#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdint.h>



using namespace std;


class ASRecord
{
public:
    ASRecord(int address[4], int prefix, int asId)
        :addr_v4(0)
    {
        int shift = 24;      
        for (int i = 0; i < 4; i++, shift -= 8)
        {
            addr_v4 |= address[i] << shift ;
        }

        addr_v4 &= (0xffffffff << (32 - prefix));
    }

    ASRecord(int address[4], int prefix, int asId)
        :addr_v4(0)
    {
        int shift = 24;      
        for (int i = 0; i < 4; i++, shift -= 8)
        {
            addr_v4 |= address[i] << shift ;
        }

        addr_v4 &= (0xffffffff << (32 - prefix));
    }
    

private:
    int32_t addr_v4;
    int64_t addr_v6[2];

};

class ASMgr
{
public:
    ASMgr(void);
    ~ASMgr();

    bool Load(string sourceFile);

};

