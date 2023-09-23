#include "CObject.h"


CObject::CObject()
{
	invincibletime = 0.1;
	hitcooldown = 0;
	hitted = false;
	life = 0;
	tag = 0;
	radius = 0;
	health = 0;
	damage = 0;
	rotation = 0;
	isCollectable = false;
	isDamagable = false;
	isDecayable = false;
	_Shapes = nullptr; // 儲存頂點的指標變數
	_Colors = nullptr;
	next = nullptr;
	previous = nullptr;
	_nSp = 0;
	_fClock = 0;
	_bUpdateMV = false;
	_bUpdateProj = false;	
	_fSize[0] = _fSize[1] = _fSize[2] = 0.0f;
	_fSize[3] = 1.0f;
	g_mxModelView = mat4(1.0f);
	g_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);
}

CObject::~CObject()
{
	if (_Shapes != nullptr) delete[] _Shapes;
	if (_Colors != nullptr) delete[] _Colors;
}

void CObject::setTRSMatrix(mat4& mat)
{
	_mxTRS = mat;
	_bUpdateMV = true;
}

void CObject::setSize(vec4 vSize)
{
	for (int i = 0; i < _nSp; i++) {
		_Shapes[i].setSize(vSize);
	}
}