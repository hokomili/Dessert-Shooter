#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 6  // 2 faces, 2 triangles/face 

class CCQuad : public CShape
{
private:


public:
	CCQuad();
	~CCQuad() {};

	void draw();
	void drawW();
	
};