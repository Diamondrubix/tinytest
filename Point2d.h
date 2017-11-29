// CS 211 lab 11
//
//  Written by Pat troy

#include <cstdio>
#include <cstdarg>
#include <cmath>

class Point2d
{
  // data members are almost ALWAYS private
  private:
    // the X and Y coordinates for the point
    int x;
    int y;

    // a way to handle debug mode
    bool debug;

  public:
    void dprintf(char *format, ...) const ;
    void setDebug (bool b) ;


   // use of class constructors to initialize the variables
   Point2d (int px, int py);
   Point2d ( ) ;

   void setX (int px);
   int getX() const ;
   void setY (int py);
   int getY() const ;
   void setXY (int px, int py);
   double distanceFrom (Point2d pt) const ;
   char*  toStr(char* buf) const ;
   int getQuadrant();
};

