#include "CLollipop.h"
#include "CCCircle.h"
#include "CCRoundrect.h"
#include "CCTri.h"
CLollipop::CLollipop()
{
	state = 0;
	radius = 2;
	b_cooldown = 0.4f;
	timer = 0;
	health = 36;
	previous = nullptr;
	next = nullptr;
	life = 200.0f;
	velocity = vec2(0.0f,-0.2f);
	position = vec2(position.x + float(rand() % 240)/10 - 12, 12.5f);
	rotation = 0;
	vec4 vColor = vec4(0.7,0.7,0.7, 1.0f);
	vec4 vSize = vec4(0.6, 7, 0, 1);
	mat4 g_mxModelView(1.0f);
	_nSp = QUAD_NUM;
	_Shapes = new CCRoundrect;
	CShape* tempptr = _Shapes;
	_Shapes->setColor(vColor);
	_Shapes->setSize(vSize);
	_Shapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_Shapes->setShader(g_mxModelView, g_mxProjection);
	_Shapes->position.y = _Shapes->position.y - 2;
	tempptr->next = new CCCircle;
	vColor = vec4(0.82, 0.46, 0.55, 1.0f);
	vSize = vec4(2.0, 2.0, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr = tempptr->next;
	tempptr->next = new CCRoundrect;
	vColor = vec4(0.8f, 0.4f, 0.5f, 1.0f);
	vSize = vec4(4.4, 1, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr = tempptr->next;
	tempptr->next = new CCRoundrect;
	vColor = vec4(0.85f, 0.85f, 0.85f, 1.0f);
	vSize = vec4(2, 0.6, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr = tempptr->next;
	tempptr->next = new CCCircle;
	vSize = vec4(0.4, 0.4, 0, 1);
	vColor = vec4(0.2,0.2,0.2, 1.0f);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr = tempptr->next;
	tempptr->next = new CCCircle;
	vSize = vec4(0.4, 0.4, 0, 1);
	vColor = vec4(0.9, 0.2, 0.2, 1.0f);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_hittedshapes = new CCCircle;
	vColor = vec4(0.9, 0.2, 0.2, 1.0f);
	vSize = vec4(2.0, 2.0, 0, 1);
	_hittedshapes->setColor(vColor);
	_hittedshapes->setSize(vSize);
	_hittedshapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_hittedshapes->setShader(g_mxModelView, g_mxProjection);
	_hittedshapes->next = new CCRoundrect;
	vColor = vec4(0.9f, 0.2f, 0.2f, 1.0f);
	vSize = vec4(4.4, 1, 0, 1);
	_hittedshapes->next->setColor(vColor);
	_hittedshapes->next->setSize(vSize);
	_hittedshapes->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_hittedshapes->next->setShader(g_mxModelView, g_mxProjection);
	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CLollipop::setTRSMatrix(mat4& mat)
{
	_Shapes->setTRSMatrix(mat);
	CShape* tempptr = _Shapes;
	for (int i = 0; tempptr != nullptr;i++) {
		tempptr->setTRSMatrix( mat* Translate(tempptr->position.x, tempptr->position.y, 0));
		tempptr = tempptr->next;
	}
	_hittedshapes->setTRSMatrix(mat);
	_mxTRS = mat;
	_bUpdateMV = true;
}


void CLollipop::draw()
{
	CShape* tempptr = _Shapes;
	if (state >= 3) {
		tempptr = tempptr->next;
	}
	else {
		tempptr->draw();
		tempptr = tempptr->next;
	}
	for (int i = 0; i < 4;i++) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
	if (state >= 2) {
		tempptr->draw();
	}
	if (hitted) {
		_hittedshapes->draw();
	}
}

void CLollipop::drawW()
{
	_Shapes->drawW();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->drawW();
		tempptr = tempptr->next;
	}
}
void CLollipop::move(float dt)
{
	if (hitted) {
		hitcooldown -= dt;
	}
	if (hitcooldown <= 0) {
		hitted = false;
	}
	timer += dt;
	mat4 mxT = Translate(position.x, position.y + velocity.y * dt * 4.0f, 0.0f);
	position = position + velocity * dt * 4.0f;
	mplayertranslate = mxT;
	if (state < 1&&position.y <= 8  ) {
		state = 1;
	}
	if (state<2&&health <= 24) {
		state = 2;
	}
	if (state < 3 && health <= 12) {
		state = 3;
	}
	if (health <= 0) {
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
void CLollipop::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->setShader(mxView, mxProjection, uiShaderHandle);
		tempptr = tempptr->next;
	}
}