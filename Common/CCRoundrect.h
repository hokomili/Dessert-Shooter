#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define CIRCLE_NUM 30  // 2 faces, 2 triangles/face 

class CCRoundrect : public CShape
{
private:


public:
	CCRoundrect();
	~CCRoundrect() {};

	void draw();
	void drawW();
	
};