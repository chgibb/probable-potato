#define CATCH_CONFIG_RUNNER
#include "../catch2/single_include/catch.hpp"

#include <allegro5/allegro.h>

#include "../src/PBP/slabPool.hpp"

PBP::SlabPool<int> pool;

TEST_CASE("Should allocate properly","") {
    //first allocation should be back of storage
    pool.add(1);
    REQUIRE(pool.cache.back().obj == 1);

    pool.add(2);

    //first two allocations should be accessed on first two iterations
    int iteration = 1;
    pool.forEach([&](PBP::PooledObject<int>&obj,bool&abort) -> bool {
        if(iteration == 1)
        {
            REQUIRE(obj.obj == 1);
        }
        else if(iteration == 2)
        {
            REQUIRE(obj.obj == 2);
        }
        iteration++;
        return false;
    });
    
    iteration = 1;

    pool.add(3);
    pool.add(4);
    pool.add(5);

    //likewise when adding 3three more
    pool.forEach([&](PBP::PooledObject<int>&obj,bool&abort) -> bool {
        if(iteration == 1)
        {
            REQUIRE(obj.obj == 1);
        }
        else if(iteration == 2)
        {
            REQUIRE(obj.obj == 2);
        }
        else if(iteration == 3)
        {
            REQUIRE(obj.obj == 3);
        }
        else if(iteration == 4)
        {
            REQUIRE(obj.obj == 4);
        }
        else if(iteration == 5)
        {
            REQUIRE(obj.obj == 5);
        }
        iteration++;
        return false;
    });

}

int main(int argc,char*argv[])
{
    int res = Catch::Session().run(argc,argv);

    return res;
}