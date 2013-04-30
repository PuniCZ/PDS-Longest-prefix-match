/*
 ============================================================================
 Project     : Longest-prefix match
 Predmet     : PDS - Prenos dat, pocitacove site a protokoly
 File        : IPv4Trie.cpp
 Author      : Filip Zapletal (xzaple27@stud.fit.vutbr.cz)
 ============================================================================
 */

#include "IPv4Trie.h"


IPv4Trie::IPv4Trie(void)
{
    root = new Node();
}


IPv4Trie::~IPv4Trie(void)
{
}


void IPv4Trie::AddAddress(int address[4], int prefix, int asId)
{
    //convert
    int shift = 24;      
    int32_t addr = 0;
    for (int i = 0; i < 4; i++, shift -= 8)
    {
        addr |= address[i] << shift ;
    }

    //remove unused address end
    addr &= (0xffffffff << (32 - prefix));

    Node* currNode = root;

    //for every 2 bits
    for (int step = 0; step < 32; step+=2)
    {
        //convert group of 2 to number (0-3)
        int32_t addrPart = 0x00000003 & (addr >> (30-step));

        //if child not exist
        if (!currNode->Childs[addrPart])
        {
            if (prefix <= step + 1)
            {                
                //address end and creating 2 subnodes

                //create first
                currNode->AddChild(addrPart, asId, prefix);

                //check second and if exists
                if (currNode->Childs[addrPart + 1])
                {
                    //change only if this is more accurate (longer prefix than existing)
                    if (currNode->Childs[addrPart + 1]->AsPrefix <= prefix || currNode->Childs[addrPart + 1]->AsId == -1)
                    {
                        currNode->Childs[addrPart + 1]->AsId = asId;
                        currNode->Childs[addrPart + 1]->AsPrefix = prefix;
                    }
                }
                else
                {
                    //if not exist, just create
                    currNode->AddChild(addrPart+1, asId, prefix);
                }
                return;
            }
            else if (prefix <= step + 2)
            {
                //address end and creating one subnode
                currNode->AddChild(addrPart, asId, prefix);
                return;
            }
            else
            {
                //not address end - create path only
                currNode = currNode->AddChild(addrPart, -1, 0);
            }
        }
        else
        {
            //child node exists
            if (prefix <= step + 1)
            {
                //address end and changing/creating 2 subnodes
                currNode->Childs[addrPart]->AsId = asId;
                currNode->Childs[addrPart]->AsPrefix = prefix;

                //if second child not exists
                if (!currNode->Childs[addrPart + 1])
                {
                    //create it
                    currNode->AddChild(addrPart + 1, asId, prefix);
                }
                else
                {
                    //or check if this is better match
                    if (currNode->Childs[addrPart + 1]->AsPrefix <= prefix || currNode->Childs[addrPart + 1]->AsId == -1)
                    {
                        //and change it
                        currNode->Childs[addrPart + 1]->AsId = asId;
                        currNode->Childs[addrPart + 1]->AsPrefix = prefix;
                    }
                }
                return;
            }
            else if (prefix <= step + 2)
            {
                //address end and changing one subnode
                currNode->Childs[addrPart]->AsId = asId;
                currNode->Childs[addrPart]->AsPrefix = prefix;
                return;
            }
            else
            {
                //not end - just step to child
                currNode = currNode->Childs[addrPart];
            }
        }
    }
}

int IPv4Trie::FindAs(int address[4])
{
    //convert
    int shift = 24;      
    int32_t addr = 0;
    for (int i = 0; i < 4; i++, shift -= 8)
    {
        addr |= address[i] << shift ;
    }
    
    Node* currNode = root;
    int asId = -1;

    //for every 2 bits
    for (int step = 0; step < 32; step+=2)
    {
        //convert group of 2 to number (0-3)
        int32_t addrPart = 0x00000003 & (addr >> (30-step));

        if (!currNode->Childs[addrPart])
            break;

        currNode = currNode->Childs[addrPart];
        if (currNode->AsId != -1)
            asId = currNode->AsId;
    }
    return asId;
}