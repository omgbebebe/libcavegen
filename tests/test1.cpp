#include "doctest.h"
#include <unistd.h>
#include "cavegen.hpp"

float noise2d(float x, float y){
    return 1.123f;
}

SCENARIO("check for noise2d function") {
    GIVEN("a new CaveGen instance") {
        Cavegen* cg = new Cavegen();

        WHEN("call get_noise_at as an object method") {

            THEN("it returns some value between 0 and 1") {
//                CHECK(cpp_noise <=  1.0f);
            }
        }

//         WHEN("call get_noise_at as a C func") {
//             float c_noise = get_noise_at(p, 0,0);
// 
//             THEN("it returns some value between 0 and 1") {
//                 CHECK(c_noise >= -1.0f);
//                 CHECK(c_noise <=  1.0f);
//             }
//         }

    }
} 
