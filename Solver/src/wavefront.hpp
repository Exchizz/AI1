#include "map.hpp"
#include <queue>

class Wavefront{
public:
  Wavefront(Map& map);
  void generate_wavefront(Point StartWavefront);
  Map LocalMap;
};
