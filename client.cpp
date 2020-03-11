#include "cache_mapper_header.h"

int main()
{
    cache_mock Cacher;
    cout << "Cache-Mapper\n"
         << endl;
    cout << "Input only compatible values (such as power of 2s, etc)\n"
         << endl;
    long int d, c, m, b, s, l; // default meaning as in 'cache_mapper.cpp' constructor call;
    long int address;
    cout << "Enter 0 for Set-Associative, 1 for Direct-Map, 2 for Fully-Associative" << endl;
    cin >> d;
    cout << "Enter Memory-Size, Cache-Size, Block-Size in Bytes/Words (stick to 1 convention)" << endl;
    cin >> m >> c >> b;
    cout << "Enter 1 for Least-Recently-Used, 0 for First-In-First-Out Heirarchy" << endl;
    cin >> l;
    if (!d)
    {
        cout << "Enter X for X-way associative";
        cin >> s;
        cache_mock temp(d, c, m, b, l, s);
        Cacher.cache_mock_copy(temp);
    }
    else
    {
        cache_mock temp(d, c, m, b, l);
        Cacher.cache_mock_copy(temp);
    }
    int flag = 1;
    int val;
    cout << "0 to display, 1 to load followed by address, 2 to store followed by address" << endl;
    cout << "3 to refresh dirty_bits, 4 to clear cache main_frame, else exit" << endl;
    while (flag)
    {
        cout << "Input" << endl;
        cin >> val;
        switch (val)
        {
        case 0:
        {
            Cacher.container_display();
            cout << endl;
            break;
        }
        case 1:
        {
            cin >> address;
            if (Cacher.loader(address))
                cout << "Hit" << endl;
            else
                cout << "Miss" << endl;
            break;
        }
        case 2:
        {
            cin >> address;
            if (Cacher.storer(address))
                cout << "Hit" << endl;
            else
                cout << "Miss" << endl;
            break;
        }
        case 3:
        {
            Cacher.refresh_dirty();
        }
        case 4:
        {
            Cacher.container_init();
        }
        default:
        {
            flag--;
        }
        }
    }
    cout << "Simulation Terminated!" << endl;
}