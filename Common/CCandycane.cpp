#include "CCandycane.h"
#include "CCCane.h"
#include "CCTri.h"
CCandycane::CCandycane()
{
	radius = 1;
	previous = nullptr;
	next = nullptr;
	life = 6.0f;
	health = 1;
	velocity = vec2(0.0f,-0.2f);
	position = vec2(position.x + float(rand() % 240)/10 - 12, 14.0f);
	rotation = 0;
	vec4 vColor = vec4( float(rand() % 6)/7, float(rand() % 6) / 7, float(rand() % 6)/7, 1.0f);
	vec4 vSize = vec4(1.5, 1.35, 0, 1);
	mat4 g_mxModelView(1.0f);
	_nSp = QUAD_NUM;
	_Shapes = new CCCane;
	CShape* tempptr = _Shapes;
	tempptr->setColor(vColor);
	tempptr->setSize(vSize);
	tempptr->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->setShader(g_mxModelView, g_mxProjection);
	tempptr->position.y = tempptr->position.y-0.77;
	tempptr->next = new CCCane;
	vColor = vec4(sqrtf(vColor.x), sqrtf(vColor.y), sqrtf(vColor.z), 0);
	tempptr->next->setColor(vColor);
	vSize = vec4(1.3, 1.3, 0, 1);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.y = tempptr->next->position.y - 0.77;
	tempptr = tempptr->next;
	tempptr->next = new CCTri;
	vSize = vec4(0.6, 0.6, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->next->position.x - 0.56;
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CCandycane::setTRSMatrix(mat4& mat)
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


void CCandycane::draw()
{
	_Shapes->draw();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
}

void CCandycane::drawW()
{
	_Shapes->drawW();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->drawW();
		tempptr = tempptr->next;
	}
}
void CCandycane::move(float dt)
{
	life -= dt;
	mat4 mxT = Translate(position.x + velocity.x * dt * 1.0f, position.y + velocity.y * dt * 1.0f, 0.0f);
	position = position+ velocity * dt * 1.0f;
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
void CCandycane::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->setShader(mxView, mxProjection, uiShaderHandle);
		tempptr = tempptr->next;
	}
}