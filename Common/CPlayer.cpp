#include "CPlayer.h"
#include "CCWaffle.h"
#include "CCQuad.h"
#include "CCCircle.h"
#include "CCCherrystick.h"
CPlayer::CPlayer()
{
	invincibletime = 0.3;
	state = 0;
	radius = 1;
	for (int i = 0; i < GRID_SIZE; i++) {
		shield[i] = nullptr;
		supports[i] = nullptr;
	}
	b_cooldown = 0.8f;
	health = 20.0f;
	velocity = vec2(0.0f,0.2f);
	position = vec2(0.0f, -15.0f);
	vec4 vColor = vec4(0.7f, 0.4f, 0.2f, 1.0f);
	vec4 vSize = vec4(1.5, 1.5, 0, 1);
	_nSp = QUAD_NUM;
	_Shapes = new CCWaffle;
	_Shapes->setColor(vColor);
	_Shapes->setSize(vSize);
	_Shapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_Shapes->setShader(g_mxModelView, g_mxProjection);
	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	CShape* tempptr = _Shapes;
	tempptr->next = new CCWaffle;
	vColor = vec4(0.8f, 0.5f, 0.3f, 1.0f);
	vSize = vec4(1.3, 1.3, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr = tempptr->next;
	tempptr->next = new CCQuad;
	vColor = vec4(0.7f, 0.4f, 0.2f, 1.0f);
	vSize = vec4(1.2, 0.1, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->position.x+0.1;
	tempptr->next->position.y = tempptr->position.y-0.1;
	tempptr = tempptr->next;
	tempptr->next = new CCQuad;
	vSize = vec4(1.2, 0.1, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->position.x - 0.2;
	tempptr->next->position.y = tempptr->position.y ;
	tempptr = tempptr->next;
	tempptr->next = new CCQuad;
	vSize = vec4(0.85, 0.1, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->position.x - 0.1;
	tempptr->next->position.y = tempptr->position.y-0.16;
	tempptr = tempptr->next;
	tempptr->next = new CCQuad;
	vSize = vec4(0.85, 0.1, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->position.x + 0.38;
	tempptr->next->position.y = tempptr->position.y-0.04;
	tempptr = tempptr->next;
	tempptr->next = new CCWaffle;
	vColor = vec4(0.9f, 0.8f, 0.7f, 1.0f);
	vSize = vec4(1, 1, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.y = tempptr->position.y + 0.4;
	tempptr = tempptr->next;
	tempptr->next = new CCCircle;
	vColor = vec4(0.86f, 0.1f, 0.16f, 1.0f);
	vSize = vec4(0.32, 0.32, 0, 1);
	tempptr->next->setColor(vColor);
	tempptr->next->setSize(vSize);
	tempptr->next->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	tempptr->next->setShader(g_mxModelView, g_mxProjection);
	tempptr->next->position.x = tempptr->position.x;
	tempptr->next->position.y = tempptr->position.y + 0.2;
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
	_hittedshapes = new CCWaffle;
	vColor = vec4(0.9f, 0.2f, 0.2f, 1.0f);
	vSize = vec4(1.5, 1.5, 0, 1);
	_hittedshapes->setColor(vColor);
	_hittedshapes->setSize(vSize);
	_hittedshapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_hittedshapes->setShader(g_mxModelView, g_mxProjection);
	
	// Create and initialize a buffer object 
	_bUpdateProj = false;
}

void CPlayer::setTRSMatrix(mat4& mat)
{
	_Shapes->setTRSMatrix(mat);
	CShape* tempptr = _Shapes;
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0) * RotateZ(120));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0) * RotateZ(240));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0) * RotateZ(120));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0) * RotateZ(240));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0));
	tempptr = tempptr->next;
	tempptr->setTRSMatrix(mat * Translate(tempptr->position.x, tempptr->position.y, 0));
	_hittedshapes->setTRSMatrix(mat);
	_mxTRS = mat;
	_bUpdateMV = true;
}

