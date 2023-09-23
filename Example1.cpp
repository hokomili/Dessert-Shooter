// Model-View matrix and Projection matrix
// Orthogonal or Orthographic projection
// Windows Events - Keyboard & Mouse
// Rotate Rectangle

#include "header/Angel.h"
#include "Common/CQuad.h"
#include "Common/CQuadEX1.h"

#define SPACE_KEY 32

// �����b glewInit(); ���槹��,�b���檫����骺���o
CQuad *g_pQuad;	// �ŧi Quad ���Ъ���A�����ɰO�o����

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

// For Rotation
int     g_iAxis = 2; // ����b�A0:X, 1:Y, 2:Z
GLfloat g_fAngle = 0;   // X/Y/Z �T�b�����ਤ��
GLfloat g_fDir = 1;     // �����V
bool    m_bAutoRotation = false; // Controlled by Space Key

//----------------------------------------------------------------------------
// �禡���쫬�ŧi
void IdleProcess();

void init( void )
{
	// �����b glewInit(); ���槹��,�b���檫����骺���o
	g_pQuad = new CQuad;

	//  ���� projection �x�}�A���B�����ͥ���v�x�}
    g_mxProjection = Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	g_pQuad->setShader(g_mxModelView, g_mxProjection);

    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
}

void AutomaticRotation(void){
	mat4 mxRot;

	g_fAngle += g_fDir * 0.025f;     // ���ਤ�׻��W(����) 0.025 ��
	if( g_fAngle > 360.0 ) g_fAngle -= 360;
	else if (g_fAngle < 0.0) g_fAngle += 360.0;
	else ;

	// �p�����x�}�ç�s�� Shader ��
	if( g_iAxis == 0 )  mxRot =  RotateX(g_fAngle);
	else if( g_iAxis == 1 )  mxRot =  RotateY(g_fAngle);
	else mxRot =  RotateZ(g_fAngle);

	g_pQuad->setTRSMatrix(mxRot);
}
//----------------------------------------------------------------------------

void GL_Display( void )
{
    glClear( GL_COLOR_BUFFER_BIT ); // clear the window
	g_pQuad->draw();
	glutSwapBuffers();	// �洫 Frame Buffer
}

void onFrameMove(float delta)
{
	if( m_bAutoRotation ) AutomaticRotation();
	//GL_Display();
}

//----------------------------------------------------------------------------
void reset()
{ 
	g_iAxis = 2; 
	g_fAngle = 0;
	g_fDir = 1;    
	m_bAutoRotation = false;
	g_pQuad->setTRSMatrix(g_mxModelView);
}
//----------------------------------------------------------------------------

void Win_Keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
	case  SPACE_KEY:
		m_bAutoRotation = !m_bAutoRotation;
		break;
	case 68: // D key
	case 100: // d key
		g_fDir = -1 * g_fDir;
		break;
	case 82: // R key
	case 114: // r key
		reset();
		break;
    case 033:
		delete g_pQuad;
        exit( EXIT_SUCCESS );
        break;
    }
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch(button) {
		case GLUT_LEFT_BUTTON:   // �ثe���U���O�ƹ�����
			if ( state == GLUT_DOWN ) {  // �ثe���ƹ����A�O����A���� X �b
				if( g_iAxis != 0 ) { g_iAxis = 0; g_fAngle = 0; } // ���b�N���]
			}
			break;
		case GLUT_MIDDLE_BUTTON:  // �ثe���U���O�ƹ����� �A���� Y �b
			if ( state == GLUT_DOWN ) {
				if( g_iAxis != 1 ) { g_iAxis = 1; g_fAngle = 0; }
			}
			break;
		case GLUT_RIGHT_BUTTON:   // �ثe���U���O�ƹ��k��
			if ( state == GLUT_DOWN ){ // �ثe���U���O�ƹ��k��A���� Z �b
				if( g_iAxis != 2 ) { g_iAxis = 2; g_fAngle = 0; }
			} 
			break;
		default:
			break;
	} 
}
//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	mat4 mxRot;
	if( !m_bAutoRotation ) { // �S���۰ʱ���U�~���@��
		switch(key) {
			case GLUT_KEY_LEFT:		// �ثe���U���O�V����V��
				g_fAngle += 2.0;		// �f�ɰw������V
				break;
			case GLUT_KEY_RIGHT:	// �ثe���U���O�V�k��V��
				g_fAngle -= 2.0;		// ���ɰw���t��V
				break;
			default:
				break;
		}

		// �p�����x�}�ç�s�� Shader ��
		if( g_iAxis == 0 )  mxRot =  RotateX(g_fAngle);
		else if( g_iAxis == 1 )  mxRot =  RotateY(g_fAngle);
		else mxRot =  RotateZ(g_fAngle);

		g_pQuad->setTRSMatrix(mxRot);
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
    glutInitWindowSize( 512, 512 );

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "OpenGL_Example1" );

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE; 
    glewInit();  

    init();

	glutMouseFunc(Win_Mouse);
    glutKeyboardFunc( Win_Keyboard );	// �B�z ASCII ����p A�Ba�BESC ��...����
	glutSpecialFunc( Win_SpecialKeyboard);	// �B�z NON-ASCII ����p F1�BHome�B��V��...����
    glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	
    glutMainLoop();
    return 0;
}
