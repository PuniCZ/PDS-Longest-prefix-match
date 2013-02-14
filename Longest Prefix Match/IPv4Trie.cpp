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
            if (prefix <= step+1)
            {                
                //end and 2 nodes creation
                currNode->AddChild(addrPart, asId);
                currNode->AddChild(addrPart+1, asId);
                return;
            }
            else if (prefix <= step+2)
            {
                //end and 1 node creation
                currNode->AddChild(addrPart, asId);
                return;
            }
            else
            {
                //not end - create path only
                currNode = currNode->AddChild(addrPart, -1);

            }
        }
        else
        {
            //if exists just step to child
            currNode = currNode->Childs[addrPart];
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