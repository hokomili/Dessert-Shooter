#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define CIRCLE_NUM 36  // 2 faces, 2 triangles/face 

class CCDonut : public CShape
{
private:


public:
	CCDonut();
	~CCDonut() {};

	void draw();
	void drawW();
	
};