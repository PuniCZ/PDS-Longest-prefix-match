#include "ASMgr.h"


ASMgr::ASMgr(void)
{
}

ASMgr::~ASMgr(void)
{
}

bool ASMgr::Load(string sourceFile, IPv4Trie& tree)
{
    ifstream file(sourceFile);

    if (!file.is_open())
        return false;

    string line;
    int addr[4] = {-1, -1, -1, -1};
    int prefix = -1;
    int asId = -1;
    
    while (file.good())
    {
        getline(file, line);
        

        sscanf_s(line.c_str(), "%d.%d.%d.%d/%d %d", &addr[0], &addr[1], &addr[2], &addr[3], &prefix, &asId);

        //ASRecord(addr, prefix, asId);

        tree.AddAddress(addr, prefix, asId);

        //cout << line << endl;
    }

    file.close();

    return true;
}
