#include "stdafx.h"
#include "SFML/OpenGL.hpp"
#include "Terrain.h"
#include <cmath>

Terrain::Terrain(void)
{
	gridWidth = 100;
	gridDepth = 100;
	heightestPoint = 0;
	terrWidth = 50; //size of terrain in world units
	terrDepth = 50;

	vertices = NULL;
	colors = NULL;	
	normals = NULL;
	texCoords = NULL;

	//num squares in grid will be width*height, two triangles per square
	//3 verts per triangle
	numVerts = gridDepth * gridWidth * 2 * 3;
}

Terrain::~Terrain(void)
{
	delete [] vertices;
	delete [] colors;
	delete [] normals;
}

//interpolate between two values
float lerp(float start, float end, float t)
{
	return start + (end - start) * t;
}

void Terrain::setPoint(vector v, float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

//helper function to calculate height of terrain at a given point in space
//you will need to modify this significantly to pull height from a map
float  Terrain::getHeight(float x, float y){

	//for the sample we will calculate height based on distance form origin
	float dist = sqrt(x * x + y * y);

	//center will be the highest point
	dist = 30 - dist;
	//put a nice curve in it
	dist *= dist;
	dist *= dist;
	//whoah, way to high, make it smaller
	dist /= 50000;

	return dist;
}

float Terrain::getHeightWithFile(float x, float y)
{
	float answer = image.getPixel(((x + terrWidth / 2) / terrWidth) * image.getSize().x, 
								  ((y + terrDepth / 2) / terrDepth) * image.getSize().y).r / 256.0f;//get 
	if (heightestPoint < answer)
	{
		heightestPoint = answer;
	}
	return answer;
}

void Terrain::Init(std::string name){
	
	delete [] vertices;//just in case we've called init before
	vertices = new vector[numVerts];
	delete [] colors;
	colors = new vector[numVerts];
	delete [] normals;
	normals = new vector[numVerts];
	delete[] texCoords;
	texCoords = new vector[numVerts];

	image.loadFromFile(name);

	GLfloat * vert1, *vert2, *vert3;

	GLfloat norm[3];

	//interpolate along the edges to generate interior points
	for (int i = 0; i < gridWidth - 1; i++)//iterate left to right
	{ 
		for (int j = 0; j < gridDepth - 1; j++)//iterate front to back
		{
			int sqNum = (j + i * gridDepth);
			int vertexNum = sqNum * 3 * 2; //6 vertices per square (2 tris)
			float front = lerp(-terrDepth / 2, terrDepth / 2, (float)j / gridDepth);
			float back  = lerp(-terrDepth / 2, terrDepth / 2, (float)(j + 1) / gridDepth);
			float left  = lerp(-terrWidth / 2, terrWidth / 2, (float)i / gridDepth);
			float right = lerp(-terrDepth / 2, terrDepth / 2, (float)(i + 1) / gridDepth);

			/*
			back   +-----+	looking from above, the grid is made up of regular squares
			|tri1/|	'left & 'right' are the x cooded of the edges of the square
			|   / |	'back' & 'front' are the y coords of the square
			|  /  |	each square is made of two trianlges (1 & 2)
			| /   |
			|/tri2|
			front  +-----+
			left   right
			*/
			int offsetheight = 10;
			//tri1
			vert1 = vertices[vertexNum];
			setPoint(texCoords[vertexNum], 0, 1, 0);
			setPoint(colors[vertexNum], getHeightWithFile(left, front), getHeightWithFile(left, front), getHeightWithFile(left, front));
			setPoint(vertices[vertexNum++], left, getHeightWithFile(left, front) * offsetheight, front);

			vert2 = vertices[vertexNum];
			setPoint(texCoords[vertexNum], 1, 1, 0);
			setPoint(colors[vertexNum], getHeightWithFile(right, front), getHeightWithFile(right, front), getHeightWithFile(right, front));
			setPoint(vertices[vertexNum++], right, getHeightWithFile(right, front) * offsetheight, front);

			vert3 = vertices[vertexNum];
			setPoint(texCoords[vertexNum], 1, 0, 0);
			setPoint(colors[vertexNum], getHeightWithFile(right, back), getHeightWithFile(right, back), getHeightWithFile(right, back));
			setPoint(vertices[vertexNum++], right, getHeightWithFile(right, back) * offsetheight, back);
			
			NormalVector(vert2, vert1, vert3, norm);
			for (int i = 0; i < 3; i++)
			{
				setPoint(normals[vertexNum - i], norm[0], norm[1], norm[2]);
			}

			//tri2
			vert1 = vertices[vertexNum];
			setPoint(texCoords[vertexNum], 0, 0, 0);
			setPoint(colors[vertexNum], getHeightWithFile(left, front), getHeightWithFile(left, front), getHeightWithFile(left, front));
			setPoint(vertices[vertexNum++], left, getHeightWithFile(left, front) * offsetheight, front);

			vert2 = vertices[vertexNum];
			setPoint(texCoords[vertexNum], 0, 1, 0);
			setPoint(colors[vertexNum], getHeightWithFile(right, back), getHeightWithFile(right, back), getHeightWithFile(right, back));
			setPoint(vertices[vertexNum++], right, getHeightWithFile(right, back) * offsetheight, back);

			vert3 = vertices[vertexNum];
			setPoint(texCoords[vertexNum], 0, 0, 0);
			setPoint(colors[vertexNum], getHeightWithFile(left, back), getHeightWithFile(left, back), getHeightWithFile(left, back));
			setPoint(vertices[vertexNum++], left, getHeightWithFile(left, back) * offsetheight, back);

			NormalVector(vert2, vert1, vert3, norm);
			for (int i = 0; i < 3; i++)
			{
				setPoint(normals[vertexNum - i], norm[0], norm[1], norm[2]);
			}
		}
	}
}

void Terrain::NormalVector(GLfloat p1[3], GLfloat p2[3], GLfloat p3[3], GLfloat n[3])
{
	GLfloat v1[3], v2[3]; // two vectors

	//calculate two vectors lying on the surface
	// v1=p1-p2
	// v2=p3-p2

	for (int i = 0; i<3; i++)
	{
		v1[i] = p2[i] - p1[i];
		v2[i] = p3[i] - p1[i];
	}

	// calculate cross product of two vectors
	n[0] = v1[1] * v2[2] - v2[1] * v1[2];
	n[1] = v1[2] * v2[0] - v2[2] * v1[0];
	n[2] = v1[0] * v2[1] - v2[0] * v1[1];
}

void Terrain::Draw()
{
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < numVerts; i++)
	{
		glColor3fv(colors[i]);
		glVertex3fv(vertices[i]);
		glNormal3fv(normals[i]);
		glTexCoord2fv(texCoords[i]);
	}
	glEnd();

}