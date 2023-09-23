#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define CIRCLE_NUM 12  // 2 faces, 2 triangles/face 

class CCJelly : public CShape
{
private:


public:
	CCJelly();
	~CCJelly() {};

	void draw();
	void drawW();
	
};