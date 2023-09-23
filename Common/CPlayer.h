#ifndef CPLAYER_H
#define CPLAYER_H
#pragma once

#include "../header/Angel.h"
#include "CObject.h"
#include "CShield.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 1
#define GRID_SIZE 4
class CPlayer : public CObject
{
private:


public:
	CShield* shield[GRID_SIZE];
	CShield* supports[GRID_SIZE];
	float b_cooldown;
	float state;
	CPlayer();
	mat4  msupporttranslate[GRID_SIZE], mshieldtranslate[GRID_SIZE];
	mat4  msupportrotation[GRID_SIZE], mshieldrotation[GRID_SIZE];
	void setTRSMatrix(mat4& mat);
	void createshield(int gd,int bd,mat4 g_mxProjection);
	void draw();
	void drawW();
	void move(float dt);
	void setShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
};

#endif