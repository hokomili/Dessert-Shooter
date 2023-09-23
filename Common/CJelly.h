#ifndef CJelly_H
#define CJelly_H
#pragma once

#include "../header/Angel.h"
#include "CObject.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 1
class CJelly : public CObject
{
private:


public:
	CJelly();
	CJelly* next;
	CJelly* previous;
	float b_cooldown;
	float timer;
	void setTRSMatrix(mat4& mat);
	void draw();
	void drawW();
	void move(float dt);
	void setShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
};

#endif