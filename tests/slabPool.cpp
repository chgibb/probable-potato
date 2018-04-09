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
    int iteration = 0;
    pool.forEach([&](PBP::PooledObject<int>&obj,bool&abort) -> bool {
        iteration++;
        REQUIRE(obj.live == true);
        if(iteration == 1)
        {
            REQUIRE(obj.obj == 1);
        }
        else if(iteration == 2)
        {
            REQUIRE(obj.obj == 2);
        }
        return false;
    });
    REQUIRE(iteration == 2);
    
    iteration = 0;

    pool.add(3);
    pool.add(4);
    pool.add(5);

    //likewise when adding 3three more
    pool.forEach([&](PBP::PooledObject<int>&obj,bool&abort) -> bool {
        iteration++;
        REQUIRE(obj.live == true);
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
        return false;
    });
    REQUIRE(iteration == 5);

}

TEST_CASE("should delete and maintain ordering","") {
    REQUIRE(pool.cache.size() == 5);

    int iteration = 0;
    pool.forEach([&](PBP::PooledObject<int>&obj,bool&abort) -> bool {
        iteration++;
        REQUIRE(obj.live == true);
        if(iteration == 3)
        {   
            //abort iteration early
            abort = true;
            //mark the current object as dead
            return true;
        }
        return false;
    });
    REQUIRE(iteration == 3);

    iteration = 0;
    //everything after 3 should appear shifted down
    pool.forEach([&](PBP::PooledObject<int>&obj,bool&abort) -> bool {
        iteration++;
        REQUIRE(obj.live == true);
        if(iteration == 1)
        {
            REQUIRE(obj.obj == 1);
        }
        if(iteration == 2)
        {
            REQUIRE(obj.obj == 2);
        }
        if(iteration == 3)
        {
            REQUIRE(obj.obj == 4);
        }
        if(iteration == 4)
        {
            REQUIRE(obj.obj == 5);
        }
        return false;
    });
    REQUIRE(iteration == 4);
}

TEST_CASE("should insert and fill hole","") {
    pool.add(6);
    int iteration = 0;
    pool.forEach([&](PBP::PooledObject<int>&obj,bool&abort) -> bool {
        iteration++;
        REQUIRE(obj.live == true);
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
            REQUIRE(obj.obj == 6);
        }
        else if(iteration == 4)
        {
            REQUIRE(obj.obj == 4);
        }
        else if(iteration == 5)
        {
            REQUIRE(obj.obj == 5);
        }
        return false;
    });
    REQUIRE(iteration == 5);
}

int main(int argc,char*argv[])
{
    int res = Catch::Session().run(argc,argv);

    return res;
}