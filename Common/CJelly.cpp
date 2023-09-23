#include "CJelly.h"
#include "CCCircle.h"
#include "CCJelly.h"
#include "CCTri.h"
CJelly::CJelly()
{
	radius = 1;
	b_cooldown = 0.4f;
	timer = 0;
	health = 2;
	previous = nullptr;
	next = nullptr;
	life = 10.0f;
	velocity = vec2(0.0f,-0.2f);
	position = vec2(position.x + float(rand() % 240)/10 - 12, 12.5f);
	rotation = 0;
	vec4 vColor = vec4(0.3f + float(rand() % 4) / 8, 0.3f + float(rand() % 4) / 8, 0.3f + float(rand() % 4) / 8, 1.0f);
	vec4 vSize = vec4(-0.6, 1, 0, 1);
	mat4 g_mxModelView(1.0f);
	_nSp = QUAD_NUM;
	_Shapes = new CCTri;
	CShape* tempptr = _Shapes;
	tempptr->setColor(vColor);
	tempptr->setSize(vSize);
	tempptr->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->setShader(g_mxModelView, g_mxProjection);
	tempptr->position.x = tempptr->position.x + 0.5;
	tempptr->next = new CCTri;
	vSize = vec4(0.6, 1, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->next->position.x - 0.5;
	tempptr = tempptr->next;
	tempptr->next = new CCJelly;
	vSize = vec4(0.6, -0.6, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr = tempptr->next;
	tempptr->next = new CCJelly;
	vColor = vec4(vColor.x+0.2, vColor.y + 0.2, vColor.z + 0.2, 1.0f);
	vSize = vec4(0.5, -0.5, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr = tempptr->next;
	for (int i = 0; i < 2;i++) {
		tempptr->next = new CCCircle;
		vSize = vec4(0.2, 0.2, 0, 1);
		vColor = vec4(0.2,0.2,0.2, 1.0f);
		tempptr->next->setColor(vColor);
		tempptr->next->setSize(vSize);
		tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
		tempptr->next->setShader(g_mxModelView, g_mxProjection);
		tempptr->next->position.x = tempptr->next->position.x+i*0.6-0.3;
		tempptr->next->position.y = tempptr->position.y;
		tempptr = tempptr->next;
	}
	_hittedshapes = new CCJelly;
	vColor = vec4(0.9,0.2,0.2, 1.0f);
	vSize = vec4(0.6, -0.6, 0, 1);
	_hittedshapes->setColor(vColor);
	_hittedshapes->setSize(vSize);
	_hittedshapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_hittedshapes->setShader(g_mxModelView, g_mxProjection);
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CJelly::setTRSMatrix(mat4& mat)
{
	_Shapes->setTRSMatrix(mat);
	CShape* tempptr = _Shapes;
	for (int i = 0; tempptr != nullptr;i++) {
		tempptr->setTRSMatrix( mat* Translate(tempptr->position.x, tempptr->position.y, 0));
		tempptr = tempptr->next;
	}
	_hittedshapes->setTRSMatrix(mat);;
	_mxTRS = mat;
	_bUpdateMV = true;
}


void CJelly::draw()
{
	_Shapes->draw();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
	if (hitted) {
		_hittedshapes->draw();
	}
}

void CJelly::drawW()
{
	_Shapes->drawW();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->drawW();
		tempptr = tempptr->next;
	}
}
void CJelly::move(float dt)
{
	if (hitted) {
		hitcooldown -= dt;
	}
	if (hitcooldown <= 0) {
		hitted = false;
	}
	life -= dt;
	timer += dt;
	mat4 mxT = Translate(position.x, position.y + velocity.y * dt * 4.0f, 0.0f);
	position.y = position.y + velocity.y * dt * 4.0f;
	mplayertranslate = mxT;
	if (life < 0||health<=0) {
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
void CJelly::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->setShader(mxView, mxProjection, uiShaderHandle);
		tempptr = tempptr->next;
	}
}