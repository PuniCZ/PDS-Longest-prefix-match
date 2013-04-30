/*
 ============================================================================
 Project     : Longest-prefix match
 Predmet     : PDS - Prenos dat, pocitacove site a protokoly
 File        : IPv6Trie.cpp
 Author      : Filip Zapletal (xzaple27@stud.fit.vutbr.cz)
 ============================================================================
 */

#include "IPv6Trie.h"


IPv6Trie::IPv6Trie(void)
{
    root = new Node();
}


IPv6Trie::~IPv6Trie(void)
{
}

void IPv6Trie::AddAddress(int address[8], int prefix, int asId)
{
    //remove unused address end
    int offsetInt = prefix / 16;
    if (offsetInt < 8)
        address[offsetInt] &= 0xffffffff << (16 - (prefix % 16));
    for (int i = offsetInt + 1; i < 8; i++)
        address[i] = 0;

    Node* currNode = root;

    //for every part 
    for (int index = 0; index < 8; index++)
    {
        //for every 2 bits
        for (int step = 0; step < 16; step+=2)
        {
            //convert group of 2 to number (0-3)
            int32_t addrPart = 0x00000003 & (address[index] >> (14-step));

            //if child not exist
            if (!currNode->Childs[addrPart])
            {                
                if (prefix <= (index * 16) + step + 1)
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
                else if (prefix <= (index * 16) + step + 2)
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
                if (prefix <= (index * 16) + step + 1)
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
                else if (prefix <= (index * 16) + step + 2)
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
}

int IPv6Trie::FindAs(int address[8])
{
    Node* currNode = root;
    int asId = -1;

    //for every part 
    for (int index = 0; index < 8; index++)
    {
        //for every 2 bits
        for (int step = 0; step < 16; step+=2)
        {
            //convert group of 2 to number (0-3)
            int32_t addrPart = 0x00000003 & (address[index] >> (14-step));

            if (!currNode->Childs[addrPart])
                return asId;

            currNode = currNode->Childs[addrPart];
            if (currNode->AsId != -1)
                asId = currNode->AsId;
        }
    }
    return asId;
}
