// Alexander Bauer
// CS 130B Programming Assignment 1
// Last Edited: 4/24/2017
// To run program, enter directory with main.cpp
// then enter the following commands:
// make all
// ./prog1 < someInput.txt

#include <string>   /* std::string */
#include <cmath>  /* std::abs */
#include <limits> /* std::numeric_limits */
#include <math.h> /* sqrt */
#include <vector> /* std::vector */
#include <cstdlib> /* qsort */
#include <iostream> /* std::cout, std::cin */

int numComparisons = 0; //Global variable for counting comparisons

// Point struct to make things easier
struct Point{

    double x;
    double y;

    //CONSTRUCTOR
    Point( double xVal = 0, double yVal = 0 )
    : x{ xVal }, y{ yVal } { }

};

//COMPARISON FUNCTIONS
//These two functions are used to sort points. Used in conjunction
//with std::qsort
int compareX( const void* a, const void* b ){
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    double val = p1->x - p2->x;
        if ( val < 0 )
            return -1;
        if ( val > 0 )
            return 1;
        return 0;
}

int compareY( const void* a, const void* b ){
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    double val = p1->y - p2->y;
    if ( val < 0 )
        return -1;
    if ( val > 0 )
        return 1;
    return 0;
}


//DISTANCE FUNCTION
double distanceBetween( Point p1, Point p2 ){
    numComparisons++; // Update number of comparisons
    return sqrt( ( p1.x - p2.x ) * ( p1.x - p2.x )
                +( p1.y - p2.y ) * ( p1.y - p2.y ) );
}

Point* bruteForce( Point P[], int numPoints ){
    double minDistance = std::numeric_limits<double>::max();
    Point* closestPair = new Point[2];
    for( int i = 0; i < numPoints; i++ ){
        for ( int j = i+1; j < numPoints; j++ ){
            double currentDistance = distanceBetween( P[i], P[j] );
            if ( currentDistance < minDistance){
                minDistance = currentDistance;
                closestPair[0].x = P[i].x;
                closestPair[0].y = P[i].y;
                closestPair[1].x = P[j].x;
                closestPair[1].y = P[j].y;
            }
        }
    }
    return closestPair;
}

// Helper function that finds the closest pair in the strip of given
// size. Points are sorted according to there y coordinates
Point* stripClosest( Point strip[], int numPoints, double d){
    double minDistance = d;
    Point* closestPair = new Point[2];
    // sort by y coordinate
    qsort( strip, numPoints, sizeof(Point), compareY );

    // Search for pair closer than distance d
    for( int i = 0; i < numPoints; i++ ){
        for ( int j = i + 1; j < numPoints && ( strip[j].y - strip[i].y ) < d; j++){
            double currentDistance = distanceBetween( strip[i], strip[j] );
            if ( currentDistance < minDistance){
                minDistance = currentDistance;
                closestPair[0].x = strip[i].x;
                closestPair[0].y = strip[i].y;
                closestPair[1].x = strip[j].x;
                closestPair[1].y = strip[j].y;
            }
        }
    }
    return closestPair;
}

Point* divideConquer( Point* P, int numPoints ){
    // P has already been sorted according to x values
    // If there are 2 or 3 points, use the bruteForce algorithm since
    // it has become trivial with this many points;
    if ( numPoints <= 3 )
        return bruteForce( P, numPoints );

    // Decide on a middle point
    int mid = numPoints / 2;

    // Calculate clsoest pair left of midPoint.x dl
    Point* dl = divideConquer( P, mid );

    // Calculate closest pair right of midPoint.x dl
    Point* dr = divideConquer( P + mid, numPoints - mid );

    // Find smaller between dl & dr, d
    Point* d = new Point[2];
    if( distanceBetween( dl[0], dl[1]) < distanceBetween( dr[0], dr[1] )){
        d[0].x = dl[0].x;
        d[0].y = dl[0].y;
        d[1].x = dl[1].x;
        d[1].y = dl[1].y;
    }
    else{
        d[0].x = dr[0].x;
        d[0].y = dr[0].y;
        d[1].x = dr[1].x;
        d[1].y = dr[1].y;
    }
    // Build strip[] that contains points closer than
    // distanceBetween(d[0], d[1]) to the vertical line x=P[mid].x
    std::vector<Point> strip;
    double smallestDistance = distanceBetween( d[0], d[1] );
    for( int i = 0; i < numPoints; i++){
        numComparisons++; //I added this update because I think you are
                            //technically comparing everytime, but I was making
                            //it easier to code
        if ( std::abs( P[i].x - P[mid].x ) < smallestDistance ){
            strip.push_back( P[i] );
        }
    }

    // Find the closest points in the strip
    Point* s = stripClosest( &strip[0], strip.size(), smallestDistance );
    if( distanceBetween( s[0], s[1] ) < .000001 ){
        return d;

    }
    else{
        return s;

    }

}

int main() {
    int numPoints = 0;
    double x;
    double y;
    std::cin >> numPoints;
    std::vector<Point> P;
    for( int i = 0; i < numPoints; i++){
        std::cin >> x;
        std::cin >> y;
        P.push_back( Point( x, y ) );
    }
    // Sort the array according to x coordinates
    std::qsort( &P[0], numPoints, sizeof(Point), compareX );

    Point* closestPointsDC = divideConquer(&P[0], numPoints);
    int divideConquerComparisons = numComparisons; //Record total Divide conquer
    numComparisons = 0; // Reset for brute force

    Point* closestPointsBF = bruteForce(&P[0], numPoints);
    int bruteForceComparisons = numComparisons; //Record total brute force

    //Output Results
    std::cout << closestPointsBF[0].x << " " << closestPointsBF[0].y
              << " " << closestPointsBF[1].x << " " << closestPointsBF[1].y
              << std::endl << bruteForceComparisons << std::endl;

    std::cout << closestPointsDC[0].x << " " << closestPointsDC[0].y
              << " " << closestPointsDC[1].x << " " << closestPointsDC[1].y
              << std::endl << divideConquerComparisons << std::endl;

    return 0;
}
