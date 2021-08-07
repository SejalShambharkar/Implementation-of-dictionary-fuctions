#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<fstream>
#include<unistd.h>
#include<conio.h>
#define ALPHABETS 26
using namespace std;
class LRUCache
{
private:
    /*Node for each key*/
    struct LRUNode
    {
        int key, val;
        struct LRUNode *prev, *next;
        LRUNode() : prev(NULL), next(NULL) {}
        LRUNode(int key, int val) : key(key), val(val), prev(NULL), next(NULL) {}
    };

int cap;                                //Capacity of LRU cache
    int curCnt;                         //Current cnt of nodes
    unordered_map<int, LRUNode *> M;    //Map from key to corresponding node

    LRUNode *oldNode, *newNode;         //Oldest and newest LRU node

    /*Adjust paramters after current query for key*/
    void curQuery(int key)
    {
        LRUNode *temp = M[key];
        if (temp == newNode)
            return;
        LRUNode *prev = temp->prev;
        LRUNode *next = temp->next;
        if (temp == oldNode)
        {
            oldNode = next;
            next->prev = NULL;
            newNode->next = temp;
            temp->prev = newNode;
            temp->next = NULL;
            newNode = temp;
        }
        else
        {
            prev->next = next;
            next->prev = prev;
            newNode->next = temp;
            temp->prev = newNode;
            temp->next = NULL;
            newNode = temp;
        }
        return;
    }

    /*Add key*/
    void addKey(int key)
    {
        if (!newNode)
        {
            newNode = M[key];
            oldNode = newNode;
            return;
        }
        LRUNode *temp = M[key];
        newNode->next = temp;
        temp->prev = newNode;
        newNode = temp;
        return;
    }

    /*Removes oldest query in cache*/
    void removeOldest()
    {
        curCnt--;
        int key = oldNode->key;
        if (oldNode == newNode)
        {
            M.erase(key);
            oldNode = newNode = NULL;
            return;
        }
        oldNode = oldNode->next;
        oldNode->prev = NULL;
        M.erase(key);
        return;
    }

public:
    LRUCache(int capacity)
    {
        cap = capacity;
        curCnt = 0;
        oldNode = NULL;
        newNode = NULL;
    }

    int get(int key)
    {
        if (M.find(key) != M.end())
        {
            curQuery(key);
            return M[key]->val;
        }
        return -1;
    }

    void put(int key, int value)
    {
        if (M.find(key) != M.end())
        {
            M[key]->val = value;
            curQuery(key);
        }
        else
        {
            LRUNode *temp = new LRUNode(key, value);
            M[key] = temp;
            if (curCnt == cap)
                removeOldest();
            curCnt++;
            addKey(key);
        }
    }
};
