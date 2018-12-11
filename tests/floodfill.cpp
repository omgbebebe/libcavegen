#include "doctest.h"
#include "cavegen.hpp"

class MyCavegen : protected Cavegen {
protected:
  int noise2d(float x, float y);
  std::vector<int> get_noise_rect(BBox rect);
};

SCENARIO("check chambers detection") {
    GIVEN("derive a CaveGen class with custom noise and noise_rec function") {
	Cavegen* cg = new MyCavegen();


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
