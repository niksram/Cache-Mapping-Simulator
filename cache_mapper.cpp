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
    long int lru;
    vector<vector<long int>> container;
    long int min_heirarchy(long int set, long int update);

public:
    cache_mock(long int, long int, long int, long int, long int = 0, long int = 0);
    void container_init();
    void container_display();
    long int loader(long int);
};

cache_mock::cache_mock(long int d, long int c, long int m, long int b, long int s, long int l) : desc(d), cache_size(c), mem_size(m), block_size(b), set_size(s), lru(l)
{
    if (d == 1)
        set_size = 1;
    else if (d == 2)
        set_size = c;
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
        block.push_back(-1);           //dirty_bit
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
    long int set = block / set_size;
    long int tag = mem_size / cache_size;
    for (int i = 4; i < container[0].size(); i++)
    {
        container[set * set_size + minh][i] = block * block_size + i - 4;
    }
}

long int cache_mock::min_heirarchy(long int set, long int update)
{
    long int block = set * set_size;
    long int min = block;
    long int max = block;
    for (long int i = 0; i < set_size; i++)
    {
        if (container[set * set_size + i][3] < container[min][3])
        {
            min = set * set_size + i;
        }
        if (ontainer[set * set_size + i][3] > container[max][3])
        {
            max = set * set_size + i;
        }
    }
    if (update)
    {
        container[set * set_size + i][3] = container[max][3] + 1;
    }
    return min;
}

int main()
{
    cache_mock a(1, 16, 2048, 2);
    a.loader(17);
    a.container_display();
    return 0;
}