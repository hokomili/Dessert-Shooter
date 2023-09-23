#include "CMissle.h"
#include "CCCircle.h"
#include "CCQuad.h"
#include "CCTri.h"
#include "CCCherrystick.h"
CMissle::CMissle()
{
	radius = 1;
	previous = nullptr;
	next = nullptr;
	life = 12.0f;
	health = 5;
	velocity = vec2(0.0f,0.2f);
	position = vec2(0.0f, -15.0f);
	vec4 vColor = vec4(0.85f, 0.65f, 0.4f, 1.0f);
	vec4 vSize = vec4(0.6, 0.6, 0, 1);
	mat4 g_mxModelView(1.0f);
	_nSp = QUAD_NUM;
	_Shapes = new CCCircle;
	_Shapes->setColor(vColor);
	_Shapes->setSize(vSize);
	_Shapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_Shapes->setShader(g_mxModelView, g_mxProjection);
	_Shapes->position.y = _Shapes->position.y + 0.5;
	CShape* tempptr = _Shapes;
	tempptr->next = new CCTri;
	vSize = vec4(1, 1, 0, 1);
	vColor = vec4(0.75f, 0.7f, 0.65f, 1.0f);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->next->position.x + 0.5;
	tempptr = tempptr->next;
	tempptr->next = new CCTri;
	vSize = vec4(-1, 1, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->next->position.x - 0.5;
	tempptr = tempptr->next;
	tempptr->next = new CCQuad;
	vColor = vec4(0.85f, 0.8f, 0.75f, 1.0f);
	vSize = vec4(1, 1, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr = tempptr->next;
	tempptr->next = new CCCircle;
	vColor = vec4(0.86f, 0.1f, 0.16f, 1.0f);
	vSize = vec4(0.32, 0.32, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->position.x;
	tempptr->next->position.y = tempptr->next->position.y + 1.15;
	tempptr = tempptr->next;
	tempptr->next = new CCCherrystick;
	vColor = vec4(0.5f, 0.1f, 0.16f, 1.0f);
	vSize = vec4(0.4, 0.4, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->position.x + 0.1;
	tempptr->next->position.y = tempptr->position.y + 0.25;
	tempptr = tempptr->next;
	for (int i = 0; i < 6;i++) {
		tempptr->next = new CCQuad;
		vColor = vec4(0.7f, 0.66f, 0.6f, 1.0f);
		vSize = vec4(0.05, 1, 0, 1);
		tempptr->next->setColor(vColor);
		tempptr->next->setSize(vSize);
		tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
		tempptr->next->setShader(g_mxModelView, g_mxProjection);
		tempptr->next->position.x = tempptr->next->position.x + 0.2*(i-2.5);
		tempptr = tempptr->next;
	}
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CMissle::setTRSMatrix(mat4& mat)
{
	_Shapes->setTRSMatrix(mat * Translate(_Shapes->position.x, _Shapes->position.y, 0));
	CShape* tempptr = _Shapes;
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0));
	tempptr = tempptr->next;
	for (int i = 0; tempptr != nullptr;i++) {
		tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0) * RotateZ(-(i-2.5)*3));
		tempptr = tempptr->next;
	}
	_mxTRS = mat;
	_bUpdateMV = true;
}


void CMissle::draw()
{
	_Shapes->draw();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
}

void CMissle::drawW()
{
	_Shapes->drawW();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->drawW();
		tempptr = tempptr->next;
	}
}
void CMissle::move(float dt)
{
	life -= dt;
	mat4 mxT = Translate(position.x - velocity.x * dt * 3.0f, position.y - velocity.y * dt * 3.0f, 0.0f);
	position = position - velocity * dt * 3.0f;
	mplayertranslate = mxT;
	if (life <= 0||health <= 0) {
		if (previous != nullptr) {
			if (this->next != nullptr) {
				previous->next = this->next;
				next->previous = this->previous;
			}
			else {
				previous->next = nullptr;
			}
		}
		else {
			if (next != nullptr) {
				next->previous = nullptr;
			}
		}
		delete(this);
	}
}
void CMissle::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->setShader(mxView, mxProjection, uiShaderHandle);
		tempptr = tempptr->next;
	}
}