#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 3  // 2 faces, 2 triangles/face 

class CCTri : public CShape
{
private:


public:
	CCTri();
	~CCTri() {};

	void draw();
	void drawW();
	
};