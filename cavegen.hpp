#ifndef CAVEGEN_H
#define CAVEGEN_H
#include <vector>
#include <cmath>
#include <ostream>

class SimplexNoise;

struct Point2d {
  int x,y;
  Point2d() : x(0), y(0) {};
  Point2d(int x, int y) : x(x), y(y) {};
  inline bool operator== (const Point2d &a) { return a.x == this->x && a.y == this->y; }
  inline Point2d operator+ (const Point2d &a) { return Point2d(a.x+this->x,a.y+this->y); }
  friend bool operator< (const Point2d &a, const Point2d &b)
  {
    return (b.x < a.x || (b.x == a.x && b.y < a.y));
  }
  friend std::ostream& operator<<(std::ostream& os, const Point2d& p){
    os << "Point2d (" << p.x << ", " << p.y << ")";
    return os;
  }
};

struct BBox {
  Point2d p0, p1;
  unsigned int width, height;
  BBox() : width(0), height(0) {}

  BBox(Point2d p0, Point2d p1)
    : p0(p0), p1(p1),
      width(abs(p1.x - p0.x)),
      height(abs(p1.y - p0.y)) {}

  BBox(Point2d p0, int w, int h)
    : p0(p0), p1(Point2d(p0.x + w, p0.y + h)),
      width(w),
      height(h) {}

  BBox(int ax, int ay, int bx, int by)
    : p0(Point2d(ax,ay)), p1(Point2d(bx,by)),
      width(abs(p1.x - p0.x)),
      height(abs(p1.y - p0.y)) {}

  bool contain(Point2d p){
    return (p.x >= p0.x && p.x < p1.x && p.y >= p0.y && p.y < p1.y);
  }

  friend bool operator< (const BBox &a, const BBox &b)
  {
    return (a.p0 < b.p0 || a.p1 < b.p1);
  }
  friend std::ostream& operator<<(std::ostream& os, const BBox& b){
    os << "bbox (" << b.p0 << ", " << b.p1 << ") | " << b.width << "," << b.height;
    return os;
  }
};

struct Chamber {
  BBox bbox;
  int area;
  std::vector<Point2d> points;
  std::vector<int> edges;

  Chamber() : area(0) {};

  void push_point(Point2d p) { points.push_back(p); }
  void push_edge_index(int i) { edges.push_back(i); }
  void calc_metrics() { area = points.size(); }
};

class Cavegen {
public:
  float scaleX, scaleY;
  int octaves;

  std::vector<Chamber> get_chambers_in(BBox rect);
  Cavegen();
  ~Cavegen();

protected:
  virtual int noise2d(int x, int y);
  virtual float noise2dF(float x, float y);
  virtual std::vector<int> get_noise_rect(BBox rect);
  virtual float _noise_filter(float n);

private:
  SimplexNoise* sn;
  Chamber flood_fill(Point2d pstart, BBox area, int fill_to, std::vector<int>* area_data);
};

#endif
