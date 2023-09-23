#include "CEBullet.h"
#include "CCCircle.h"
CEBullet::CEBullet()
{
	radius = 0.5f;
	previous = nullptr;
	next = nullptr;
	life = 3.0f;
	health = 1;
	velocity = vec2(0.0f,0.2f);
	position = vec2(0.0f, -15.0f);
	vec4 vColor = vec4(0.85f, 0.65f, 0.4f, 1.0f);
	vec4 vSize = vec4(0.5f, 0.5f, 0, 1);
	mat4 g_mxModelView(1.0f);
	_nSp = QUAD_NUM;
	_Shapes = new CCCircle;
	_Shapes->setColor(vColor);
	_Shapes->setSize(vSize);
	_Shapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_Shapes->setShader(g_mxModelView, g_mxProjection);
	CShape* tempptr = _Shapes;
	for (int i = 0; i < 6;i++) {
		tempptr->next = new CCCircle;
		vColor = vec4(0.88f, 0.4f, 0.3f, 1.0f);
		vSize = vec4(0.1f, 0.1f, 0, 1);
		tempptr->next->setColor(vColor);
		tempptr->next->setSize(vSize);
		tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
		tempptr->next->setShader(g_mxModelView, g_mxProjection);
		tempptr = tempptr->next;
	}
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CEBullet::setTRSMatrix(mat4& mat)
{
	_Shapes->setTRSMatrix(mat);
	CShape* tempptr = _Shapes;
	tempptr = tempptr->next;
	for (int i = 0; tempptr != nullptr;i++) {
		tempptr->setTRSMatrix(mat * Translate(cosf(i - 1) / 3, sinf(i - 1) / 3, 0));
		tempptr = tempptr->next;
	}
	_mxTRS = mat;
	_bUpdateMV = true;
}


void CEBullet::draw()
{
	_Shapes->draw();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
}

void CEBullet::drawW()
{
	_Shapes->drawW();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->drawW();
		tempptr = tempptr->next;
	}
}
void CEBullet::move(float dt)
{
	life -= dt;
	mat4 mxT = Translate(position.x - velocity.x * dt * 9.0f, position.y - velocity.y * dt * 9.0f, 0.0f);
	position = position - velocity * dt * 9.0f;
	mplayertranslate = mxT;
	if (life < 0 || health <= 0) {
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
void CEBullet::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->setShader(mxView, mxProjection, uiShaderHandle);
		tempptr = tempptr->next;
	}
}