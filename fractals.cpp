// Nicholas Marcopoli
// Fundamentals of Computing Lab - Section 01
// 12-7-2017
// Recursion and Fractals

#include "gfx.h"
#include <cmath>
#include <unistd.h>
#include <iostream>

using namespace std;

void sierpinski(int, int, int, int, int, int);
void shrink_square(int, int, int);
void spiral_square(double, double);
void circular_lace(int, int, int);
void snowflake(int, int, int);
void tree(int, int, int, double);
void fern(int, int, int, double, int);
void spiral_spiral(int, int, double, double);
void square(int, int, int);
void triangle(int, int, int, int, int, int);

int main(){
    
    // Menu window size
    const int width = 700, height = 700;
    
    gfx_open(width, height, "Fractals!");
    
    bool exit = false;
    
    while(!exit){
		// Set up initial menu
		gfx_clear();
		gfx_color(0,255,100);
		gfx_text(0,10,"Welcome to Nick Marcopoli's fractal program!");
		gfx_text(0,20,"Here are the instructions:");
		gfx_text(0,30,"Press 1 for the Sierpinski Triangle");
		gfx_text(0,40,"Press 2 for Shrinking Squares");
		gfx_text(0,50,"Press 3 for Spiral Squares");
		gfx_text(0,60,"Press 4 for Circular Lace");
		gfx_text(0,70,"Press 5 for Snowflake");
		gfx_text(0,80,"Press 6 for Tree");
		gfx_text(0,90,"Press 7 for Fern");
		gfx_text(0,100,"Press 8 for Spiral of Spirals");
		gfx_text(0,110,"Press 'q' to quit!");
		gfx_flush();
		
		char input = gfx_wait();
		gfx_clear();
		gfx_text(0,10,"Press 'x' to return to the menu.");
		
		switch(input){
			case '1':
				sierpinski(50, 50, width/2, 600, 650, 50);
				while(gfx_wait() != 'x'); // wait for user to type x to exit
				break;
			case '2':
				shrink_square(width/2,height/2,350);
				while(gfx_wait() != 'x'); // wait for user to type x to exit
				break;
			case '3':
				spiral_square(width/2,0);
				while(gfx_wait() != 'x'); // wait for user to type x to exit
				break;
			case '4':
				circular_lace(width/2,height/2,200);
				while(gfx_wait() != 'x'); // wait for user to type x to exit
				break;
			case '5':
				snowflake(width/2,height/2,250);
				while(gfx_wait() != 'x'); // wait for user to type x to exit
				break;
			case '6':
				tree(width/2,height-10,250,-M_PI_2);
				while(gfx_wait() != 'x'); // wait for user to type x to exit
				break;
			case '7':
				fern(width/2,height-10,100,-M_PI_2,1);
				while(gfx_wait() != 'x'); // wait for user to type x to exit
				break;
			case '8':
				spiral_spiral(width/2,height/2,350,0);
				while(gfx_wait() != 'x'); // wait for user to type x to exit
				break;
			case 'q':
				exit = true;
				break;
			default:
				break;
		}
		
	}
    
    return 0;
    
}

// Function that creates the Sierpinski Triangle
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 ){
    
    // Base case. 
    if( abs(x2-x1) < 4 ) return;

    // Draw the triangle
    triangle( x1, y1, x2, y2, x3, y3 );

    // Recursive calls
    sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
    sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
    sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
    
}

// Creates the Shrinking Square fractal
void shrink_square(int x, int y, int side){
	
	// Base Case
	if(side < 5) return;
	
	// Draw Square
	side *= (4./9); // multiply side by 4/9 for use in fractals
	square(x, y, side);
	
	// Recursive Calls, at each corner
	shrink_square(x-side,y-side,side);
	shrink_square(x+side,y-side,side);
	shrink_square(x-side,y+side,side);
	shrink_square(x+side,y+side,side);
	
}

// Creates the Spiral Squares fractal
void spiral_square(double radius, double theta){
	
	// Base Case
	if(radius < 2) return;
	
	// Draw Square
	// Polar coordinates - start at large r and 0 rads then decrease
	// convert polar to cartesian, then draw a square at that point
	double x = 350 + radius * cos(theta), y = 350 + radius * sin(theta);
	int side = radius / 10;
	
	square(x,y,side);
	
	radius -= 10, 
	theta += M_PI / 6;
	
	// Recursive Calls
	spiral_square(radius,theta);
	
}

