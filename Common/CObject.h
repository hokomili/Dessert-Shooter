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
	CShape* _Shapes; // 儲存
	CShape* _hittedshapes; // 儲存
	CObject* next;
	CObject* previous;
	vec4* _Colors; // 儲存頂點顏色的指標變數

	int  _nSp; // 這個物件有幾個 vertex
	//char* _pVXshader, * _pFSshader; //vertex 與 pixel shader 的字元指標
	//GLfloat _fColor[4]; // object's color
	GLfloat _fSize[4];
	GLfloat _fClock; // 物件自己的時間

	//  for Shader
	GLuint _uiProgram;
	// Vertex Position Attribute
	GLuint _uiModelView, _uiProjection;
	// Matrix 
	mat4 g_mxModelView, g_mxProjection;
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;
	// 紀錄是否有矩陣的更新
	bool  _bUpdateMV;
	bool  _bUpdateProj;


	CObject();
	virtual ~CObject();

	//virtual void Update(float dt) = 0;// 提供讓每一個 frame 都可以對幾何模型改變內容
	void setTRSMatrix(mat4& mat);
	void setSize(vec4 vSize);
	virtual void setShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT)=0;
	virtual void move(float dt)=0;
	virtual void draw() = 0;
	virtual void drawW() = 0; // Drawing without setting shaders

};


