#version 130
in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;

uniform float fAngle;
uniform vec3 vTranslate;

void main()
{
    //縮放矩陣
	mat4 mxSca = mat4( 
	1, 0, 0 ,0,
	0, 1, 0 ,0,
	0, 0, 1 ,0,
	0, 0, 0 ,1);	
	
	//旋轉矩陣
	mat4 mxRot = mat4( 
	1, 0, 0 ,0,
	0, 1, 0 ,0,
	0, 0, 1 ,0,
	0, 0, 0 ,1);

	float a = radians(fAngle);
	float x = cos(a);
	float y = sin(a);
	
	//對 z 軸旋轉
	mxRot[0][0] =  x; mxRot[0][1] =  y;
	mxRot[1][0] = -y; mxRot[1][1] =  x;


	//位移矩陣
	mat4 mxTrans = mat4( 
	1, 0, 0 ,0,
	0, 1, 0 ,0,
	0, 0, 1 ,0,
	0, 0, 0 ,1);

	//加入位移量
	mxTrans[3][0] = vTranslate.x;
	mxTrans[3][1] = vTranslate.y;
	mxTrans[3][2] = vTranslate.z;

    gl_Position = Projection * ModelView * mxTrans * mxRot * vPosition;
	color = vColor;
}
