/*
 ============================================================================
 Project     : Longest-prefix match
 Predmet     : PDS - Prenos dat, pocitacove site a protokoly
 File        : IPv6Trie.h
 Author      : Filip Zapletal (xzaple27@stud.fit.vutbr.cz)
 ============================================================================
 */

#pragma once

#include <stdint.h>
#include <string>
#include <iostream>

class IPv6Trie
{
public:
	IPv6Trie(void);
	~IPv6Trie(void);

	class Node
    {
    public:

        Node()
            :AsId(-1)
        { 
            for (int i = 0; i < 8; i++)
                Childs[i] = NULL;
        }

        Node(int asId, int prefix)
            :AsId(asId), AsPrefix(prefix)
        {
            for (int i = 0; i < 8; i++)
                Childs[i] = NULL;
        }

        ~Node()
        {
            for (int i = 0; i < 8; i++)
                delete Childs[i];
        }

        inline Node* AddChild(int value, int asId, int asPrefix)
        {
            return this->Childs[value] = new Node(asId, asPrefix);
        }

        inline Node* GetChild(int value) 
        {
            return this->Childs[value];
        }

        Node* Childs[8];
        int AsId;
        int AsPrefix;
    };

    void AddAddress(int address[8], int prefixLen, int asId);

    int FindAs(int address[8]);

private:
    Node* root;

};

