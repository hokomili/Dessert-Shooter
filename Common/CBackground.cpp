#include "CBackground.h"
#include "CCCircle.h"
CBackground::CBackground()
{
	previous = nullptr;
	next = nullptr;
	life = 6.0f;
	velocity = vec2(0.0f,0.2f);
	position = vec2(0.0f, -15.0f);
	vec4 vColor = vec4(0.65f, 0.85f, 0.6f, 1.0f);
	vec4 vSize = vec4(0.8f, 0.8f, 0, 1);
	mat4 g_mxModelView(1.0f);
	_nSp = QUAD_NUM;
	_Shapes = new CCCircle;
	_Shapes->setColor(vColor);
	_Shapes->setSize(vSize);
	_Shapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_Shapes->setShader(g_mxModelView, g_mxProjection);
	CShape* tempptr = _Shapes;
	for (int i = 0; i < 3;i++) {
		tempptr->next = new CCCircle;
		float xsize = 3+float(rand() % 6)/3;
		vSize = vec4(xsize, xsize, 0, 1);
		vColor = vec4(0.8+float(rand() % 4)/64, 0.8 + float(rand() % 4) / 64, 0.8 + float(rand() % 4) / 64, 1.0f);
		tempptr->next->setColor(vColor);
		tempptr->next->setSize(vSize);
		tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
		tempptr->next->setShader(g_mxModelView, g_mxProjection);
		tempptr->next->position.x = tempptr->position.x+rand() % 16 - 8;
		tempptr->next->position.y = 32.0f + float(rand() % 24)/3 - 4;
		if (tempptr->next->position.x < -12)tempptr->next->position.x += 12;
		else if(tempptr->next->position.x > 12)tempptr->next->position.x -= 12;
		tempptr = tempptr->next;
	}
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CBackground::setTRSMatrix(mat4& mat)
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


void CBackground::draw()
{
	_Shapes->draw();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
}

void CBackground::drawW()
{
	_Shapes->drawW();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->drawW();
		tempptr = tempptr->next;
	}
}
void CBackground::move(float dt)
{
	life -= dt;
	mat4 mxT = Translate(position.x, position.y + velocity.y * dt * 8.0f, 0.0f);
	position.y = position.y + velocity.y * dt * 8.0f;
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
void CBackground::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->setShader(mxView, mxProjection, uiShaderHandle);
		tempptr = tempptr->next;
	}
}