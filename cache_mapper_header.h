#ifndef cm
#define cm
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
    long int lru; //when lru=0, fifo is followed
    vector<vector<long int>> container;
    long int find_hierarchy_min(long int set);
    long int find_hierarchy_max(long int set);

public:
    cache_mock(long int, long int, long int, long int, long int = 1, long int = 0);
    cache_mock();
    void cache_mock_copy(cache_mock &);
    void container_init();     // can be used to clear cache data too
    void container_display();  //diplays cache mainframe
    long int loader(long int); //when data is to be loaded to the processor
    long int storer(long int); //when data is to be stored by the processor
    long int refresh_dirty();  // refreshes all dirty_bits to 0
    ~cache_mock();
};
#endif