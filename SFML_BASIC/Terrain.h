#pragma once
#include "stdafx.h"
#include <string>
class Terrain
{
	//size of the mesh forming the terrain
	int gridWidth,gridDepth;
	int numVerts;
	
	//size of the terrain in world_coords
	float terrWidth,terrDepth;

	typedef  GLfloat vector[3];
	//array of vertices for the grid(this will be a triangle list)
	//I know, very inefficient, but let's run before we walk
	vector *vertices;
	vector *colors;
	vector *normals;
	vector *texCoords;

	float getHeight(float x, float y);
	float getHeightWithFile(float x, float y);
	void setPoint(vector, float, float, float);

	sf::Image image;

public:
	Terrain(void);
	~Terrain(void);

	float heightestPoint;

	void Init(std::string name);
	void Draw(bool wireframe);
	void NormalVector(GLfloat p1[3], GLfloat p2[3], GLfloat p3[3], GLfloat n[3]);
};

