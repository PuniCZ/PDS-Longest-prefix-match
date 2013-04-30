/*
 ============================================================================
 Project     : Longest-prefix match
 Predmet     : PDS - Prenos dat, pocitacove site a protokoly
 File        : IPv4Trie.h
 Author      : Filip Zapletal (xzaple27@stud.fit.vutbr.cz)
 ============================================================================
 */

#pragma once

#include <stdint.h>
#include <string>
#include <iostream>

class IPv4Trie
{
public:
    IPv4Trie(void);
    ~IPv4Trie(void);

    

    class Node
    {
    public:

        Node()
            :AsId(-1)
        { 
            for (int i = 0; i < 4; i++)
                Childs[i] = NULL;
        }

        Node(int asId, int prefix)
            :AsId(asId), AsPrefix(prefix)
        {
            for (int i = 0; i < 4; i++)
                Childs[i] = NULL;
        }

        ~Node()
        {
            for (int i = 0; i < 4; i++)
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

        Node* Childs[4];
        int AsId;
        int AsPrefix;
    };

    void AddAddress(int address[4], int prefixLen, int asId);

    int FindAs(int address[4]);


private:
    Node* root;


};

