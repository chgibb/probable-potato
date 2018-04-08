#define CATCH_CONFIG_RUNNER
#include "../catch2/single_include/catch.hpp"

#include <allegro5/allegro.h>

#include "../src/PBP/slabPool.hpp"

TEST_CASE("Should allocate properly","") {
    PBP::SlabPool<int> pool;
    
    //first allocation should be back of storage
    pool.add(1);
    REQUIRE(pool.cache.back().obj == 1);

    pool.add(2);

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
}

int main(int argc,char*argv[])
{
    int res = Catch::Session().run(argc,argv);

    return res;
}