void CPlayer::createshield(int gd,int bd,mat4 g_mxProjection)
{
	float  translate_player[3];
	float  translate_support[GRID_SIZE][3] = { 0 };
	float  translate_shield[GRID_SIZE][3] = { 0 };
	vec4 vColor = vec4(1, 1, 1, 1);
	translate_player[0] = translate_player[1] = translate_player[2] = 0;
	mplayertranslate = Translate(translate_player[0], translate_player[1], translate_player[2]);
	// 放在 Red Quad 上下左右四個方向，距離各為 GDISTANCE
	vColor.x = 0; vColor.y = 1;
	translate_support[0][0] = gd; translate_support[0][1] = translate_support[0][2] = 0;
	translate_support[1][0] = -gd; translate_support[1][1] = translate_support[1][2] = 0;
	translate_support[2][0] = translate_support[2][2] = 0; translate_support[2][1] = gd;
	translate_support[3][0] = translate_support[3][2] = 0; translate_support[3][1] = -gd;

	for (int i = 0; i < GRID_SIZE; i++) {
		supports[i] = new CShield;
		msupporttranslate[i] = Translate(translate_support[i][0], translate_support[i][1], translate_support[i][2]);
		supports[i]->setTRSMatrix(mplayertranslate * msupporttranslate[i]);
	}

	// 放在 Green Quad 上下左右四個方向，距離各為 BDISTANCE
	vColor.x = 1; vColor.y = 1; vColor.z = 1;
	translate_shield[0][0] = bd; translate_shield[0][1] = translate_shield[0][2] = 0;
	translate_shield[1][0] = -bd; translate_shield[1][1] = translate_shield[1][2] = 0;
	translate_shield[2][0] = translate_shield[2][2] = 0; translate_shield[2][1] = bd;
	translate_shield[3][0] = translate_shield[3][2] = 0; translate_shield[3][1] = -bd;

	for (int i = 0; i < 4; i++) {
		shield[i] = new CShield;
		mshieldtranslate[i] = Translate(translate_shield[i][0], translate_shield[i][1], translate_shield[i][2]);
		shield[i]->setTRSMatrix(mplayertranslate * msupporttranslate[i] * mshieldtranslate[i]);
		mat4 trs = mplayertranslate * msupporttranslate[i] * mshieldtranslate[i];
		shield[i]->position = vec2(trs._m[0].w, trs._m[1].w);
	}
}

void CPlayer::draw()
{
	_Shapes->draw();
	CShape* tempptr = _Shapes;
	for (int i = 0; i < 6;i++) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
	if (state>0) {
		tempptr->draw();
		tempptr = tempptr->next;
	}
	if (state > 1) {
		tempptr->draw();
		tempptr = tempptr->next;
		tempptr->draw();
		tempptr = tempptr->next;
	}
	if (hitted) {
		_hittedshapes->draw();
	}
	for (int i = 0; i < GRID_SIZE; i++) {
		shield[i]->draw();
	}
}

void CPlayer::drawW()
{
	_Shapes->drawW();
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->drawW();
		tempptr = tempptr->next;
	}
	for (int i = 0; i < GRID_SIZE; i++) {
		shield[i]->drawW();
	}
}
void CPlayer::move(float dt)
{
	if (hitted) {
		hitcooldown -= dt;
	}
	if (hitcooldown <= 0) {
		hitted = false;
	}
	mat4 mxT = Translate(position.x+velocity.x * dt*4.0f,position.y+velocity.y * dt*4.0f, 0.0f);
	position = position + velocity * dt*4.0f;
	rotation = atan2f(velocity.y * dt * 4.0f + 1, velocity.x * dt * 4.0f) *180 / 3.141592f-90;
	if (rotation < 0) rotation += 360;
	mplayertranslate = mxT;
}
void CPlayer::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	_Shapes->setShader(mxView, mxProjection, uiShaderHandle);
	CShape* tempptr = _Shapes;
	while (tempptr != nullptr) {
		tempptr->setShader(mxView, mxProjection, uiShaderHandle);
		tempptr = tempptr->next;
	}
}