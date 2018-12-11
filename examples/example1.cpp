#include <iostream>
#include "cavegen.hpp"

using namespace std;

int main()
{
  auto cg = new Cavegen();
  BBox bb(Point2d(0,0),100,100);
  cout << "generate caves in " << bb << endl;
  auto chambers = cg->get_chambers_in(bb);
  cout << "chambers count: " << chambers.size() << endl;
  return 0;
}
