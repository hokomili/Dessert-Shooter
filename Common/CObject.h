#pragma once

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class CObject
{
private:



public:
	mat4 mplayertranslate, mplayerrotation;
	int health;
	float life;
	float radius;
	float invincibletime;
	float hitcooldown;
	int damage;
	int tag; //0 = player, 1 = enemy , 2 = collectable , 3 = background
	vec2 velocity;
	vec2 position;
	float rotation;
	bool isDamagable;
	bool isDecayable;
	bool isCollectable;
	bool hitted;
	CShape* _Shapes; // �x�s
	CShape* _hittedshapes; // �x�s
	CObject* next;
	CObject* previous;
	vec4* _Colors; // �x�s���I�C�⪺�����ܼ�

	int  _nSp; // �o�Ӫ��󦳴X�� vertex
	//char* _pVXshader, * _pFSshader; //vertex �P pixel shader ���r������
	//GLfloat _fColor[4]; // object's color
	GLfloat _fSize[4];
	GLfloat _fClock; // ����ۤv���ɶ�

	//  for Shader
	GLuint _uiProgram;
	// Vertex Position Attribute
	GLuint _uiModelView, _uiProjection;
	// Matrix 
	mat4 g_mxModelView, g_mxProjection;
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;
	// �����O�_���x�}����s
	bool  _bUpdateMV;
	bool  _bUpdateProj;


	CObject();
	virtual ~CObject();

	//virtual void Update(float dt) = 0;// �������C�@�� frame ���i�H��X��ҫ����ܤ��e
	void setTRSMatrix(mat4& mat);
	void setSize(vec4 vSize);
	virtual void setShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT)=0;
	virtual void move(float dt)=0;
	virtual void draw() = 0;
	virtual void drawW() = 0; // Drawing without setting shaders

};


