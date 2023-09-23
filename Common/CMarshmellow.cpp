#include "CMarshmellow.h"
#include "CCCircle.h"
#include "CCRoundrect.h"
#include "CCTri.h"
CMarshmellow::CMarshmellow()
{
	radius = 1;
	b_cooldown = 1.0f;
	timer = 0;
	health = 1;
	previous = nullptr;
	next = nullptr;
	life = 12.0f;
	velocity = vec2(0.0f,-0.2f);
	position = vec2(position.x + float(rand() % 240)/10 - 12, 12.5f);
	rotation = 180;
	vec4 vColor = vec4(0.3f + float(rand() % 4) / 20, 0.3f + float(rand() % 4) / 20, 0.3f + float(rand() % 4) / 20, 1.0f);
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
	tempptr->next = new CCRoundrect;
	vSize = vec4(1.1, 1.1, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr = tempptr->next;
	tempptr->next = new CCRoundrect;
	vColor = vec4(0.85f, 0.85f, 0.85f, 1.0f);
	vSize = vec4(1, 1, 0, 1);
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
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CMarshmellow::setTRSMatrix(mat4& mat)
{
	_Shapes->setTRSMatrix(mat);
	CShape* tempptr = _Shapes;
	for (int i = 0; tempptr != nullptr;i++) {
		tempptr->setTRSMatrix( mat* Translate(tempptr->position.x, tempptr->position.y, 0));
		tempptr = tempptr->next;
	}
	_mxTRS = mat;
	_bUpdateMV = true;
}


void CMarshmellow::draw()
{
	_Shapes->draw();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
}

void CMarshmellow::drawW()
{
	_Shapes->drawW();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->drawW();
		tempptr = tempptr->next;
	}
}
void CMarshmellow::move(float dt)
{
	life -= dt;
	timer += dt;
	mat4 mxT = Translate(position.x, position.y + velocity.y * dt * 3.0f, 0.0f);
	position.y = position.y + velocity.y * dt * 3.0f;
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
void CMarshmellow::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->setShader(mxView, mxProjection, uiShaderHandle);
		tempptr = tempptr->next;
	}
}