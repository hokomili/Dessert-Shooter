#pragma once

#include "../header/Angel.h"
#define VP_HALFWIDTH  12.0f
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class CShape
{
private:



public:
	vec4* _Points; // �x�s���I�������ܼ�
	vec4* _Colors; // �x�s���I�C�⪺�����ܼ�
	vec2 position;
	int  _nVtx; // �o�Ӫ��󦳴X�� vertex
	char* _pVXshader, * _pFSshader; //vertex �P pixel shader ���r������
	GLfloat _fColor[4]; // object's color
	GLfloat _fSize[4];
	GLfloat _fClock; // ����ۤv���ɶ�
	CShape* next;
	//  for Shader
	GLuint _uiProgram;
	// Vertex Position Attribute
	GLuint _uiModelView, _uiProjection;
	// Matrix 
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;
	mat4 g_mxModelView, g_mxProjection;
	// VAO
	GLuint _uiVao;
	// VBO
	GLuint _uiBuffer;
	// �����O�_���x�}����s
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	void CreateBufferObject();


	CShape();
	virtual ~CShape();

	//virtual void Update(float dt) = 0;// �������C�@�� frame ���i�H��X��ҫ����ܤ��e

	void setShaderName(const char vxShader[], const char fsShader[]);
	void setShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint getShaderHandle() { return _uiProgram; }
	void setViewMatrix(mat4& mat);
	void setProjectionMatrix(mat4& mat);
	void setTRSMatrix(mat4& mat);
	void setColor(vec4 vColor); // Single color
	void setSize(vec4 vSize);

	virtual void draw() = 0;
	virtual void drawW() = 0; // Drawing without setting shaders

};


