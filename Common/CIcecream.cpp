#include "CIcecream.h"
#include "CCCircle.h"
#include "CCCone.h"
CIcecream::CIcecream()
{
	previous = nullptr;
	next = nullptr;
	life = 6.0f;
	velocity = vec2(0.0f,0.2f);
	position = vec2(0.0f, -15.0f);
	vec4 vColor = vec4(0.7 + float(rand() % 4) / 18, 0.7 + float(rand() % 4) / 18, 0.7 + float(rand() % 4) / 18, 1.0f);
	vec4 vSize = vec4(1, 1, 0, 1);
	mat4 g_mxModelView(1.0f);
	_nSp = QUAD_NUM;
	_Shapes = new CCCircle;
	_Shapes->setColor(vColor);
	_Shapes->setSize(vSize);
	_Shapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_Shapes->setShader(g_mxModelView, g_mxProjection);
	_Shapes->position.x = _Shapes->position.x + rand() % 16 - 8;
	if (_Shapes->position.x < -12)_Shapes->position.x += 12;
	_Shapes->position.y = _Shapes->position.y + 2;
	CShape* tempptr = _Shapes;
	for (int i = 0; i < 2;i++) {
		tempptr->next = new CCCircle;
		vColor = vec4(0.7 + float(rand() % 4) / 18, 0.7 + float(rand() % 4) / 18, 0.7 + float(rand() % 4) / 18, 1.0f);
		tempptr->next->setColor(vColor);
		tempptr->next->setSize(vSize);
		tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
		tempptr->next->setShader(g_mxModelView, g_mxProjection);
		tempptr->next->position.x = _Shapes->position.x + i * 2 - 1;
		tempptr->next->position.y = _Shapes->position.y + 1;
		tempptr = tempptr->next;
	}
	tempptr->next = new CCCone;
	vColor = vec4(1,0.54,0.3, 1.0f);
	vSize = vec4(7, 7, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CIcecream::setTRSMatrix(mat4& mat)
{
	_Shapes->setTRSMatrix(mat);
	CShape* tempptr = _Shapes;
	for (int i = 0; tempptr != nullptr;i++) {
		tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0));
		tempptr = tempptr->next;
	}
	_mxTRS = mat;
	_bUpdateMV = true;
}


void CIcecream::draw()
{
	_Shapes->draw();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
}

void CIcecream::drawW()
{
	_Shapes->drawW();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->drawW();
		tempptr = tempptr->next;
	}
}
void CIcecream::move(float dt)
{
	life -= dt;
	mat4 mxT = Translate(position.x + velocity.x * dt * 8.0f, position.y + velocity.y * dt * 8.0f, 0.0f);
	position = position + velocity * dt * 8.0f;
	mplayertranslate = mxT;
	if (life < 0) {
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
void CIcecream::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->setShader(mxView, mxProjection, uiShaderHandle);
		tempptr = tempptr->next;
	}
}