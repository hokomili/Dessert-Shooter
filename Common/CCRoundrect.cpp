#include "CCRoundrect.h"

CCRoundrect::CCRoundrect()
{
	_nVtx = CIRCLE_NUM;
	_Points = new vec4[CIRCLE_NUM];
	float twicepi = 2 * M_PI;
	_Points[0] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 1; i < 8; i++) {
		_Points[i] = vec4(cosf((i-1) * twicepi / (CIRCLE_NUM - 3)) * 0.2 + 0.3, sinf((i-1) * twicepi / (CIRCLE_NUM - 3)) * 0.2 + 0.3, 0.0f, 1.0f);
	}
	_Points[8] = vec4(-0.3f, 0.5f, 0.0f, 1.0f);
	for (int i = 9; i < 15; i++) {
		_Points[i] = vec4(cosf(i * twicepi / (CIRCLE_NUM - 3)) * 0.2 - 0.3, sinf(i * twicepi / (CIRCLE_NUM - 3)) * 0.2 + 0.3, 0.0f, 1.0f);
	}
	_Points[15] = vec4(-0.5f, -0.3f, 0.0f, 1.0f);
	for (int i = 16; i < 22; i++) {
		_Points[i] = vec4(cosf(i * twicepi / (CIRCLE_NUM - 3)) * 0.2 - 0.3, sinf(i * twicepi / (CIRCLE_NUM - 3)) * 0.2 - 0.3, 0.0f, 1.0f);
	}
	_Points[22] = vec4(0.3f, -0.5f, 0.0f, 1.0f);
	for (int i = 23; i < CIRCLE_NUM - 1; i++) {
		_Points[i] = vec4(cosf(i * twicepi / (CIRCLE_NUM - 3)) * 0.2 + 0.3, sinf(i * twicepi / (CIRCLE_NUM - 3)) * 0.2 - 0.3, 0.0f, 1.0f);
	}
	_Points[CIRCLE_NUM - 1] = vec4(0.5f, 0.3f, 0.0f, 1.0f);

	_Colors = new vec4[CIRCLE_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)

	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}


void CCRoundrect::draw()
{
	glUseProgram(_uiProgram);
	glBindVertexArray(_uiVao);
	if (_bUpdateMV) {
		_mxMVFinal = _mxView * _mxTRS;
		_bUpdateMV = false;
	}
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);

	if (_bUpdateProj) {
		glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
		_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_NUM);
}

void CCRoundrect::drawW()
{
	glBindVertexArray(_uiVao);

	if (_bUpdateMV) {
		_mxMVFinal = _mxView * _mxTRS;
		_bUpdateMV = false;
	}

	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);
	if (_bUpdateProj) {
		glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
		_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_NUM);
}
