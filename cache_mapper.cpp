#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

class cache_mock
{
private:
    long int desc; // 0 - Set_Associative, 1 - Direct Mapping, 2 - Associative
    long int cache_size;
    long int mem_size;
    long int block_size;
    long int set_size;
    long int no_sets;
    long int lru;
    vector<vector<long int>> container;
    long int find_heirarchy_min(long int set);
    long int find_heirarchy_max(long int set);

public:
    cache_mock(long int, long int, long int, long int, long int = 0, long int = 0);
    void container_init();
    void container_display();
    long int loader(long int);
    long int storer(long int);
};

cache_mock::cache_mock(long int d, long int c, long int m, long int b, long int s, long int l) : desc(d), cache_size(c), mem_size(m), block_size(b), set_size(s), lru(l)
{
    if (d == 1)
        set_size = 1;
    else if (d == 2)
        set_size = c/b;
    no_sets = cache_size / (block_size * set_size);
    container_init();
}

void cache_mock::container_init()
{
    if (container.size())
        container.clear();
    long int size = cache_size / block_size;
    for (long int i = 0; i < size; i++)
    {
        vector<long int> block;
        block.push_back(i);
        block.push_back(-1);           //tag_bit
        block.push_back(0);            //dirty_bit
        block.push_back(i % set_size); //heirarchy
        for (long int j = 0; j < block_size; j++)
        {
            block.push_back(-1);
        }
        container.push_back(block);
    }
}

void cache_mock::container_display()
{
    printf("ID\tTag\tDirty\tHeirarchy\tBlock-Display\n");
    for (long int i = 0; i < container.size(); i++)
    {
        if (!(i % set_size))
        {
            printf("\n");
        }
        for (long int j = 0; j < container[i].size(); j++)
        {
            printf("%ld\t", container[i][j]);
            if (j == 3)
            {
                printf("\t");
            }
        }
        printf("\n");
    }
}

long int cache_mock::loader(long int address)
{
    if (address >= mem_size)
        return -1;
    long int block = address / block_size;
    long int set = block % no_sets;
    long int tag = address / (block_size * no_sets);
    for (long int i = 0; i < set_size; i++) // Hit Case!!!
    {
        if (container[set * set_size + i][1] == tag)
        {
            if (lru)
                container[set * set_size + i][3] = container[find_heirarchy_max(set)][3] + 1;
            return 1;
        }
    }
    //miss case
    long int min_heir=find_heirarchy_min(set);
    container[min_heir][1]=tag;
    container[min_heir][2]=0;
    container[min_heir][3]=container[find_heirarchy_max(set)][3]+1;
    for(int i=4;i<container[0].size();i++)
    {
        container[min_heir][i]=block*block_size+i-4;
    }
    return 0;    
}

long int cache_mock::storer(long int address)
{
    if (address >= mem_size)
        return -1;
    long int block = address / block_size;
    long int set = block % no_sets;
    long int tag = address / (block_size * no_sets);
    for (long int i = 0; i < set_size; i++) // Hit Case!!!
    {
        if (container[set * set_size + i][1] == tag)
        {
            if (lru)
                container[set * set_size + i][3] = container[find_heirarchy_max(set)][3] + 1;
            container[set*set_size+i][2]=1;
            return 1;
        }
    }
    //miss case
    long int min_heir=find_heirarchy_min(set);
    container[min_heir][1]=tag;
    container[min_heir][2]=0;
    container[min_heir][3]=container[find_heirarchy_max(set)][3]+1;
    for(int i=4;i<container[0].size();i++)
    {
        container[min_heir][i]=block*block_size+i-4;
    }
    return 0;    
}

long int cache_mock::find_heirarchy_max(long int set)
{
    long int max = set * set_size;
    for (long int i = 0; i < set_size; i++)
    {
        if (container[set * set_size + i][3] > container[max][3])
        {
            max = set * set_size + i;
        }
    }
    return (max);
}

long int cache_mock::find_heirarchy_min(long int set)
{
    long int min = set * set_size;
    for (long int i = 0; i < set_size; i++)
    {
        if (container[set * set_size + i][3] < container[min][3])
        {
            min = set * set_size + i;
        }
    }
    return (min);
}

int main()
{
    cache_mock a(2, 16, 2048, 2);
    cout<<a.loader(2047)<<endl;
    cout<<a.loader(1576)<<endl;
    a.container_display();
    return 0;
}