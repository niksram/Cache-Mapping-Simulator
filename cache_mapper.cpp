#include "cache_mapper_header.h"

cache_mock::cache_mock(long int d, long int c, long int m, long int b, long int l, long int s) : desc(d), cache_size(c), mem_size(m), block_size(b), lru(l), set_size(s)
{
    if (d == 1)
        set_size = 1;
    else if (d == 2)
        set_size = c / b;
    no_sets = cache_size / (block_size * set_size);
    container_init();
}

cache_mock::cache_mock() : desc(1), cache_size(1), mem_size(1), block_size(1), lru(1), set_size(1)
{
}

void cache_mock::cache_mock_copy(cache_mock &c)
{
    this->desc = c.desc;
    this->cache_size = c.cache_size;
    this->mem_size = c.mem_size;
    this->block_size = c.block_size;
    this->lru = c.lru;
    this->set_size = c.set_size;
    this->no_sets=c.no_sets;
    this->container = c.container;
    //copy(c.container.begin(), c.container.end(), this->container.begin());
}

cache_mock::~cache_mock()
{
    container.clear();
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
        block.push_back(i % set_size); //hierarchy
        for (long int j = 0; j < block_size; j++)
        {
            block.push_back(-1);
        }
        container.push_back(block);
    }
}

void cache_mock::container_display()
{
    if(!desc)
        printf("Set\t");
    printf("ID\tTag\tDirty\thierarchy\tBlock-Display\n");
    for (long int i = 0; i < container.size(); i++)
    {
        if (!desc)
        {
            if(!(i % set_size))
            {
                printf("\n");
                printf("%ld",i/set_size);
            }
            printf("\t");
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
    if (address >= mem_size || address < 0)
        return -1;
    long int block = address / block_size;
    long int set = block % no_sets;
    long int tag = address / (block_size * no_sets);
    for (long int i = 0; i < set_size; i++) // Hit Case!!!
    {
        if (container[set * set_size + i][1] == tag)
        {
            if (lru)
                container[set * set_size + i][3] = container[find_hierarchy_max(set)][3] + 1;
            return 1;
        }
    }
    //miss case
    long int min_heir = find_hierarchy_min(set);
    container[min_heir][1] = tag;
    container[min_heir][2] = 0;
    container[min_heir][3] = container[find_hierarchy_max(set)][3] + 1;
    for (int i = 4; i < container[0].size(); i++)
    {
        container[min_heir][i] = block * block_size + i - 4;
    }
    return 0;
}

long int cache_mock::storer(long int address)
{
    if (address >= mem_size || address < 0)
        return -1;
    long int block = address / block_size;
    long int set = block % no_sets;
    long int tag = address / (block_size * no_sets);
    for (long int i = 0; i < set_size; i++) // Hit Case!!!
    {
        if (container[set * set_size + i][1] == tag)
        {
            if (lru)
                container[set * set_size + i][3] = container[find_hierarchy_max(set)][3] + 1;
            container[set * set_size + i][2] = 1;
            return 1;
        }
    }
    //miss case
    long int min_heir = find_hierarchy_min(set);
    container[min_heir][1] = tag;
    container[min_heir][2] = 0;
    container[min_heir][3] = container[find_hierarchy_max(set)][3] + 1;
    for (int i = 4; i < container[0].size(); i++)
    {
        container[min_heir][i] = block * block_size + i - 4;
    }
    return 0;
}

long int cache_mock::find_hierarchy_max(long int set)
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

long int cache_mock::find_hierarchy_min(long int set)
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

long int cache_mock::refresh_dirty()
{
    for (int i = 0; i < container.size(); i++)
    {
        container[i][2] = 0;
    }
}