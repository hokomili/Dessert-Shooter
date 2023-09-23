#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define CIRCLE_NUM 8  // 2 faces, 2 triangles/face 

class CCWaffle : public CShape
{
private:


public:
	CCWaffle();
	~CCWaffle() {};

	void draw();
	void drawW();
	
};