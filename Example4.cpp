// The parent-child relationship 
// �������ʬ�����¶�ۺ�����i��f�ɰw��V����
// �W�U�����Ŧ���¶�۬������i��f�ɰw��V����

#include "header/Angel.h"
#include "Common/CCQuad.h"

#define SPACE_KEY 32
#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2) 
#define VP_HALFWIDTH  12.0f
#define GRID_SIZE 4 
#define GDISTANCE 5
#define BDISTANCE 3

// For grid quad
CCQuad *g_pRQuad;				// ���e��������
CCQuad *g_pGQuad[GRID_SIZE];	// �� Red Quad �� child
CCQuad *g_pBQuad[GRID_SIZE];	// x�� Green Quad �� child
float  g_fRQuadT[3];
float  g_fGQuadT[GRID_SIZE][3]={0};	// ���������첾
float  g_fBQuadT[GRID_SIZE][3]={0};	// �Ŧ������첾�A�P�����������l���Y���@��@

mat4  mxRT, mxGT[GRID_SIZE], mxBT[GRID_SIZE];
mat4  mxRR, mxGR[GRID_SIZE], mxBR[GRID_SIZE];


// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxIdentity(1.0f);
mat4 g_mxProjection;

GLfloat g_fGAngle = 0;   // Green �����ਤ��
GLfloat g_fBAngle = 0;   // Blue �����ਤ��

//----------------------------------------------------------------------------
// �禡���쫬�ŧi
extern void IdleProcess();
void CreateQuadRelationship();

void init( void )
{
	//  ���� projection �x�}�A���B�����ͥ���v�x�}
    g_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);

	// �����b glewInit(); ���槹��,�b���檫����骺���o
	CreateQuadRelationship();

    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
}

//----------------------------------------------------------------------------

void GL_Display( void )
{
    glClear( GL_COLOR_BUFFER_BIT ); // clear the window
	g_pRQuad->draw();
	for( int i = 0 ; i < GRID_SIZE ; i++ ) g_pGQuad[i]->draw();
	for( int i = 0 ; i < GRID_SIZE ; i++ ) g_pBQuad[i]->draw();

	glutSwapBuffers();	// �洫 Frame Buffer
}

void onFrameMove(float delta)
{
	GL_Display();
}

//----------------------------------------------------------------------------
void CreateQuadRelationship()
{
	GLuint uiShaderHandle;
	vec4 vColor = vec4( 1, 0, 0, 1);
	vec4 vT;
	mat4 mxT;
	int idx = 0;

	// Red Quad ��b�ù�������
	g_pRQuad = new CCQuad;
	g_pRQuad->setColor(vColor);
	g_fRQuadT[0] = g_fRQuadT[1] = g_fRQuadT[2] = 0;
	mxRT = Translate(g_fRQuadT[0],g_fRQuadT[1],g_fRQuadT[2]);
	g_pRQuad->setShader(g_mxModelView, g_mxProjection);
	g_pRQuad->setTRSMatrix(mxRT);

	// ��b Red Quad �W�U���k�|�Ӥ�V�A�Z���U�� GDISTANCE
	vColor.x = 0; vColor.y = 1;
	g_fGQuadT[0][0] =  GDISTANCE; g_fGQuadT[0][1] = g_fGQuadT[0][2] = 0;
	g_fGQuadT[1][0] = -GDISTANCE; g_fGQuadT[1][1] = g_fGQuadT[1][2] = 0;
	g_fGQuadT[2][0] = g_fGQuadT[2][2]; g_fGQuadT[2][1] =  GDISTANCE;
	g_fGQuadT[3][0] = g_fGQuadT[3][2]; g_fGQuadT[3][1] = -GDISTANCE;

	for( int i = 0 ; i < 4 ; i++ ) {
		g_pGQuad[i] = new CCQuad;
		g_pGQuad[i]->setColor(vColor); 
		mxGT[i] = Translate(g_fGQuadT[i][0], g_fGQuadT[i][1], g_fGQuadT[i][2]);
		g_pGQuad[i]->setShader(g_mxModelView, g_mxProjection);
		g_pGQuad[i]->setTRSMatrix(mxRT*mxGT[i]);
	}
	
	// ��b Green Quad �W�U���k�|�Ӥ�V�A�Z���U�� BDISTANCE
	vColor.y = 0; vColor.z = 1; 
	g_fBQuadT[0][0] =  BDISTANCE; g_fBQuadT[0][1] = g_fBQuadT[0][2] = 0;
	g_fBQuadT[1][0] = -BDISTANCE; g_fBQuadT[1][1] = g_fBQuadT[1][2] = 0;
	g_fBQuadT[2][0] = g_fBQuadT[2][2]; g_fBQuadT[2][1] =  BDISTANCE;
	g_fBQuadT[3][0] = g_fBQuadT[3][2]; g_fBQuadT[3][1] = -BDISTANCE;

	for( int i = 0 ; i < 4 ; i++ ) {
		g_pBQuad[i] = new CCQuad;
		g_pBQuad[i]->setColor(vColor); 
		mxBT[i] = Translate(g_fBQuadT[i][0], g_fBQuadT[i][1], g_fBQuadT[i][2]);
		g_pBQuad[i]->setShader(g_mxModelView, g_mxProjection);
		g_pBQuad[i]->setTRSMatrix(mxRT*mxGT[i]*mxBT[i]);
	}
}
//----------------------------------------------------------------------------

