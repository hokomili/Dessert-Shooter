#include "CCQuad.h"

CCQuad::CCQuad()
{
	_nVtx = QUAD_NUM;
	_Points = new vec4[QUAD_NUM];

	_Points[0] = vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	_Points[1] = vec4(0.5f, 0.5f, 0.0f, 1.0f);
	_Points[2] = vec4(0.5f, -0.5f, 0.0f, 1.0f);
	_Points[3] = vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	_Points[4] = vec4(0.5f, -0.5f, 0.0f, 1.0f);
	_Points[5] = vec4(-0.5f, -0.5f, 0.0f, 1.0f);

	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	_Colors[1] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_Colors[2] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[3] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[4] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[5] = vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}


void CCQuad::draw()
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
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
}

void CCQuad::drawW()
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
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
}
