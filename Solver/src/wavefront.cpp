#include "wavefront.hpp"

Wavefront::Wavefront(Map & map){
  LocalMap = *map.Clone();

  for(int y = 0; y < LocalMap.rows; y++ ){
    for(int x = 0; x < LocalMap.cols; x++){
      if(LocalMap[ Point(x,y) ] == '.' || LocalMap[ Point(x,y) ] == 'M' || LocalMap[ Point(x,y) ] == 'G' ){
        LocalMap.setValue(Point(x,y), 100);
      }
    }
  }
}

void Wavefront::generate_wavefront(Point StartWavefront){
  std::queue<Point> brushfire;

  brushfire.push( StartWavefront );

  while( !brushfire.empty() ) {
        if(!brushfire.empty()){
            Point CurrentBrushfire = brushfire.front();
            brushfire.pop();
            //value1 = img->getPixel(CurrentBrushfire.x, CurrentBrushfire.y) + 1;
            int value = LocalMap[CurrentBrushfire] + 1;
            std::cout << "value: " << value << std::endl;

            //check and set all adjacent pixels (4 point connectivity)
            for(signed int x_add = -1; x_add < 1; x_add++) {
                for(signed int y_add = -1; y_add < 1; y_add++) {
                    if(x_add == y_add){
                      continue;
                    }

                    //check for out of bounds, skip if it is
                    if(!LocalMap.inMap( Point(CurrentBrushfire.x + x_add, CurrentBrushfire.y + y_add ))) {
                        continue;
                    }

                    //unsigned int check_value = img->getPixel(CurrentBrushfire.x + x_add, CurrentBrushfire.y + y_add);
                    unsigned int CheckValue = LocalMap[ Point(CurrentBrushfire.x + x_add, CurrentBrushfire.y + y_add)];

                    std::cout << "checkValue: " << CheckValue << std::endl;
                    if(CheckValue > value) {
                        Point nextFire(CurrentBrushfire.x + x_add, CurrentBrushfire.y + y_add);
                        brushfire.push(nextFire);

                        //img->setPixel(CurrentBrushfire.x + x_add, CurrentBrushfire.y + y_add, value1);
                        LocalMap.setValue( Point(CurrentBrushfire.x + x_add, CurrentBrushfire.y + y_add), value );
                    }
                }
            }
        }
  }
}
