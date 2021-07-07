#include<bits/stdc++.h>
using namespace std;
typedef long long lli;
int n,maxlen,q,k;
struct node
{
    node *child[26];
    int prefix;int num;
    vector<string>went;
    node()
    {
        for(int i=0;i<26;i++)
        {
            child[i]=NULL;
            prefix=0;
            num=0;
        }
    }
};
struct trie
{
    node *root;
    trie()
    {
        root=new node;
    }
};
void insert(string s,trie r)
{
    node *cur=r.root;
    for(int i=0;i<s.length();i++)
    {
        cur->prefix++;
        int x=s[i]-'a';
        if(cur->child[x]==NULL)
        {
            cur->child[x]=new node;
        }
        cur=cur->child[x];
    }
    cur->num++;
    cur->went.push_back(s);
}
void autosuggestion(node *cur)
{
    int f=0;
    if(cur!=NULL && !cur->went.empty() && k>0)
    {
        int x=cur->num;
        while(k>0 && x>0)
        {
            cout<<cur->went.back()<<" ";
            k--;
            x--;
        }
    }
    for(int i=0;i<=25 && k>0;i++)
    {
        if(cur!=NULL)
        {
            autosuggestion(cur->child[i]);
            f=1;
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int i;
    cin>>n>>maxlen>>q;
    trie t;
    for(i=0;i<n;i++)
    {
        int x;
        string s;
        cin>>x>>s;
        insert(s, t);
    }
    for(int z=0;z<q;z++)
    {
        int x;
        string st;
        cin>>x>>st>>k;
        int q=k;
        for(i=0;i<x;i++)
        {
            node *cur=t.root;
            for(int j=0;j<=i;j++)
            {
                int m=st[j]-'a';
                if(cur!=NULL)
                    cur=cur->child[m];
            }
            autosuggestion(cur);
            cout<<"\n";
            k=q;
        }
    }
}
