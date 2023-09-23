// Rotate Objects with mouse events
// �������ʱ��� Y �b
// �W�U���ʱ��� X �b

#include "header/Angel.h"
#include "Common/CQuad.h"

#define SPACE_KEY 32
#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2) 
#define VP_HALFWIDTH 12.0f
#define GRID_SIZE 11 

// For grid quad
CQuad *g_pGridQuad[GRID_SIZE*GRID_SIZE]; // �Q���@�� 8X8 ���ѽL��l
float  g_fQuadT[GRID_SIZE*GRID_SIZE][3]={0};

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxIdentity(1.0f);
mat4 g_mxProjection;

// �u�� Y �b����
GLfloat g_fYAngle = 0;   // Y �b�����ਤ��
GLfloat g_fXAngle = 0;   // X �b�����ਤ��

GLfloat g_fTx=0, g_fTy=0;

//----------------------------------------------------------------------------
// �禡���쫬�ŧi
void IdleProcess();
void CreateGridQuad();

void init( void )
{
	//  ���� projection �x�}�A���B�����ͥ���v�x�}
    g_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);

	// �����b glewInit(); ���槹��,�b���檫����骺���o
	CreateGridQuad();

    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
}

//----------------------------------------------------------------------------

void GL_Display( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window


	g_pGridQuad[0]->draw();
	for( int i = 1 ; i < GRID_SIZE*GRID_SIZE ; i++ )  {
		g_pGridQuad[i]->drawW();
	}

	//for( int i = 0 ; i < GRID_SIZE*GRID_SIZE ; i++ )  {
	//	g_pGridQuad[i]->Draw();
	//}

	glutSwapBuffers();	// �洫 Frame Buffer
}

void onFrameMove(float delta)
{
	GL_Display();
}

//----------------------------------------------------------------------------
void CreateGridQuad()
{
	GLuint uiShaderHandle;
	vec4 vColor = vec4( 0, 0, 0, 1);
	vec4 vT;
	mat4 mxT;
	int idx = 0;

	// x-> -10 -8 -6 -4 -2 0  2  4  6  8  10
	// y->  10  8  6  4  2 0 -2 -4 -6 -8 -10

	for( int i = 0 ; i < GRID_SIZE ; i++ ) {
		for( int j = 0 ; j < GRID_SIZE ; j++ ) {
			g_fQuadT[idx][1] = 10 - i*2.0f;
			g_fQuadT[idx][0] = -10 + j*2.0f;
			g_pGridQuad[idx] = new CQuad;
			if( idx == 0 )  { // �Ĥ@�Ӫ���A�����إ� Shader
				g_pGridQuad[idx]->setShader(g_mxModelView, g_mxProjection);
				uiShaderHandle = g_pGridQuad[idx]->getShaderHandle(); // ���o Shader Handle
				vColor.x = 0.15f; vColor.y = 0.3f; vColor.z = 0.3f; vColor.w = 1.0f;
				g_pGridQuad[idx]->setColor(vColor);
			}
			else {
				g_pGridQuad[idx]->setShader(g_mxModelView, g_mxProjection, uiShaderHandle);
				vColor.x = j*0.08f + 0.15f; vColor.y = i*0.06f + 0.3f; vColor.z =  0.3f; vColor.w = 1.0f;
				g_pGridQuad[idx]->setColor(vColor);
			}
			mxT = Translate(g_fQuadT[idx][0],g_fQuadT[idx][1],g_fQuadT[idx][2]);	
			g_pGridQuad[idx]->setTRSMatrix(mxT);
			idx++;
		}
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
		for( int i = 0 ; i < GRID_SIZE*GRID_SIZE ; i++ ) delete g_pGridQuad[i];
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
//----------------------------------------------------------------------------
// The passive motion callback for a window is called when the mouse moves within the window while no mouse buttons are pressed.
void Win_PassiveMotion(int x, int y) {
	mat4 mxGT, mxT;
	
	g_fTx = 12.0f*(x - HALF_SIZE)/(HALF_SIZE);
	g_fTy = -12.0f*(y - HALF_SIZE)/(HALF_SIZE);
	mxGT = Translate(g_fTx,g_fTy,0);

	for( int i = 0 ; i < GRID_SIZE*GRID_SIZE ; i++ ) {
		mxT = Translate(g_fQuadT[i][0],g_fQuadT[i][1],g_fQuadT[i][2]);	
		g_pGridQuad[i]->setTRSMatrix(mxGT*mxT);
	}
}

// The motion callback for a window is called when the mouse moves within the window while one or more mouse buttons are pressed.
void Win_MouseMotion(int x, int y) {
	mat4 mxRx, mxRy, mxT, mxF, mxGT;
	vec4 vT;
	int idx=0;
	g_fYAngle = 90.0f*(x - HALF_SIZE)/(HALF_SIZE);
	g_fXAngle = -90.0f*(y - HALF_SIZE)/(HALF_SIZE);
	mxRx = RotateX(g_fXAngle);
	mxRy = RotateY(g_fYAngle);
	mxF = mxRy*mxRx;
	mxGT = Translate(g_fTx,g_fTy,0);
	for( int i = 0 ; i < GRID_SIZE*GRID_SIZE ; i++ ) {
		mxT = Translate(g_fQuadT[i][0],g_fQuadT[i][1],g_fQuadT[i][2]);	
		g_pGridQuad[i]->setTRSMatrix(mxGT*mxT*mxF);
	}
}
//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	mat4 rx, ry, rz;
		switch(key) {
		case GLUT_KEY_LEFT:		// �ثe���U���O�V����V��
			break;
		case GLUT_KEY_RIGHT:		// �ثe���U���O�V�k��V��
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

    glutCreateWindow( "OpenGL_Example3" );

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE; 
    glewInit();  

    init();

	glutMouseFunc(Win_Mouse);
	glutMotionFunc(Win_MouseMotion);
	glutPassiveMotionFunc(Win_PassiveMotion);
	
    glutKeyboardFunc( Win_Keyboard );	// �B�z ASCII ����p A�Ba�BESC ��...����
	glutSpecialFunc( Win_SpecialKeyboard);	// �B�z NON-ASCII ����p F1�BHome�B��V��...����
    glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	
    glutMainLoop();
    return 0;
}
