#include "stdafx.h"
#include "SFML/OpenGL.hpp"
#include "Terrain.h"
#include <cmath>

Terrain::Terrain(void)
{
	gridWidth=100;
	gridDepth=100;

	terrWidth=50; //size of terrain in world units
	terrDepth=50;
<<<<<<< HEAD
	vertices = NULL;
	colors = NULL;	
	
	//num squares in grid will be width*height, two triangles per square
	//3 verts per triangle
	 numVerts = gridDepth * gridWidth * 2 * 3;
}

=======
	vertices=NULL;
	colors=NULL;	
	
	//num squares in grid will be width*height, two triangles per square
	//3 verts per triangle
	 numVerts=gridDepth*gridWidth*2*3;


}


>>>>>>> 9ee06265fab3ad1f90849f39954766e5d6de13f0
Terrain::~Terrain(void)
{
	delete [] vertices;
	delete [] colors;
}

//interpolate between two values
float lerp(float start, float end, float t){
	return start+(end-start)*t;
}

<<<<<<< HEAD
void Terrain::setPoint(vector v,float x, float y, float z)
{
=======

void Terrain::setPoint(vector v,float x, float y, float z){

>>>>>>> 9ee06265fab3ad1f90849f39954766e5d6de13f0
		v[0]=x;
		v[1]=y;
		v[2]=z;
}

//helper function to calculate height of terrain at a given point in space
//you will need to modify this significantly to pull height from a map
float  Terrain::getHeight(float x, float y){

	//for the sample we will calculate height based on distance form origin
<<<<<<< HEAD
	float dist = sqrt(x * x + y * y);

	//center will be the highest point
	dist = 30 - dist;
	//put a nice curve in it
	dist *= dist;
	dist *= dist;
	//whoah, way to high, make it smaller
	dist /= 50000;
=======
	float dist=sqrt(x*x+y*y);

	//center will be the highest point
	dist=30-dist;
	//put a nice curve in it
	dist*=dist;
	dist*=dist;
	//whoah, way to high, make it smaller
	dist/=50000;
>>>>>>> 9ee06265fab3ad1f90849f39954766e5d6de13f0

	return dist;
}

void Terrain::Init(){
	
	delete [] vertices;//just in case we've called init before
	vertices=new vector[numVerts];
	delete [] colors;
	colors=new vector[numVerts];


	//interpolate along the edges to generate interior points
<<<<<<< HEAD
	for(int i = 0; i < gridWidth - 1; i++){ //iterate left to right
		for(int j = 0; j < gridDepth - 1; j++){//iterate front to back
			int sqNum = (j + i * gridDepth);
			int vertexNum = sqNum * 3 * 2; //6 vertices per square (2 tris)
			float front = lerp(-terrDepth / 2,terrDepth / 2,(float)j / gridDepth);
			float back = lerp(-terrDepth / 2,terrDepth / 2,(float)(j + 1) / gridDepth);
			float left = lerp(-terrWidth / 2,terrWidth / 2,(float)i / gridDepth);
			float right = lerp(-terrDepth / 2,terrDepth / 2,(float) (i + 1) / gridDepth);
=======
	for(int i=0;i<gridWidth-1;i++){ //iterate left to right
		for(int j=0;j<gridDepth-1;j++){//iterate front to back
			int sqNum=(j+i*gridDepth);
			int vertexNum=sqNum*3*2; //6 vertices per square (2 tris)
			float front=lerp(-terrDepth/2,terrDepth/2,(float)j/gridDepth);
			float back =lerp(-terrDepth/2,terrDepth/2,(float)(j+1)/gridDepth);
			float left=lerp(-terrWidth/2,terrWidth/2,(float)i/gridDepth);
			float right=lerp(-terrDepth/2,terrDepth/2,(float)(i+1)/gridDepth);
>>>>>>> 9ee06265fab3ad1f90849f39954766e5d6de13f0
			
			/*
			back   +-----+	looking from above, the grid is made up of regular squares
			       |tri1/|	'left & 'right' are the x cooded of the edges of the square
				   |   / |	'back' & 'front' are the y coords of the square
				   |  /  |	each square is made of two trianlges (1 & 2)
				   | /   |	
				   |/tri2|
			front  +-----+
			     left   right
<<<<<<< HEAD
			*/

			//tri1
			setPoint(colors[vertexNum], (rand()% 255) / 255.0, (rand()% 255) / 255.0, (rand()% 255) / 255.0);//changes colour
			setPoint(vertices[vertexNum++], left, getHeight(left, front), front);// position

			setPoint(colors[vertexNum],(rand()% 255) / 255.0,(rand()%255) / 255.0,(rand()%255) / 255.0);
			setPoint(vertices[vertexNum++], right, getHeight(right, front), front);

			setPoint(colors[vertexNum],(rand()% 255) / 255.0,(rand()% 255) / 255.0,(rand()% 255) / 255.0);
			setPoint(vertices[vertexNum++], right, getHeight(right, back), back);

			//tri2
			setPoint(colors[vertexNum], (rand() % 255) / 255.0, (rand() % 255) / 255.0, (rand() % 255) / 255.0);
			setPoint(vertices[vertexNum++], right, getHeight(right, back), back);
			
			setPoint(colors[vertexNum], (rand() % 255) / 255.0, (rand() % 255) / 255.0, (rand() % 255) / 255.0);
			setPoint(vertices[vertexNum++], left, getHeight(left, back), back);

			setPoint(colors[vertexNum], (rand() % 255) / 255.0, (rand() % 255) / 255.0, (rand() % 255) / 255.0);
			setPoint(vertices[vertexNum++], left, getHeight(left, front), front);
		}
	}
}


void Terrain::Draw()
{
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < numVerts; i++)
	{
		glColor3fv(colors[i]);
		glVertex3fv(vertices[i]);
=======
				 */
			//tri1
			setPoint(colors[vertexNum],(rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
			setPoint(vertices[vertexNum++],left,getHeight(left,front),front);



			setPoint(colors[vertexNum],(rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
			setPoint(vertices[vertexNum++],right,getHeight(right,front),front);

			setPoint(colors[vertexNum],(rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
			setPoint(vertices[vertexNum++],right,getHeight(right,back),back);


			//declare a degenerate triangle
			//TODO: fix this to draw the correct triangle
			setPoint(colors[vertexNum],0,0,0);
			setPoint(vertices[vertexNum++],0,0,0);
			setPoint(colors[vertexNum],0,0,0);
			setPoint(vertices[vertexNum++],0,0,0);
			setPoint(colors[vertexNum],0,0,0);
			setPoint(vertices[vertexNum++],0,0,0);




		}
	}




}


void Terrain::Draw(){

	glBegin(GL_TRIANGLES);
	for(int i =0;i<numVerts;i++){
			glColor3fv(colors[i]);
			glVertex3fv(vertices[i]);
>>>>>>> 9ee06265fab3ad1f90849f39954766e5d6de13f0
	}
	glEnd();
}