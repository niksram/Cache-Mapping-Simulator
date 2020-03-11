CLASS cache_mock
    
    cache_size: size of cache frame
    block_size: size of each block
    mem_size: size of the main memory
    set_size: size of the set, 1 in Direct-Map, cache_size in Fully-Associative
    lru: 1 for Least-Recently-Used and 0 for First-In-First-Out Heirarchy
    no_sets: total number of sets in the cache
    
    container: Vector matrix which simulates the functioning of cache.

Functions
    
    loader: used to simulate loading data to processor from cache
    storer: used to simulate storing data to cache from processor
    display: displays the container frame
    container_init: initialises the container frame
    refresh_dirty: sets all dirty-bits to zero

Client
    
    self-explanatory