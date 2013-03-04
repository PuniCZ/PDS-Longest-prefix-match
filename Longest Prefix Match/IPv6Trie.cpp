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
	int offsetInt = prefix / 32;
	address[offsetInt] &= 0xffffffff << (32 - (prefix % 32));
	for (int i = offsetInt + 1; i < 8; i++)
		address[i] = 0;

    Node* currNode = root;

	//for every part 
	for (int index = 0; index < 8; index++)
	{
		//for every 2 bits
		for (int step = 0; step < 32; step+=2)
		{
			//convert group of 2 to number (0-3)
			int32_t addrPart = 0x00000003 & (address[index] >> (30-step));

			//if child not exist
			if (!currNode->Childs[addrPart])
			{
				if (prefix <= (index + 1) * step + 1)
				{                
					//end and 2 nodes creation
					currNode->AddChild(addrPart, asId);
					currNode->AddChild(addrPart + 1, asId);
					return;
				}
				else if (prefix <= (index + 1) * step + 2)
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
}

int IPv6Trie::FindAs(int address[8])
{
    Node* currNode = root;
    int asId = -1;

    //for every part 
	for (int index = 0; index < 8; index++)
	{
        //for every 2 bits
        for (int step = 0; step < 32; step+=2)
        {
            //convert group of 2 to number (0-3)
            int32_t addrPart = 0x00000003 & (address[index] >> (30-step));

            if (!currNode->Childs[addrPart])
                break;

            currNode = currNode->Childs[addrPart];
            if (currNode->AsId != -1)
                asId = currNode->AsId;
        }
    }
    return asId;

}
