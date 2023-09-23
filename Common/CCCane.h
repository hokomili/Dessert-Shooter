#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define CIRCLE_NUM 22  // 2 faces, 2 triangles/face 

class CCCane : public CShape
{
private:


public:
	CCCane();
	~CCCane() {};

	void draw();
	void drawW();
	
};