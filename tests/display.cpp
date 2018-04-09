#define CATCH_CONFIG_RUNNER
#include "../catch2/single_include/catch.hpp"

#include <allegro5/allegro.h>

#include "../src/PBP/display.hpp"

TEST_CASE( "Should init properly","") {
    REQUIRE(PBP::init() == 0);
    REQUIRE(PBP::initDisplay(640,480) == 0);
    REQUIRE(PBP::display != NULL);
    al_rest(1.5);
    PBP::destroyDisplay();
}

int main(int argc,char*argv[])
{
    int res = Catch::Session().run(argc,argv);

    return res;
}