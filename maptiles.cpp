/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include <vector>
#include "maptiles.h"
#include "rgbapixel.h"
#include "png.h"
#include "kdtree.h"
#include "mosaiccanvas.h"
//#include "photomosaic.cpp"
#include "mosaiccanvas.h"
#include "rgbapixel.h"
//#include "rgbapixel.cpp"
#include "sourceimage.h"
#include "tileimage.h"
#include "point.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
     /*
     MosaicCanvas* thiscanvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns()); //create a new mosaiccanvas
     vector<Point<3>> pixels;
     for(size_t i = 0; i < theSource.getRows(), i ++){
       for(size_t j = 0 ; j < theSource.getColumns(); j ++){
          RGBAPixel sourceavg = theSource.getRegionColor(i,j);
          pixels[i*theSource.getColumns() + j][0] = sourceavg.red;
          pixels[i*theSource.getColumns() + j][1] = sourceavg.green;
          pixels[i*theSource.getColumns() + j][2] = sourceavg.blue;
       }
     }//create the point vector of pixels
     pixeltree KDTree(pixels); //make a kdtree of pixels

     for(size_t i = 0; i < theSource.getRows(), i ++){
       for(size_t j = 0 ; j < theSource.getColumns(); j ++){
          //RGBAPixel sourceavg = theSource.getRegionColor(i,j);
          Point<3> avgcolortile;
          avgcolortile[0] = theTiles[i*theSource.getColumns() + j].red;
          avgcolortile[1] = theTiles[i*theSource.getColumns() + j].green;
          avgcolortile[2] = theTiles[i*theSource.getColumns() + j].blue;
          pixeltree.findNearestNeighbor(avgcolortile);
       }
     }
     */

     MosaicCanvas* thiscanvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns()); //create a new mosaiccanvas
     vector<Point<3>> pixels;
     map<Point<3>,TileImage> pointmap;
    // for(int i = 0; i < (theSource.getRows()); i ++){
       //for(int j = 0 ; j < (theSource.getColumns()); j ++){
       for(unsigned long i = 0; i < theTiles.size(); i ++){
          RGBAPixel tileavg = theTiles[i].getAverageColor();
          //cout<<i<<endl;
          Point<3> pointtile;
          pixels.push_back(pointtile);
          //pixels[i] = pointtile;
          pixels[i][0] = tileavg.red;
          pixels[i][1] = tileavg.green;
          pixels[i][2] = tileavg.blue;
          pointmap.insert(std::make_pair(pixels[i],theTiles[i]));

     }//create the point vector of pixels

     KDTree<3> pixeltree(pixels) ; //make a kdtree of pixels

     for(int i = 0; i < (theSource.getRows()); i ++){
       for(int j = 0 ; j < (theSource.getColumns()); j ++){
          //RGBAPixel sourceavg = theSource.getRegionColor(i,j);
          Point<3> avgcolorpix;
          avgcolorpix[0] = theSource.getRegionColor(i,j).red;
          avgcolorpix[1] = theSource.getRegionColor(i,j).green;
          avgcolorpix[2] = theSource.getRegionColor(i,j).blue;
          Point<3> closest = pixeltree.findNearestNeighbor(avgcolorpix);
          //closest is the best tile
          (*thiscanvas).setTile(i,j,pointmap[closest]);
       }
     }
     return thiscanvas;

    return NULL;
}
