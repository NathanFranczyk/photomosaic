/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <tgmath.h>
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if(first[curDim] == second[curDim]){
	return first < second;
	}
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int curbestdist = 0;
    int potdist = 0;
    for(int i = 0; i  < Dim;i++){
	curbestdist = curbestdist + pow((target[i] - currentBest[i]),2);
	potdist = potdist + pow((target[i] - potential[i]),2);
	}
    if(potdist == curbestdist){
		    return potential < currentBest;
	}
    else{
	return potdist<curbestdist;
	}

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
  points = newPoints;
  KDTreehelper(0, 0, newPoints.size()-1, 0);

}
template<int Dim>
void KDTree<Dim>::KDTreehelper(int target, int left, int right, int curdim){

    if(left >= right){
      return;
    }
    if(right <= left){
      return;
    }
    int median = floor((left+ right)/2); //get median index;
    int dim = Dim;
    Point<Dim> medianroot = select(left, right, median, curdim);
    points[median] = medianroot;
    KDTreehelper(median-1, left, median-1, (curdim + 1) % dim);
    //^^recursively call for the left half of the points
    KDTreehelper(median+1, median+1, right, (curdim + 1) % dim );
    //^^ recursively call on the right half of the vector

   /*
  for(int i = 0; i < numpoints; i ++){ //constructs the temp vector
    if( i == median){
      finalpoints[i] = medianroot;
    }
    else{
      Point<Dim> defaultpoint;
      finalpoints[i] = defaultpoint;
    }
  }
  for(int i = 0; i < median, i ++){

  }
  */
}

template <int Dim>
int KDTree<Dim>::partition( int left,int right,int pivotindex, int curdim){
  Point<Dim> pivotval = points[pivotindex];
  Point<Dim> temp = points[pivotindex];
  points[pivotindex] = points[right];
  points[right] = temp;
  int storeindex = left;

  for( int i = left ; i < right; i ++){
    if( smallerDimVal(points[i] , pivotval, curdim) ){

      Point<Dim> temp = points[storeindex];
      points[storeindex] = points[i];
      points[i] = temp;
      storeindex ++;
    }
  }

  Point<Dim> temp2 = points[right];
  points[right] = points[storeindex]; //swap points back
  points[storeindex] = temp2;
  //points[left] = points[storeindex]
  return storeindex;
}

template<int Dim>
Point<Dim> KDTree<Dim>::select(int left, int right,int k, int curdim){
  /*
  if(pivotindex -1 == right){//base case
    return;
  }
  if(!(smallerDimVal(newPoints[pivotindex],right,curdim))){
    //right value is smaller than current index;
    Point<Dim> temp = newPoints[pivotindex];
    newPoints[pivotindex] = newPoints[right];
    newPoints[right] = temp;
  }
  int newdim = (pivotindex + 1) % 3; // dimension to be used in next recusive call
  */


    if(left == right)
      return points[left];

    int pivotindex = left +1;
    //CINDAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa
    //AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHh
    //HaLP PLES
    //INB4 a ta reads this instead of Cinda

    //pivotindex = floor(left+right/2;
    pivotindex = partition(left, right, pivotindex, curdim);
    if( k == pivotindex){
      return points[k];
    }
    else if( k <  pivotindex){
      return select(left, pivotindex -1, k, curdim);
    }
    else{
      return select(pivotindex + 1, right, k, curdim);
    }

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& startpoint) const
{
    /**
     * @todo Implement this function!
     */
    bool test = true;
    Point<Dim> best;
    int radius = 0;
    neighborhelp(startpoint, best, 0, 0, (points.size()-1),  radius, test);
    return best;

}

template <int Dim>
int KDTree<Dim>::finddistance(Point<Dim> end, Point<Dim> start) const
{
    int retval = 0;
    for (int i = 0; i < Dim; i++) //iterate through all the dimensions and add them
    {
        retval = retval +  ((end[i] - start[i]) * (end[i] - start[i]));
    }
    return retval;
}

template <int Dim>
void KDTree<Dim>::neighborhelp(const Point<Dim>& startpoint, Point<Dim>& closest, int curdim, int size, int b, int& radius, bool& test) const
{
    if (size > b-1) //size of neigbor is bigger than the
    {
        if (test)
        {
            test = false;
            closest = points[size]; //find the point at size that is in the vector of points
            radius = finddistance(startpoint, closest);//find the distance

        }
        else if (shouldReplace(startpoint, closest, points[size])) //if distance closer, replace
        {
            closest = points[size];
            radius = finddistance(startpoint, points[size]); //update radius and closest
        }
        return;
    }
    //CINDA THIS IS SO HARDDDDDDDDDDDDDDDDDDDd
    //AHHHHHHHHFHFHHFHF
    //How are y'all tas and profs so smart
    int k = (size+b)/2; //check if halfway point is smaller than current value
    bool works = true;
    if (smallerDimVal(startpoint, points[k], curdim))
        {
          neighborhelp(startpoint, closest, (curdim+1)%Dim, size, k-1, radius, test);
        }
    else//check next dimension
    {
        neighborhelp(startpoint, closest, (curdim+1)%Dim, k+1, b, radius, test);
        works = false;
    }

    if (shouldReplace(startpoint, closest, points[k]))
    {
        closest = points[k];
        radius = finddistance(startpoint, points[k]);
    }

    if((startpoint[curdim] - points[k][curdim]) * (startpoint[curdim] - points[k][curdim]) <= radius)
    {
        if (works)
            neighborhelp(startpoint, closest, (curdim+1)%Dim, k+1, b, radius, test);
        else
            neighborhelp(startpoint, closest, (curdim+1)%Dim, size, k-1, radius, test);
    }
}
