#include "CShield.h"
#include "CCQuad.h"
CShield::CShield()
{
	radius = 0.5;
	health = 2000.0f;
	velocity = vec2(0.0f,0.2f);
	position = vec2(0.0f, 0.0f);
	vec4 vColor = vec4(0.76f, 0.54f, 0.32f, 1.0f);
	vec4 vSize = vec4(1.2, 1.2, 0, 1);
	mat4 g_mxModelView(1.0f);
	_nSp = QUAD_NUM;
	_Shapes = new CCQuad;
	_Shapes->setColor(vColor);
	_Shapes->setSize(vSize);
	_Shapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_Shapes->setShader(g_mxModelView, g_mxProjection);
	_Shapes->next =  new CCQuad;
	vColor = vec4(0.6f, 0.4f, 0.2f, 1.0f);
	vSize = vec4(0.8, 0.8, 0, 1);
	_Shapes->next->setColor(vColor);
	_Shapes->next->setSize(vSize);
	_Shapes->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_Shapes->next->setShader(g_mxModelView, g_mxProjection);
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CShield::setTRSMatrix(mat4& mat)
{
	_Shapes->setTRSMatrix(mat);
	_mxTRS = mat;
	_Shapes->next->setTRSMatrix(mat);
	_bUpdateMV = true;
}


void CShield::draw()
{
	_Shapes->draw();
	_Shapes->next->draw();
}

void CShield::drawW()
{
	_Shapes->drawW();
	_Shapes->next->drawW();
}
void CShield::move(float dt)
{
	mat4 mxT = Translate(velocity.x * dt, velocity.y * dt, 0.0f);
	_Shapes->setTRSMatrix(mxT);
	_Shapes->next->setTRSMatrix(mxT);
}
void CShield::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
}