// Creates the circular lace fractal
void circular_lace(int x, int y, int radius){
	
	// Base Case
	if(radius < 1) return;
	
	// Draw Circle
	gfx_circle(x, y, radius);
	
	// Recursive Calls, 6 more circles
	// Draw six equally spaced circles using polar coordinates
	double theta = 0;
	int x_arr[6], y_arr[6];
	for(int i = 0; i < 6; i++){
		x_arr[i] = x + (radius * cos(theta));
		y_arr[i] = y + (radius * sin(theta));
		theta += M_PI / 3;
	}
	// adjust radius for recursion
	radius /= 3;
	for(int i = 0; i < 6; i++){
		circular_lace(x_arr[i],y_arr[i],radius);
	}
	
}

// Creates the snowflake fractal
void snowflake(int x, int y, int radius){
	
	// Base Case
	if(radius < 1) return;
	
	// Draw 5 Snowflake lines
	int x_arr[5], y_arr[5];
	double theta = M_PI_2;
	for(int i = 0; i < 5; i++){
		x_arr[i] = x + (radius * cos(theta));
		y_arr[i] = y + (radius * sin(theta));
		gfx_line(x,y,x_arr[i],y_arr[i]);
		
		theta += (360/5) * (M_PI / 180); // increase by 1/5 of a circle
	}
	
	// 5 Recursive calls
	radius /= 3;
	for(int i = 0; i < 5; i++){
		snowflake(x_arr[i],y_arr[i],radius);
	}
}

// Creates the tree fractal
void tree(int x, int y, int length, double theta){
	
	// Base Case
	if(length < 1) return;
	
	// Draw tree branches
	int x1 = x + (length * cos(theta)), y1 = y + (length * sin(theta));
	gfx_line(x,y,x1,y1);
	

	// Recursive Calls
	length /= 1.5;
	tree(x1,y1,length,theta-(M_PI / 5));
	tree(x1,y1,length,theta+(M_PI / 5));
	
}

// Creates the fern fractal
// Numsegs counts the number of fern segments on each branch,
// since there should only be 4 fern segments when it branches off
void fern(int x, int y, int length, double theta, int numsegs){
	
	// Base Case
	if(numsegs > 4 || length < 2) return;
	
	// Draw Fern lines
	int x1 = x + (length * cos(theta)), y1 = y + (length * sin(theta));
	gfx_line(x,y,x1,y1);
	
	// 3 Recursive Calls
	fern(x1,y1,length,theta,++numsegs); // straight up
	fern(x1,y1,length/2.5,theta+(M_PI / 5),1); // to the right
	fern(x1,y1,length/2.5,theta-(M_PI / 5),1); // to the left
	
}

void spiral_spiral(int x, int y, double radius, double theta){
	
	// Base case
	if(radius < 1) return;
	
	// Draw Spiral Point
	int x1 = x + radius * cos(theta), y1 = y + radius * sin(theta);
	gfx_point(x1,y1);
	
	// Recursive Calls
	spiral_spiral(x1,y1,radius/3,theta);
	spiral_spiral(x,y,radius/1.1,theta+(M_PI / 5));
	
	
}

void square(int x, int y, int side){
	
	// create points
	int x1 = x - side, y1 = y - side; // top left
	int x2 = x + side, y2 = y - side; // top right
	int x3 = x - side, y3 = y + side; // bottom left
	int x4 = x + side, y4 = y + side; // bottom right
	// line between points
	gfx_line(x1,y1,x2,y2);
	gfx_line(x2,y2,x4,y4);
	gfx_line(x1,y1,x3,y3);
	gfx_line(x3,y3,x4,y4);
	
}

// Creates a triangle from three points
void triangle(int x1,int y1,int x2,int y2,int x3,int y3){
    
    gfx_line(x1,y1,x2,y2);
    gfx_line(x2,y2,x3,y3);
    gfx_line(x3,y3,x1,y1);
    gfx_flush();
    
}