void UpdateMatrix()
{
	mat4 mxGR, mxBR;
	mxGR = RotateZ(g_fGAngle);
	mxBR = RotateZ(g_fBAngle);

	g_pRQuad->setTRSMatrix(mxRT);
	for( int i = 0 ; i < 4 ; i++ ) {
		g_pGQuad[i]->setTRSMatrix(mxRT*mxGR*mxGT[i]);
	}

	for( int i = 0 ; i < 4 ; i++ ) {
		g_pBQuad[i]->setTRSMatrix(mxRT*mxGR*mxGT[i]*mxBR*mxBT[i]);
	}
}
//----------------------------------------------------------------------------
void Win_Keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
	case  SPACE_KEY:

		break;
	case 68: // D key
	case 100: // d key

		break;
	case 82: // R key
	case 114: // r key
		break;
    case 033:
		glutIdleFunc( NULL );
		delete g_pRQuad;
		for( int i = 0 ; i < GRID_SIZE ; i++ ) delete g_pGQuad[i];
		for( int i = 0 ; i < GRID_SIZE ; i++ ) delete g_pBQuad[i];
        exit( EXIT_SUCCESS );
        break;
    }
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch(button) {
		case GLUT_LEFT_BUTTON:   // �ثe���U���O�ƹ�����
			if ( state == GLUT_DOWN ) ;  
			break;
		case GLUT_MIDDLE_BUTTON:  // �ثe���U���O�ƹ����� 
			if ( state == GLUT_DOWN )  ;
			break;
		case GLUT_RIGHT_BUTTON:   // �ثe���U���O�ƹ��k��
			if ( state == GLUT_DOWN )  ; 
			break;
		default:
			break;
	} 
}

// The motion callback for a window is called when the mouse moves within the window while one or more mouse buttons are pressed.
void Win_MouseMotion(int x, int y) {
	mat4 mxGR, mxBR;
	g_fGAngle = 180.0f*(x - HALF_SIZE)/(HALF_SIZE);
	g_fBAngle = -270.0f*(y - HALF_SIZE)/(HALF_SIZE);

	mxGR = RotateZ(g_fGAngle);
	mxBR = RotateZ(g_fBAngle);

	g_pRQuad->setTRSMatrix(mxRT);
	for( int i = 0 ; i < 4 ; i++ ) {
		g_pGQuad[i]->setTRSMatrix(mxRT*mxGR*mxGT[i]);
	}

	for( int i = 0 ; i < 4 ; i++ ) {
		g_pBQuad[i]->setTRSMatrix(mxRT*mxGR*mxGT[i]*mxBR*mxBT[i]);
	}
}
//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	mat4 rx, ry, rz;
	switch(key) {
		case GLUT_KEY_LEFT:		// �ثe���U���O�V����V��A���� Red ����
			g_fRQuadT[0] -= 0.25;
			mxRT = Translate(g_fRQuadT[0],g_fRQuadT[1],g_fRQuadT[2]);
			UpdateMatrix();
			break;
		case GLUT_KEY_RIGHT:		// �ثe���U���O�V�k��V��A���� Red ���k
			g_fRQuadT[0] += 0.25;
			mxRT = Translate(g_fRQuadT[0],g_fRQuadT[1],g_fRQuadT[2]);
			UpdateMatrix();
			break;
		case GLUT_KEY_UP:		// �ثe���U���O�V�k��V��A���� Red ���k
			g_fRQuadT[1] += 0.25;
			mxRT = Translate(g_fRQuadT[0],g_fRQuadT[1],g_fRQuadT[2]);
			UpdateMatrix();
			break;
		case GLUT_KEY_DOWN:		// �ثe���U���O�V�k��V��A���� Red ���k
			g_fRQuadT[1] -= 0.25;
			mxRT = Translate(g_fRQuadT[0],g_fRQuadT[1],g_fRQuadT[2]);
			UpdateMatrix();
			break;
		default:
			break;
	}
}
//----------------------------------------------------------------------------
void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}

//----------------------------------------------------------------------------

int main( int argc, char **argv )
{
    
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( SCREEN_SIZE, SCREEN_SIZE );

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "OpenGL_Example4" );

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE; 
    glewInit();  

    init();

	glutMouseFunc(Win_Mouse);
	glutMotionFunc(Win_MouseMotion);
    glutKeyboardFunc( Win_Keyboard );	// �B�z ASCII ����p A�Ba�BESC ��...����
	glutSpecialFunc( Win_SpecialKeyboard);	// �B�z NON-ASCII ����p F1�BHome�B��V��...����
    glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	
    glutMainLoop();
    return 0;
}
