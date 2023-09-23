#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define CIRCLE_NUM 20  // 2 faces, 2 triangles/face 

class CCCircle : public CShape
{
private:


public:
	CCCircle();
	~CCCircle() {};

	void draw();
	void drawW();
	
};