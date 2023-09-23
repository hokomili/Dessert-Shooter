#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 3  // 2 faces, 2 triangles/face 

class CCCone : public CShape
{
private:


public:
	CCCone();
	~CCCone() {};

	void draw();
	void drawW();
	
};