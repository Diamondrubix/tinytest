//  Code for CS 211 Lab 11
//
//  Written by Pat Troy
//
/**  This code will represent line segments in a 2-D space.
  * 
  * This code will use the Point2d.cpp code
  *    Note that the Point2d class uses integer values for the X and Y corrdinates
  * 
  * The code is attempting to show how one class might use/contain another class
  *   This is often referred to as "aggregation", "composition"
  *   or having a "HAS-A" relationship.
  * 
  * So the Segment class "has a" member of the Point2D class (actually it has 2).
  */

#include "Point2d.h"

const double PI = 3.14159265359;

class Segment
{
 private:
   Point2d endp1;
   Point2d endp2;

 public:
   Segment();
   Segment ( Point2d p1, Point2d p2 );
   void changeEndPoint1 ( Point2d p);
   void changeEndPoint2 ( Point2d p);
   double length();
   double slope() const ;
   char* toStr (char* buf);
};


  Segment::Segment()
  {
   printf ("In constructor Segment()\n");
   endp1.setXY( 0, 0 );
   endp2.setXY( 0, 0 );
  }

  Segment::Segment ( Point2d p1, Point2d p2 )
  {
   printf ("In constructor Segment(Point2d, Point2d)\n");
   endp1 = p1;
   endp2 = p2;
  }

  void Segment::changeEndPoint1 ( Point2d p)
  {
   endp1 = p;
  }

  void Segment::changeEndPoint2 ( Point2d p)
  {
   endp2 = p;
  }


  double Segment::length()
  {
    return 0.0;
  }

  double Segment::slope() const
  { 
    return INFINITY;
  }

  // note this is unsafe since length of buf is never verified
  char* Segment::toStr (char* buf)
  {
    char tbuf1[300], tbuf2[300];
    sprintf ( buf, "End Point 1: %s, End Point 2: %s", 
               endp1.toStr(tbuf1), endp2.toStr(tbuf2) );

    return buf;
   }


double calcAngleOfIntersection ( Segment s1, Segment s2)
{
 double m1 = s1.slope();
 double m2 = s2.slope();

 // note atan() return radians, so convert to degrees
 //  The angle returned is from positive x axis
 double angle1 = atan( m1 ) * 180.0 / PI ;
 double angle2 = atan( m2 ) * 180.0 / PI ;

 // note use abs( ) if you only want positive angle values
 return angle1 - angle2;
}

int main (int argc, char** argv)
{
 char buffer[100];

 Point2d p1 (3, 5);
 Point2d p2 (-4, 2);
 
 printf ("\nCreating Segments\n"); 
 Segment seg1 ( p1, p2);
 Segment seg2;
 printf ("Segment1: %s\n", seg1.toStr(buffer) );
 printf ("Segment2: %s\n", seg2.toStr(buffer) );

 printf ("\nChanging Segments\n"); 
 p2.setXY ( 7, -4 );
 printf ("Segment1: %s\n", seg1.toStr(buffer) );

 seg1.changeEndPoint2 ( p2 );
 printf ("Segment1: %s\n", seg1.toStr(buffer) );
 seg1.changeEndPoint2 ( Point2d( -4, 12) );
 printf ("Segment1: %s\n", seg1.toStr(buffer) );

 printf ("\nInformation On Segments\n"); 
 printf ("Length of Segement1: %f\n", seg1.length() );
 printf ("Slope of Segement1: %f\n", seg1.slope() );
 printf ("Slope of Segement2: %f\n", seg2.slope() );

 // calling calcAngleOfIntersection( ) as a function
 double angle;
 angle = calcAngleOfIntersection ( seg1, seg2 );
 // calling calcAngleOfIntersection( ) as a method
 // angle =  seg1.calcAngleOfIntersection ( seg2 );
 printf ("Angle of Intersection: %f\n", angle );

 printf ("Sizeof Segment: %d\n", sizeof (Segment) );
 printf ("Sizeof Segment pointer: %d\n", sizeof(Segment*) );
 return 1;
}

