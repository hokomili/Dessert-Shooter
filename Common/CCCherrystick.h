#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define CIRCLE_NUM 16  // 2 faces, 2 triangles/face 

class CCCherrystick : public CShape
{
private:


public:
	CCCherrystick();
	~CCCherrystick() {};

	void draw();
	void drawW();
	
};