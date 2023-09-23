#include "CCJelly.h"

CCJelly::CCJelly()
{
	_nVtx = CIRCLE_NUM;
	_Points = new vec4[CIRCLE_NUM];
	float twicepi = 2 * M_PI;
	_Points[0] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 1; i < CIRCLE_NUM - 3; i++) {
		_Points[i] = vec4(cosf((i-1) * twicepi / (CIRCLE_NUM +2)), sinf((i-1) * twicepi / (CIRCLE_NUM +2)), 0.0f, 1.0f);
	}
	_Points[9] = vec4(-1.0f, -1.0f, 0.0f, 1.0f);
	_Points[10] = vec4(1.0f, -1.0f, 0.0f, 1.0f);
	_Points[11]= vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_Colors = new vec4[CIRCLE_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	_Colors[1] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_Colors[2] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[3] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[4] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[5] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[6] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_Colors[7] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[8] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[9] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[10] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[11] = vec4(1.0f, 0.0f, 0.0f, 1.0f);

	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}


void CCJelly::draw()
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

void CCJelly::drawW()
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
