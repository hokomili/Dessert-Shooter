#include "CDonut.h"
#include "CCDonut.h"
CDonut::CDonut()
{
	radius = 0.5f;
	previous = nullptr;
	next = nullptr;
	life = 15.0f;
	health = 7;
	velocity = vec2(0.0f,0.2f);
	position = vec2(0.0f, -15.0f);
	vec4 vColor = vec4(0.85f, 0.65f, 0.4f, 1.0f);
	vec4 vSize = vec4(0.5f, 0.5f, 0, 1);
	mat4 g_mxModelView(1.0f);
	_nSp = QUAD_NUM;
	_Shapes = new CCDonut;
	_Shapes->setColor(vColor);
	_Shapes->setSize(vSize);
	_Shapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_Shapes->setShader(g_mxModelView, g_mxProjection);
	_Shapes->next = new CCDonut;
	vColor = vec4(0.6f, 0.4f, 0.3f, 1.0f);
	vSize = vec4(0.4f, 0.4f, 0, 1);
	_Shapes->next->setColor(vColor);
	_Shapes->next->setSize(vSize);
	_Shapes->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_Shapes->next->setShader(g_mxModelView, g_mxProjection);
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CDonut::setTRSMatrix(mat4& mat)
{
	_Shapes->setTRSMatrix(mat);
	CShape* tempptr = _Shapes;
	tempptr = tempptr->next;
	for (int i = 0; tempptr != nullptr;i++) {
		tempptr->setTRSMatrix(mat);
		tempptr = tempptr->next;
	}
	_mxTRS = mat;
	_bUpdateMV = true;
}


void CDonut::draw()
{
	_Shapes->draw();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
}

void CDonut::drawW()
{
	_Shapes->drawW();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->drawW();
		tempptr = tempptr->next;
	}
}
void CDonut::move(float dt)
{
	life -= dt;
	mat4 mxT = Translate(position.x - velocity.x * dt * 9.0f, position.y - velocity.y * dt * 9.0f, 0.0f);
	position = position - velocity * dt * 9.0f;
	if (position.x > 10|| position.x < -10) {
		velocity.x = -velocity.x;
	}
	if (position.y > 12|| position.y < -12) {
		velocity.y = -velocity.y;
	}
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
void CDonut::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->setShader(mxView, mxProjection, uiShaderHandle);
		tempptr = tempptr->next;
	}
}