#include "doctest.h"
#include "cavegen.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <utility>

class MyCavegen : public Cavegen {
public:
  unsigned int width, height;
  explicit MyCavegen(std::string map_name) : Cavegen() {
    std::ifstream f;
    std::string l;
    width = 0;
    height = 0;

    f.open(map_name);
    if (f.is_open()){
      INFO("reading file...");
      while (std::getline(f,l)){
	if (l.size() > width)
	  width = l.size();
	for (char c : l){
	  noise_map.push_back(c);
	}
	height++;
      }
      f.close();
    } else {
      FAIL_CHECK("failed to open " << map_name << " file");
    }
    INFO("width: " << width << ", height: " << height);
  };

protected:
  int noise2d(int x, int y){
    if (x >= 0 && x < (int)width && y >= 0 && y < (int)height && noise_map[x + y*width] == 'x'){
      return 255;
    }
    return 0;
  };

  std::vector<int> get_noise_rect(BBox rect){
    std::vector<int> v;
    for (int y = rect.p0.y; y < rect.p1.y; y++){
      for (int x = rect.p0.x; x < rect.p1.x; x++){
	v.push_back(noise2d(x,y));
      }
    }
    return v;
  };
private:
  std::vector<char> noise_map;
};

TEST_CASE("chambers detection"){
  auto cg = new MyCavegen("test_data/caves.txt");
  int w = cg->width;
  int h = cg->height;
  std::map<BBox, int> test_boxes =
    {
     {BBox(0,0,w,h), 3},
     {BBox(0,8,w,h), 2},
     {BBox(0,0,3,3), 0},
     {BBox(0,0,w-10,h), 2}
    };

  for(auto kv = test_boxes.begin(); kv != test_boxes.end(); ++kv){
    BBox bb = kv->first;
    int expect = kv->second;
    std::vector<Chamber> chambers = cg->get_chambers_in(bb);

    int count = chambers.size();
    INFO("bbox: " << bb << " expect " << expect << " caves but actual is " << count);
    CHECK(count ==  expect);
  }
}
