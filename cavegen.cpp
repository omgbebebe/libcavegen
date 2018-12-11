#include "cavegen.hpp"
#include <queue>
#include <set>
#include <iostream>
#include "SimplexNoise.h"
#include <chrono>

using namespace std;

inline int xy2ndx (Point2d p, Point2d offset, int width)
{
  return (p.x-offset.x) + (p.y-offset.y)*width;
}

using namespace std::chrono;
vector<Chamber> Cavegen::get_chambers_in(BBox rect)
{
  vector<Chamber> chs;
  microseconds t1 = duration_cast< microseconds > (system_clock::now().time_since_epoch());
  vector<int> r = get_noise_rect(rect);
  microseconds t2 = duration_cast< microseconds > (system_clock::now().time_since_epoch());
  cout << "get_noise_rect time: " << (t2-t1).count() << " us" << endl;
  int fill_from = 255;
  int fill_to = 254;

  t1 = duration_cast< microseconds > (system_clock::now().time_since_epoch());
  for (unsigned int y = 0; y <= rect.height; y++){
    for (unsigned int x = 0; x <= rect.width; x++){
      if (r[xy2ndx(Point2d(x,y), Point2d(0,0), rect.width)] == fill_from){
	Chamber ch = flood_fill(Point2d(x,y)+rect.p0, rect, fill_to, &r);
	chs.push_back(ch);
      }
    }
  }
  t2 = duration_cast< microseconds > (system_clock::now().time_since_epoch());
  cout << "flood_fill loop time: " << (t2-t1).count() << " us" << endl;
  return chs;
}

Chamber Cavegen::flood_fill(Point2d pstart, BBox area, int fill_to, vector<int>* area_data)
{
  Chamber ch;
  int fill_from = area_data->at(xy2ndx(pstart, area.p0, area.width));

  set<Point2d> queued;
  queue<Point2d> q;
  q.push(pstart);

  while(!q.empty()){
    Point2d p = q.front();
    q.pop();
    if (area.contain(p)){
      area_data->at(xy2ndx(p, Point2d(area.p0), area.width)) = fill_to;
    }

    auto neighbors =
      { Point2d(p.x+1, p.y),
	Point2d(p.x-1, p.y),
	Point2d(p.x, p.y+1),
	Point2d(p.x, p.y-1),

	Point2d(p.x+1, p.y+1),
	Point2d(p.x+1, p.y-1),
	Point2d(p.x-1, p.y+1),
	Point2d(p.x-1, p.y-1)
      };

    for (Point2d n : neighbors){
      int noise = noise2d(n.x, n.y);
      if (noise == fill_from && (queued.count(n) == 0)){
	queued.insert(n);
	q.push(n);
	ch.push_point(n);
      }
    }
  }
  return ch;
}

vector<int> Cavegen::get_noise_rect(BBox r)
{
  vector<int> v;
  for (int y = r.p0.y; y < r.p1.y; y++){
    for (int x = r.p0.x; x < r.p1.x; x++){
      v.push_back(noise2d(x, y));
    }
  }
  return v;
}

int Cavegen::noise2d(int x, int y)
{
  return 255 * ((1.0f + noise2dF(x*scaleX,y*scaleY)) / 2.0f);
}

float Cavegen::noise2dF(float x, float y)
{
  return _noise_filter(sn->fractal(size_t(octaves), x, y));
}

float Cavegen::_noise_filter(float n)
{
   if (n < (-0.3))
	return (1.0);
    if (n > (0.3))
	return 1.0;
    return -1.0;
}

Cavegen::Cavegen()
{
  scaleX = scaleY = 0.004;
  octaves = 7;
  sn = new SimplexNoise(1.0f, //frequency = 1.0f,
			1.0f, //amplitude = 1.0f,
			2.0f, //lacunarity = 2.0f,
			0.5f);//persistence = 0.5f);
}

Cavegen::~Cavegen()
{
  if (sn)
    delete sn;
}
