/*
 ============================================================================
 Project     : Longest-prefix match
 Predmet     : PDS - Prenos dat, pocitacove site a protokoly
 File        : ASMgr.h
 Author      : Filip Zapletal (xzaple27@stud.fit.vutbr.cz)
 ============================================================================
 */

#include "ASMgr.h"


ASMgr::ASMgr(void)
{
}

ASMgr::~ASMgr(void)
{
}


void ASMgr::StringToIPv6(string& str, int addr6[8], int &prefix, int &asId)
{
    char c, lastC;
    int i = 0, ii = 0, byteCounter = 0, byteCounter2 = 0;
    int state = 0;
    char buff[15];
    int addr6tmp[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

    while ((c = str.c_str()[i]) != 0)
    {
        switch (state)
        {
            case 0: //part before ::
            case 1: //part after ::
                if (c == '/')
                {   
                    if (ii != 0)
                    {
                        buff[ii] = 0;
                            
                        if (state == 0)
                        {
                            sscanf(buff, "%x", &addr6[byteCounter]);
                            byteCounter++;
                        }
                        else
                        {
                            sscanf(buff, "%x", &addr6tmp[byteCounter2]);
                            byteCounter2++;
                        }
                    }
                    ii=-1;
                    state = 2;
                }
                else if (c == ':') //is :
                {
                    if (lastC != ':')
                    {
                        //parse buff to int
                        buff[ii] = 0;
                        if (state == 0)
                        {
                            sscanf(buff, "%x", &addr6[byteCounter]);
                            byteCounter++;
                        }
                        else
                        {
                            sscanf(buff, "%x", &addr6tmp[byteCounter2]);
                            byteCounter2++;
                        }
                        ii=-1;
                    }
                    else //found ::
                    {
                        ii=-1;
                        state = 1;
                    }
                }
                else //normal character
                    buff[ii] = c;
                break;

            case 2: //after / (prefix length part)
                    buff[ii] = c;
                break;
        }
        lastC = c;
        i++;
        ii++;
    }

    if (state == 2)
    {
        //parse AS id
        buff[ii] = 0;
        sscanf(buff, "%d %d", &prefix, &asId);
    }


    if (state < 2)
    {
        if (ii != 0)
        {
            buff[ii] = 0;
                            
            if (state == 0)
            {
                sscanf(buff, "%x", &addr6[byteCounter]);
                byteCounter++;
            }
            else
            {
                sscanf(buff, "%x", &addr6tmp[byteCounter2]);
                byteCounter2++;
            }
        }
    }
    
    //fill address missing parts
    ii=0;
    for (int i = byteCounter; i < 8; i++)
    {
        if (i < 8 - byteCounter2)
        {
            addr6[i] = 0;
        }
        else
        {
            addr6[i] = addr6tmp[ii++];
        }
    }
    
}

bool ASMgr::Load(string sourceFile)
{
    ifstream file(sourceFile.c_str());

    if (!file.is_open())
        return false;

    string line;
    int addr[4] = {-1, -1, -1, -1};
    int addr6[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    int prefix = -1;
    int asId = -1;
        
    while (file.good())
    {
        getline(file, line);
        
        if (line == "")
            continue;

        if (sscanf(line.c_str(), "%d.%d.%d.%d/%d %d", &addr[0], &addr[1], &addr[2], &addr[3], &prefix, &asId) == 6)
        {
            //ipv4
            ipv4Trie.AddAddress(addr, prefix, asId);
        }
        else
        {
            //ipv6
            StringToIPv6(line, addr6, prefix, asId);

            //add to tree
            ipv6Trie.AddAddress(addr6, prefix, asId);
        }
    }
    file.close();

    return true;
}

int ASMgr::Find(string address)
{
    int addr[4] = {-1, -1, -1, -1};
    int addr6[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

    if (sscanf(address.c_str(), "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]) == 4)
        {
            //ipv4
            return ipv4Trie.FindAs(addr);
        }
        else
        {
            //ipv6
            StringToIPv6(address, addr6);
            
            return ipv6Trie.FindAs(addr6);
        }
}
