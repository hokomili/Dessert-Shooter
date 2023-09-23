//110819013 Candy franzy shooter
/*
* 功能需求
(8%)操控與背景部分
	(1%)滑鼠可以控制戰鬥機的左右移動
	(1%)戰鬥機傭有防禦裝置，並以父子關係方式呈現
	(1%)可以發射飛彈
	(3%)能提供連續發射(LINKED LIST，自己撰寫，使用STL 2分)
	(2%)能產生有速度感的背景物件，或是其他裝飾性的物件
(11%)敵人部分
	(2%)有至少三種以上不同外形的敵人(不同的顏色)，基本的四方型不算在內
	(3%)以物件導向的多型來控制所有的敵人
	(1%)敵人可以不斷的產生，而且具有不同的顏色
	(1%)敵人能隨機朝向玩家發射子彈攻擊
	(2%)戰鬥機發射的子彈可以打到敵人，而且敵人會消失
	(2%)有BOSS級的敵人，且至會根據被攻擊的多寡至少三種不同的狀態(外型改變或攻擊方式)可以切換
(4%) (玩家部分)
	(2%)能判斷玩家是否被打中 並做出合理的反應
	(2%)玩家的船艦至少有三種狀態(外型改變)，且有提供玩家的船艦可改變狀態的機制
(8%)其他你覺得可以展示的技術，包含物理或是數學的運算
	(2%)提供階層式動態控制，並以時間為基礎進行動態的展示
	(如: OpenGL_2 的 Example4 ，以自動產生的軌跡去控制相關的物件運動)
	(2%)發射導向飛彈攻擊移動的Boss
	敵人被打到有其他的效果
	戰鬥機被打到時有其他的效果
	背景除了速度感物件外，有其他的效果
總分：
*/

#include "header/Angel.h"
#include "Common/CCQuad.h"
#include "Common/CCCircle.h"
#include "Common/CCTri.h"
#include "Common/CCCane.h"
#include "Common/CBullet.h"
#include "Common/CMissle.h"
#include "Common/CPlayer.h"
#include "Common/CBackground.h"
#include "Common/CMarshmellow.h"
#include "Common/CJelly.h"
#include "Common/CCandycane.h"
#include "Common/CEBullet.h"
#include "Common/CLollipop.h"
#include "Common/CDonut.h"
#include "Common/CIcecream.h"

#define SPACE_KEY 32
#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2) 
#define VP_HALFWIDTH  12.0f
#define GRID_SIZE 4 
#define GDISTANCE 3
#define BDISTANCE 1

// For grid quad
CPlayer *player;				// 位於畫面正中間
CBullet* p_bullet;
CMissle* missle;
CBackground* background;
CMarshmellow* marshe;
CJelly* jerry;
CCandycane* can;
CEBullet* e_bullet;
CLollipop* lol;
CDonut* don;
CIcecream* ice;

/*
CCQuad *support[GRID_SIZE];	// 為 Red Quad 的 child
CBullet *shield[GRID_SIZE];	// x為 Green Quad 的 child

float  translate_support[GRID_SIZE][3]={0};	// 紅色方塊的位移
float  translate_shield[GRID_SIZE][3]={0};	// 藍色方塊的位移，與紅色方塊的父子關係為一對一

mat4  mplayertranslate, msupporttranslate[GRID_SIZE], mshieldtranslate[GRID_SIZE];
mat4  mplayerrotation, msupportrotation[GRID_SIZE], mshieldrotation[GRID_SIZE];
*/
float  translate_player[3];
// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxIdentity(1.0f);
mat4 g_mxProjection;
int lastx, lasty;
float bullettimer;
int bulletcounter = 0;
int bbcounter = 0;
GLfloat supportangle = 0;   // Green 的旋轉角度
GLfloat shieldangle = 0;   // Blue 的旋轉角度
bool won=false;
int score = 0;
GLfloat g_fTx = 0, g_fTy = 0;
//----------------------------------------------------------------------------
// 函式的原型宣告
extern void IdleProcess();
//void CreateQuadRelationship();
void autoMotion(float);
void generate(float);
void UpdateMatrix();
void collide(float);
bool iscollided(vec2,vec2, float);
//vec2 normalize(vec2);
void init( void )
{
	//  產生 projection 矩陣，此處為產生正投影矩陣
    g_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);
	srand(time(NULL));
	// 必須在 glewInit(); 執行完後,在執行物件實體的取得
	//CreateQuadRelationship();
	player = new CPlayer;
	p_bullet = nullptr;
	missle = nullptr;
	background = nullptr;
	marshe = nullptr;
	jerry = nullptr;
	can = nullptr;
	e_bullet = nullptr;
	lol = nullptr;
	don = nullptr;
	ice = nullptr;
	player->createshield(GDISTANCE, BDISTANCE, g_mxProjection);
	translate_player[0] = translate_player[1] = translate_player[2] = 0;
    glClearColor( 0.8, 0.83, 0.8, 1.0 ); // black background
}

//----------------------------------------------------------------------------

void GL_Display( void )
{
    glClear( GL_COLOR_BUFFER_BIT ); // clear the window
	CBackground* bg_ptr = background;
	while (bg_ptr != nullptr) {
		bg_ptr->draw();
		bg_ptr = bg_ptr->next;
	}
	CIcecream* i_ptr = ice;
	while (i_ptr != nullptr) {
		i_ptr->draw();
		i_ptr = i_ptr->next;
	}
	if(lol != nullptr) {
		lol->draw();
	}
	CBullet* b_ptr = p_bullet;
	while (b_ptr != nullptr) {
		b_ptr->draw();
		b_ptr = b_ptr->next;
	}
	CDonut* d_ptr = don;
	while (d_ptr != nullptr) {
		d_ptr->draw();
		d_ptr = d_ptr->next;
	}
	CMissle* m_ptr = missle;
	while (m_ptr != nullptr) {
		m_ptr->draw();
		m_ptr = m_ptr->next;
	}
	CEBullet* eb_ptr = e_bullet;
	while (eb_ptr != nullptr) {
		eb_ptr->draw();
		eb_ptr = eb_ptr->next;
	}
	CMarshmellow* ms_ptr = marshe;
	while (ms_ptr != nullptr) {
		ms_ptr->draw();
		ms_ptr = ms_ptr->next;
	}
	CJelly* j_ptr = jerry;
	while (j_ptr != nullptr) {
		j_ptr->draw();
		j_ptr = j_ptr->next;
	}
	CCandycane* c_ptr = can;
	while (c_ptr != nullptr) {
		c_ptr->draw();
		c_ptr = c_ptr->next;
	}
	player->draw();
	//for( int i = 0 ; i < GRID_SIZE ; i++ ) g_pGQuad[i]->draw(); hide parent
	//for( int i = 0 ; i < GRID_SIZE ; i++ ) shield[i]->draw();

	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	generate(delta);
	autoMotion(delta);
	collide(delta);
	GL_Display();
}

//----------------------------------------------------------------------------
/*
void CreateQuadRelationship()
{
	// Red Quad 放在螢幕正中間
	player = new CPlayer;
	player->createshield(GDISTANCE, BDISTANCE);
	translate_player[0] = translate_player[1] = translate_player[2] = 0;
	mplayertranslate = Translate(translate_player[0],translate_player[1],translate_player[2]);
	player->_Shapes->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	player->setShader(g_mxModelView, g_mxProjection);
	player->setTRSMatrix(mplayertranslate);
	// 放在 Red Quad 上下左右四個方向，距離各為 GDISTANCE
	translate_support[0][0] =  GDISTANCE; translate_support[0][1] = translate_support[0][2] = 0;
	translate_support[1][0] = -GDISTANCE; translate_support[1][1] = translate_support[1][2] = 0;
	translate_support[2][0] = translate_support[2][2]=0; translate_support[2][1] =  GDISTANCE;
	translate_support[3][0] = translate_support[3][2]=0; translate_support[3][1] = -GDISTANCE;

	for( int i = 0 ; i < 4 ; i++ ) {
		support[i] = new CCQuad;
		support[i]->setColor(vColor); 
		msupporttranslate[i] = Translate(translate_support[i][0], translate_support[i][1], translate_support[i][2]);
		support[i]->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
		support[i]->setShader(g_mxModelView, g_mxProjection);
		support[i]->setTRSMatrix(mplayertranslate*msupporttranslate[i]);
	}
	
	// 放在 Green Quad 上下左右四個方向，距離各為 BDISTANCE
	vColor.x = 1; vColor.y = 1; vColor.z = 1;
	translate_shield[0][0] =  BDISTANCE; translate_shield[0][1] = translate_shield[0][2] = 0;
	translate_shield[1][0] = -BDISTANCE; translate_shield[1][1] = translate_shield[1][2] = 0;
	translate_shield[2][0] = translate_shield[2][2]=0; translate_shield[2][1] =  BDISTANCE;
	translate_shield[3][0] = translate_shield[3][2]=0; translate_shield[3][1] = -BDISTANCE;

	for( int i = 0 ; i < 4 ; i++ ) {
		shield[i] = new CBullet;
		//g_pBQuad[i]->setColor(vColor); 
		mshieldtranslate[i] = Translate(translate_shield[i][0], translate_shield[i][1], translate_shield[i][2]);
		//g_pBQuad[i]->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
		shield[i]->setShader(g_mxModelView, g_mxProjection);
		shield[i]->setTRSMatrix(mplayertranslate*msupporttranslate[i]*mshieldtranslate[i]);
	}
}
*/
//----------------------------------------------------------------------------

void UpdateMatrix()
{
	mat4 msupportrotation, mshieldrotation;
	msupportrotation = RotateZ(supportangle);
	mshieldrotation = RotateZ(shieldangle);

	player->setTRSMatrix(player->mplayertranslate*player->mplayerrotation);
	for( int i = 0 ; i < 4 ; i++ ) {
		player->supports[i]->setTRSMatrix(player->mplayertranslate*msupportrotation*player->msupporttranslate[i]);
	}

	for( int i = 0 ; i < 4 ; i++ ) {
		player->shield[i]->setTRSMatrix(player->mplayertranslate*msupportrotation* player->msupporttranslate[i]*mshieldrotation* player->mshieldtranslate[i]);
		mat4 trs = player->mplayertranslate * msupportrotation * player->msupporttranslate[i] * mshieldrotation * player->mshieldtranslate[i];
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
		for( int i = 0 ; i < GRID_SIZE ; i++ ) delete player->supports[i];
		for( int i = 0 ; i < GRID_SIZE ; i++ ) delete player->shield[i];
		delete player;
        exit( EXIT_SUCCESS );
        break;
    }
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch(button) {
		case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
			if ( state == GLUT_DOWN ) ;  
			break;
		case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵 
			if ( state == GLUT_DOWN )  ;
			break;
		case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
			if ( state == GLUT_DOWN )  ; 
			break;
		default:
			break;
	} 
}
float g_fClock = 0;
float l_Clock = 0;
void autoMotion(float dt) {
	if (lol!=nullptr) {
		switch (lol->state) {
			case 0:
				lol->velocity = vec2(0, -1);
				lol->mplayerrotation = RotateZ(lol->rotation);
				lol->setTRSMatrix(lol->mplayertranslate * lol->mplayerrotation);
				if (lol->health <= 0) {
					lol->move(dt);
					lol = nullptr;
					won = true;
				}
				else {
					lol->move(dt);
				}
				break;
			case 1:
				lol->velocity = vec2(0, 0);
				lol->rotation= atan2f((lol->position.y - player->position.y) * dt * 4.0f, (lol->position.x - player->position.x) * dt * 4.0f) * 180 / 3.141592f - 90;
				lol->mplayerrotation = RotateZ(lol->rotation);
				lol->setTRSMatrix(lol->mplayertranslate * lol->mplayerrotation);
				if (lol->health <= 0) {
					lol->move(dt);
					lol = nullptr;
					won = true;
				}
				else {
					lol->move(dt);
					if (lol->state == 2)l_Clock = 12;
				}
				break;
			case 2:
				lol->velocity.x = sinf(360 * l_Clock * 0.02)*15;
				lol->rotation = atan2f((lol->position.y - player->position.y) * dt * 4.0f, (lol->position.x - player->position.x) * dt * 4.0f) * 180 / 3.141592f - 90;
				lol->mplayerrotation = RotateZ(lol->rotation);
				lol->setTRSMatrix(lol->mplayertranslate * lol->mplayerrotation);
				if (lol->health <= 0) {
					lol->move(dt);
					lol = nullptr;
					won = true;
				}
				else {
					lol->move(dt);
				}
				break;
			case 3:
				if (lol->position.x > 10) {
					lol->position.x -= 1;
				}
				if(lol->position.x < -10) {
					lol->position.x += 1;
				}
				lol->velocity.x = sinf(360 * l_Clock * 0.02) * 15;
				lol->velocity.y = sinf(180 * l_Clock * 0.02) * 2;
				lol->rotation = atan2f((lol->position.y - player->position.y) * dt * 4.0f, (lol->position.x - player->position.x) * dt * 4.0f) * 180 / 3.141592f - 90;
				lol->mplayerrotation = RotateZ(lol->rotation);
				lol->setTRSMatrix(lol->mplayertranslate * lol->mplayerrotation);
				if (lol->health <= 0) {
					lol->move(dt);
					lol = nullptr;
					won = true;
				}
				else {
					lol->move(dt);
				}
				break;
		}
	}
	if (player->state==0&&score >= 10) {
		player->state = 1;
		player->b_cooldown -= 0.3;
		player->health += 15;
	}
	if (player->state == 1 && score >= 30) {
		player->state = 2;
		player->b_cooldown -= 0.2;
		player->health += 25;
	}
	player->move(dt);
	player->velocity = vec2(lastx - player->position.x, lasty - player->position.y);
	
	float x, y;
	x = 360 * g_fClock * 0.25;
	y = 360 * g_fClock * 0.25;
	mat4 msupportrotation, mshieldrotation;
	supportangle = x;
	shieldangle = y;
	msupportrotation = RotateZ(supportangle);
	mshieldrotation = RotateZ(shieldangle);
	player->mplayerrotation = RotateZ(player->rotation);
	player->setTRSMatrix(player->mplayertranslate*player->mplayerrotation);
	for (int i = 0; i < 4; i++) {
		player->supports[i]->setTRSMatrix(player->mplayertranslate * msupportrotation * player->msupporttranslate[i]);
	}

	for (int i = 0; i < 4; i++) {
		player->shield[i]->setTRSMatrix(player->mplayertranslate * msupportrotation * player->msupporttranslate[i] * mshieldrotation * player->mshieldtranslate[i]);
		mat4 trs = player->mplayertranslate * msupportrotation * player->msupporttranslate[i] * mshieldrotation * player->mshieldtranslate[i];
		player->shield[i]->position = vec2(trs._m[0].w, trs._m[1].w);
	}

	g_fClock += dt;
	if (g_fClock >= 4.0f) g_fClock -= 4.0f;
	l_Clock += dt;
	if (l_Clock >= 50.0f) l_Clock -= 50.0f;
	CBullet* b_ptr = p_bullet;
	while (b_ptr != nullptr) {
		CBullet* tempptr = b_ptr->next;
		b_ptr->mplayerrotation = RotateZ(b_ptr->rotation);
		b_ptr->setTRSMatrix(b_ptr->mplayertranslate * b_ptr->mplayerrotation);
		if (b_ptr->life - dt < 0 || b_ptr->health <= 0) {
			if (tempptr == nullptr && b_ptr == p_bullet) {
				p_bullet = nullptr;
			}
			else if (tempptr != nullptr && b_ptr == p_bullet) {
				tempptr->previous = nullptr;
				p_bullet = tempptr;
			}
		}
		b_ptr->move(dt);
		b_ptr = tempptr;
	}
	CDonut* d_ptr = don;
	while (d_ptr != nullptr) {
		CDonut* tempptr = d_ptr->next;
		d_ptr->mplayerrotation = RotateZ(d_ptr->rotation);
		d_ptr->setTRSMatrix(d_ptr->mplayertranslate * d_ptr->mplayerrotation);
		if (d_ptr->life - dt < 0 || d_ptr->health <= 0) {
			if (tempptr == nullptr && d_ptr == don) {
				don = nullptr;
			}
			else if (tempptr != nullptr && d_ptr == don) {
				tempptr->previous = nullptr;
				don = tempptr;
			}
		}
		d_ptr->move(dt);
		d_ptr = tempptr;
	}
	CMissle* m_ptr = missle;
	while (m_ptr != nullptr) {
		CMissle* tempptr = m_ptr->next;
		if (lol != nullptr) {
			m_ptr->rotation = atan2f((lol->position.y-m_ptr->position.y) * dt * 4.0f, (lol->position.x-m_ptr->position.x) * dt * 4.0f) * 180 / 3.141592f - 90;
			float degree = m_ptr->rotation - 90;
			if (degree < 90)degree += 360;
			m_ptr->velocity= vec2(cosf(degree / 180 * 3.141592), sinf(degree / 180 * 3.141592));
		}
		m_ptr->mplayerrotation = RotateZ(m_ptr->rotation);
		m_ptr->setTRSMatrix(m_ptr->mplayertranslate * m_ptr->mplayerrotation);
		if (m_ptr->life - dt < 0 || m_ptr->health <= 0) {
			if (tempptr == nullptr && m_ptr == missle) {
				missle = nullptr;
			}
			else if (tempptr != nullptr && m_ptr == missle) {
				tempptr->previous = nullptr;
				missle = tempptr;
			}
		}
		
		m_ptr->move(dt);
		m_ptr = tempptr;
	}
	CBackground* bg_ptr = background;
	while (bg_ptr != nullptr) {
		CBackground* tempptr = bg_ptr->next;
		bg_ptr->mplayerrotation = RotateZ(bg_ptr->rotation);
		bg_ptr->setTRSMatrix(bg_ptr->mplayertranslate * bg_ptr->mplayerrotation);
		if (bg_ptr->life - dt < 0) {
				bg_ptr->previous->next = nullptr;
			if (tempptr == nullptr && bg_ptr == background) {
				background = nullptr;
			}
			else if (tempptr != nullptr && bg_ptr == background) {
				tempptr->previous = nullptr;
				background = tempptr;
			}
		}
		bg_ptr->move(dt);
		bg_ptr = tempptr;
	}
	CIcecream* i_ptr = ice;
	while (i_ptr != nullptr) {
		CIcecream* tempptr = i_ptr->next;
		i_ptr->mplayerrotation = RotateZ(i_ptr->rotation);
		i_ptr->setTRSMatrix(i_ptr->mplayertranslate * i_ptr->mplayerrotation);
		if (i_ptr->life - dt < 0) {
			i_ptr->previous->next = nullptr;
			if (tempptr == nullptr && i_ptr == ice) {
				ice = nullptr;
			}
			else if (tempptr != nullptr && i_ptr == ice) {
				tempptr->previous = nullptr;
				ice = tempptr;
			}
		}
		i_ptr->move(dt);
		i_ptr = tempptr;
	}
	CMarshmellow* ms_ptr = marshe;
	while (ms_ptr != nullptr) {
		CMarshmellow* tempptr = ms_ptr->next;
		ms_ptr->mplayerrotation = RotateZ(ms_ptr->rotation);
		ms_ptr->setTRSMatrix(ms_ptr->mplayertranslate * ms_ptr->mplayerrotation);
		if (ms_ptr->life - dt < 0 || ms_ptr->health <= 0){
			if (tempptr == nullptr && ms_ptr == marshe) {
				marshe = nullptr;
			}
			else if (tempptr != nullptr && ms_ptr == marshe) {
				tempptr->previous = nullptr;
				marshe = tempptr;
			}
			score += 1;
		}
		ms_ptr->rotation = atan2f((ms_ptr->position.y - player->position.y) * dt * 4.0f, (ms_ptr->position.x - player->position.x) * dt * 4.0f) * 180 / 3.141592f - 90;
		ms_ptr->move(dt);
		ms_ptr = tempptr;
	}
	CJelly* j_ptr = jerry;
	while (j_ptr != nullptr) {
		CJelly* tempptr = j_ptr->next;
		j_ptr->mplayerrotation = RotateZ(j_ptr->rotation);
		j_ptr->setTRSMatrix(j_ptr->mplayertranslate * j_ptr->mplayerrotation);
		if (j_ptr->life - dt < 0 || j_ptr->health <= 0) {
			if (tempptr == nullptr && j_ptr == jerry) {
				jerry = nullptr;
			}
			else if (tempptr != nullptr && j_ptr == jerry) {
				tempptr->previous = nullptr;
				jerry = tempptr;
			}
			score += 1;
		}
		j_ptr->move(dt);
		j_ptr = tempptr;
	}
	CCandycane* c_ptr = can;
	while (c_ptr != nullptr) {
		CCandycane* tempptr = c_ptr->next;
		c_ptr->mplayerrotation = RotateZ(c_ptr->rotation);
		c_ptr->setTRSMatrix(c_ptr->mplayertranslate * c_ptr->mplayerrotation);
		if (c_ptr->life - dt < 0 || c_ptr->health <= 0) {
			if (tempptr == nullptr&&c_ptr==can) {
				can = nullptr;
			}
			else if (tempptr != nullptr && c_ptr == can) {
				tempptr->previous = nullptr;
				can = tempptr;
			}
			score += 1;
		}
		c_ptr->rotation = atan2f((c_ptr->position.y - player->position.y) * dt * 4.0f, (c_ptr->position.x - player->position.x) * dt * 4.0f) * 180 / 3.141592f - 90;
		c_ptr->move(dt);
		c_ptr = tempptr;
	}
	CEBullet* eb_ptr = e_bullet;
	while (eb_ptr != nullptr) {
		CEBullet* tempptr = eb_ptr->next;
		eb_ptr->mplayerrotation = RotateZ(eb_ptr->rotation);
		eb_ptr->setTRSMatrix(eb_ptr->mplayertranslate * eb_ptr->mplayerrotation);
		if (eb_ptr->life - dt < 0 || eb_ptr->health <= 0) {
			if (tempptr == nullptr&& eb_ptr == e_bullet) {
				e_bullet = nullptr;
			}
			else if(tempptr != nullptr && eb_ptr == e_bullet){
				tempptr->previous = nullptr;
				e_bullet = tempptr;
			}
		}
		eb_ptr->move(dt);
		eb_ptr = tempptr;
	}
	UpdateMatrix();
}
void generate(float dt){
	bullettimer += dt;
	if (score>=30 && !won && lol == nullptr) {
		lol = new CLollipop;
		lol->position = vec2(0, 18);
		lol->velocity = vec2(0, -6);
		lol->rotation = 0;
		lol->mplayertranslate = Translate(lol->position.x - lol->velocity.x * dt * 3.0f, lol->position.y - lol->velocity.y * dt * 3.0f, 0.0f);
		lol->setTRSMatrix(lol->mplayertranslate * lol->mplayerrotation);
	}
	if (bulletcounter % 2 == 0 && bullettimer > player->b_cooldown) {
		CBackground* tempptr = background;
		if (background == nullptr) {
			background = new CBackground;
			tempptr = background;
		}
		else {
			background->previous = new CBackground;
			background->previous->next = background;
			background = background->previous;
			tempptr = background;
		}
		tempptr->velocity = vec2(0, -1);
		tempptr->mplayertranslate = Translate(tempptr->position.x + tempptr->velocity.x * dt * 6.0f, tempptr->position.y + tempptr->velocity.y * dt * 6.0f, 0.0f);
		tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
	}
	if (bulletcounter % 4 == 1 && bullettimer > player->b_cooldown) {
		CIcecream* tempptr = ice;
		if (ice == nullptr) {
			ice = new CIcecream;
			tempptr = ice;
		}
		else {
			ice->previous = new CIcecream;
			ice->previous->next = ice;
			ice = ice->previous;
			tempptr = ice;
		}
		tempptr->velocity = vec2(0, -1);
		tempptr->mplayertranslate = Translate(tempptr->position.x + tempptr->velocity.x * dt * 6.0f, tempptr->position.y + tempptr->velocity.y * dt * 6.0f, 0.0f);
		tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
	}
	if (player->state>=2&&bulletcounter % 10 == 0 && bullettimer > player->b_cooldown) {
		CMissle* b_ptr = missle;
		CMissle* tempptr = b_ptr;
		while (tempptr != nullptr) {
			b_ptr = tempptr;
			tempptr = b_ptr->next;
		}
		if (missle == nullptr) {
			missle = new CMissle;
			tempptr = missle;
		}
		else {
			b_ptr->next = new CMissle;
			b_ptr->next->previous = b_ptr;
			tempptr = b_ptr->next;
		}
		float degree = player->rotation - 90;
		if (degree < 90)degree += 360;
		tempptr->velocity = vec2(cosf(degree / 180 * 3.141592), sinf(degree / 180 * 3.141592));
		tempptr->position = player->position;
		tempptr->rotation = player->rotation;
		tempptr->mplayertranslate = Translate(tempptr->position.x - tempptr->velocity.x * dt * 3.0f, tempptr->position.y - tempptr->velocity.y * dt * 3.0f, 0.0f);
		tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
	}
	if (player->state >= 1 && bulletcounter % 9 == 3 && bullettimer > player->b_cooldown) {
		CDonut* d_ptr = don;
		CDonut* tempptr = d_ptr;
		while (tempptr != nullptr) {
			d_ptr = tempptr;
			tempptr = d_ptr->next;
		}
		if (don == nullptr) {
			don = new CDonut;
			tempptr = don;
		}
		else {
			d_ptr->next = new CDonut;
			d_ptr->next->previous = d_ptr;
			tempptr = d_ptr->next;
		}
		float degree = player->rotation - 90;
		if (degree < 90)degree += 360;
		tempptr->velocity = vec2(cosf(degree / 180 * 3.141592), sinf(degree / 180 * 3.141592))*1.5;
		tempptr->position = player->position;
		tempptr->rotation = player->rotation;
		tempptr->mplayertranslate = Translate(tempptr->position.x - tempptr->velocity.x * dt * 3.0f, tempptr->position.y - tempptr->velocity.y * dt * 3.0f, 0.0f);
		tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
	}
	if ((bulletcounter % 5 == 0 || (lol != nullptr && lol->state >= 1)) && bullettimer > player->b_cooldown) {
		CMarshmellow* b_ptr = marshe;
		CMarshmellow* tempptr = b_ptr;
		while (tempptr != nullptr) {
			b_ptr = tempptr;
			tempptr = b_ptr->next;
		}
		if (marshe == nullptr) {
			marshe = new CMarshmellow;
			tempptr = marshe;
		}
		else {
			b_ptr->next = new CMarshmellow;
			b_ptr->next->previous = b_ptr;
			tempptr = b_ptr->next;
		}
		tempptr->velocity = vec2(0, -1);
		tempptr->mplayertranslate = Translate(tempptr->position.x - tempptr->velocity.x * dt * 3.0f, tempptr->position.y - tempptr->velocity.y * dt * 3.0f, 0.0f);
		tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
	}
	if ((bulletcounter % 6 == 2||(lol != nullptr && lol->state==2)) && bullettimer > player->b_cooldown) {
		CJelly* b_ptr = jerry;
		CJelly* tempptr = b_ptr;
		while (tempptr != nullptr) {
			b_ptr = tempptr;
			tempptr = b_ptr->next;
		}
		if (jerry == nullptr) {
			jerry = new CJelly;
			tempptr = jerry;
		}
		else {
			b_ptr->next = new CJelly;
			b_ptr->next->previous = b_ptr;
			tempptr = b_ptr->next;
		}
		tempptr->velocity = vec2(0, -1);
		tempptr->mplayertranslate = Translate(tempptr->position.x - tempptr->velocity.x * dt * 3.0f, tempptr->position.y - tempptr->velocity.y * dt * 3.0f, 0.0f);
		tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
	}
	if ((bulletcounter % 7 == 4 || (lol != nullptr && lol->state==3) )&& bullettimer > player->b_cooldown) {
		CCandycane* b_ptr = can;
		CCandycane* tempptr = b_ptr;
		while (tempptr != nullptr) {
			b_ptr = tempptr;
			tempptr = b_ptr->next;
		}
		if (can == nullptr) {
			can = new CCandycane;
			tempptr = can;
		}
		else {
			b_ptr->next = new CCandycane;
			b_ptr->next->previous = b_ptr;
			tempptr = b_ptr->next;
		}
		tempptr->velocity = player->position - tempptr->position;
		tempptr->mplayertranslate = Translate(tempptr->position.x - tempptr->velocity.x * dt * 3.0f, tempptr->position.y - tempptr->velocity.y * dt * 3.0f, 0.0f);
		tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
	}
	if (bullettimer>player->b_cooldown) {
		bullettimer -= player->b_cooldown;
		bulletcounter++;
		CBullet* b_ptr=p_bullet;
		CBullet* tempptr = b_ptr;
		while (tempptr!=nullptr) {
			b_ptr = tempptr;
			tempptr = b_ptr->next;
		}
		if (p_bullet==nullptr) {
			p_bullet = new CBullet;
			tempptr = p_bullet;
		}
		else {
			b_ptr->next = new CBullet;
			b_ptr->next->previous = b_ptr;
			tempptr = b_ptr->next;
		}
		float degree = player->rotation-90;
		if (degree < 90)degree += 360;
		tempptr->velocity =vec2(cosf(degree / 180 * 3.141592), sinf(degree / 180 * 3.141592));
		tempptr->position =  player->position;
		tempptr->rotation = player->rotation;
		tempptr->mplayertranslate=Translate(tempptr->position.x - tempptr->velocity.x * dt * 9.0f, tempptr->position.y - tempptr->velocity.y * dt * 9.0f, 0.0f);
		tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
	}
	CMarshmellow* m_ptr = marshe;
	while (m_ptr !=nullptr) {
		if (m_ptr->timer >= m_ptr->b_cooldown&&m_ptr->position.y>-10.0f) {
			m_ptr->timer = 0;
			CEBullet* tempptr = e_bullet;
			if (e_bullet == nullptr) {
				e_bullet = new CEBullet;
				tempptr = e_bullet;
			}
			else {
				while (tempptr->next != nullptr) {
					tempptr = tempptr->next;
				}
				tempptr->next = new CEBullet;
				tempptr->next->previous = tempptr;
				tempptr = tempptr->next;
			}
			float degree = m_ptr->rotation +90;
			if (degree < 90)degree += 360;
			tempptr->velocity = vec2(cosf(degree / 180 * 3.141592), sinf(degree / 180 * 3.141592));
			tempptr->position = m_ptr->position;
			tempptr->rotation = m_ptr->rotation;
			tempptr->mplayertranslate = Translate(tempptr->position.x - tempptr->velocity.x * dt * 9.0f, tempptr->position.y - tempptr->velocity.y * dt * 9.0f, 0.0f);
			tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
		}
		m_ptr = m_ptr->next;
	}
	CJelly* j_ptr = jerry;
	while (j_ptr != nullptr) {
		if (j_ptr->timer >= j_ptr->b_cooldown && j_ptr->position.y > -10.0f) {
			j_ptr->timer = 0;
			CEBullet* tempptr = e_bullet;
			if (e_bullet == nullptr) {
				e_bullet = new CEBullet;

				tempptr = e_bullet;
			}
			else {
				while (tempptr->next != nullptr) {
					tempptr = tempptr->next;
				}
				tempptr->next = new CEBullet;
				tempptr->next->previous = tempptr;
				tempptr = tempptr->next;
			}
			float degree = j_ptr->rotation + 90;
			if (degree < 90)degree += 360;
			tempptr->velocity = vec2(cosf(degree / 180 * 3.141592) + float(rand() % 5-2)/10, sinf(degree / 180 * 3.141592))/2;
			tempptr->life = tempptr->life * 1.5;
			tempptr->position = j_ptr->position;
			tempptr->rotation = j_ptr->rotation;
			tempptr->mplayertranslate = Translate(tempptr->position.x - tempptr->velocity.x * dt * 9.0f, tempptr->position.y - tempptr->velocity.y * dt * 9.0f, 0.0f);
			tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
		}
		j_ptr = j_ptr->next;
	}
	if (lol!=nullptr&&lol->timer >= lol->b_cooldown && lol->position.y > -10.0f) {
		lol->timer = 0;
		bbcounter += 1;
		CEBullet* tempptr = e_bullet;
		if (e_bullet == nullptr) {
			e_bullet = new CEBullet;

			tempptr = e_bullet;
		}
		else {
			while (tempptr->next != nullptr) {
				tempptr = tempptr->next;
			}
			tempptr->next = new CEBullet;
			tempptr->next->previous = tempptr;
			tempptr = tempptr->next;
		}
		float degree = lol->rotation + 90;
		if (degree < 90)degree += 360;
		tempptr->velocity = vec2(cosf(degree / 180 * 3.141592) + float(rand() % 5 - 2) / 20, sinf(degree / 180 * 3.141592));
		tempptr->life = tempptr->life * 1.5;
		tempptr->position = lol->position;
		tempptr->rotation = lol->rotation;
		tempptr->mplayertranslate = Translate(tempptr->position.x - tempptr->velocity.x * dt * 9.0f, tempptr->position.y - tempptr->velocity.y * dt * 9.0f, 0.0f);
		tempptr->setTRSMatrix(tempptr->mplayertranslate * tempptr->mplayerrotation);
	}
}
void collide(float) {
	CLollipop* l_ptr = lol;
	while (l_ptr != nullptr) {
		if (!l_ptr->hitted) {
			if (!player->hitted && iscollided(l_ptr->position, player->position, l_ptr->radius + player->radius)) {
				player->health -= 1;
				player->hitted = true;
				player->hitcooldown = player->invincibletime;
			}
			CBullet* b_ptr = p_bullet;
			while (b_ptr != nullptr) {
				if (iscollided(l_ptr->position, b_ptr->position, l_ptr->radius + b_ptr->radius)) {
					l_ptr->health -= 1;
					b_ptr->health -= 1;
					l_ptr->hitted = true;
					l_ptr->hitcooldown = l_ptr->invincibletime;
				}
				b_ptr = b_ptr->next;
			}
			CDonut* d_ptr = don;
			while (d_ptr != nullptr) {
				if (iscollided(l_ptr->position, d_ptr->position, l_ptr->radius + d_ptr->radius)) {
					l_ptr->health -= 1;
					d_ptr->health -= 1;
					l_ptr->hitted = true;
					l_ptr->hitcooldown = l_ptr->invincibletime;
					d_ptr->velocity = d_ptr->velocity+normalize(l_ptr->position - d_ptr->position);
				}
				d_ptr = d_ptr->next;
			}
			CMissle* mi_ptr = missle;
			while (mi_ptr != nullptr) {
				if (iscollided(l_ptr->position, mi_ptr->position, l_ptr->radius + mi_ptr->radius)) {
					l_ptr->health -= 1;
					mi_ptr->health -= 1;
				}
				mi_ptr = mi_ptr->next;
			}
		}
		l_ptr = l_ptr->next;
	}
	CJelly* j_ptr = jerry;
	while (j_ptr != nullptr) {
		if (!j_ptr->hitted) {
			if (!player->hitted && iscollided(j_ptr->position, player->position, j_ptr->radius + player->radius)) {
				j_ptr->health -= 1;
				player->health -= 1;
				player->hitted = true;
				j_ptr->hitted = true;
				player->hitcooldown = player->invincibletime;
				j_ptr->hitcooldown = j_ptr->invincibletime;
			}
			for (int i = 0; i < 4; i++) {
				if (iscollided(j_ptr->position, player->shield[i]->position, j_ptr->radius + player->shield[i]->radius)) {
					j_ptr->health -= 1;
					j_ptr->hitted = true;
					j_ptr->hitcooldown = j_ptr->invincibletime;
				}
			}
			CBullet* b_ptr = p_bullet;
			while (b_ptr != nullptr) {
				if (iscollided(j_ptr->position, b_ptr->position, j_ptr->radius + b_ptr->radius)) {
					j_ptr->health -= 1;
					j_ptr->hitted = true;
					j_ptr->hitcooldown = j_ptr->invincibletime;
					b_ptr->health -= 1;
				}
				b_ptr = b_ptr->next;
			}
			CDonut* d_ptr = don;
			while (d_ptr != nullptr) {
				if (iscollided(j_ptr->position, d_ptr->position, j_ptr->radius + d_ptr->radius)) {
					j_ptr->health -= 1;
					d_ptr->health -= 1;
					j_ptr->hitted = true;
					j_ptr->hitcooldown = j_ptr->invincibletime;
					d_ptr->velocity = d_ptr->velocity + normalize(j_ptr->position - d_ptr->position);
				}
				d_ptr = d_ptr->next;
			}
			CMissle* mi_ptr = missle;
			while (mi_ptr != nullptr) {
				if (iscollided(j_ptr->position, mi_ptr->position, j_ptr->radius + mi_ptr->radius)) {
					j_ptr->health -= 1;
					mi_ptr->health -= 1;
				}
				mi_ptr = mi_ptr->next;
			}
		}
		j_ptr = j_ptr->next;
	}
	CCandycane* c_ptr = can;
	while (c_ptr != nullptr) {
		if (!player->hitted && iscollided(c_ptr->position, player->position, c_ptr->radius + player->radius)) {
			c_ptr->health -= 1;
			player->health -= 1;
			player->hitted = true;
			player->hitcooldown = player->invincibletime;
		}
		for (int i = 0; i < 4; i++) {
			if (iscollided(c_ptr->position, player->shield[i]->position, c_ptr->radius + player->shield[i]->radius)) {
				c_ptr->health -= 1;
			}
		}
		CBullet* b_ptr = p_bullet;
		while (b_ptr != nullptr) {
			if (iscollided(c_ptr->position, b_ptr->position, c_ptr->radius + b_ptr->radius)) {
				c_ptr->health -= 1;
				b_ptr->health -= 1;
			}
			b_ptr = b_ptr->next;
		}
		CDonut* d_ptr = don;
		while (d_ptr != nullptr) {
			if (iscollided(c_ptr->position, d_ptr->position, c_ptr->radius + d_ptr->radius)) {
				c_ptr->health -= 1;
				d_ptr->health -= 1;
				c_ptr->hitted = true;
				c_ptr->hitcooldown = c_ptr->invincibletime;
				d_ptr->velocity = d_ptr->velocity + normalize(c_ptr->position - d_ptr->position);
			}
			d_ptr = d_ptr->next;
		}
		CMissle* mi_ptr = missle;
		while (mi_ptr != nullptr) {
			if (iscollided(c_ptr->position, mi_ptr->position, c_ptr->radius + mi_ptr->radius)) {
				c_ptr->health -= 1;
				mi_ptr->health -= 1;
			}
			mi_ptr = mi_ptr->next;
		}
		c_ptr = c_ptr->next;
	}
	CMarshmellow* m_ptr = marshe;
	while (m_ptr != nullptr) {
		if (!player->hitted && iscollided(m_ptr->position, player->position, m_ptr->radius + player->radius)) {
			m_ptr->health -= 1;
			player->health -= 1;
			player->hitted = true;
			player->hitcooldown = player->invincibletime;
		}
		for (int i = 0; i < 4; i++) {
			if (iscollided(m_ptr->position, player->shield[i]->position, m_ptr->radius + player->shield[i]->radius)) {
				m_ptr->health -= 1;
			}
		}
		CBullet* b_ptr = p_bullet;
		while (b_ptr != nullptr) {
			if (iscollided(m_ptr->position, b_ptr->position, m_ptr->radius + b_ptr->radius)) {
				m_ptr->health -= 1;
				b_ptr->health -= 1;
			}
			b_ptr = b_ptr->next;
		}
		CDonut* d_ptr = don;
		while (d_ptr != nullptr) {
			if (iscollided(m_ptr->position, d_ptr->position, m_ptr->radius + d_ptr->radius)) {
				m_ptr->health -= 1;
				d_ptr->health -= 1;
				m_ptr->hitted = true;
				m_ptr->hitcooldown = m_ptr->invincibletime;
				d_ptr->velocity = d_ptr->velocity + normalize(m_ptr->position - d_ptr->position);
			}
			d_ptr = d_ptr->next;
		}
		CMissle* mi_ptr = missle;
		while (mi_ptr != nullptr) {
			if (iscollided(m_ptr->position, mi_ptr->position, m_ptr->radius + mi_ptr->radius)) {
				m_ptr->health -= 1;
				mi_ptr->health -= 1;
			}
			mi_ptr = mi_ptr->next;
		}
		m_ptr = m_ptr->next;
	}
	CEBullet* e_ptr = e_bullet;
	while (e_ptr != nullptr) {
		if (!player->hitted && iscollided(e_ptr->position, player->position, e_ptr->radius + player->radius)) {
			e_ptr->health -= 1;
			player->health -= 1;
			player->hitted = true;
			player->hitcooldown = player->invincibletime;
		}
		for (int i = 0; i < 4; i++) {
			if (iscollided(e_ptr->position, player->shield[i]->position, e_ptr->radius + player->shield[i]->radius)) {
				e_ptr->health -= 1;
			}
		}
		CBullet* b_ptr = p_bullet;
		while (b_ptr != nullptr) {
			if (iscollided(e_ptr->position, b_ptr->position, e_ptr->radius + b_ptr->radius)) {
				e_ptr->health -= 1;
				b_ptr->health -= 1;
			}
			b_ptr = b_ptr->next;
		}
		CDonut* d_ptr = don;
		while (d_ptr != nullptr) {
			if (iscollided(e_ptr->position, d_ptr->position, e_ptr->radius + d_ptr->radius)) {
				e_ptr->health -= 1;
				d_ptr->health -= 1;
				e_ptr->hitted = true;
				e_ptr->hitcooldown = e_ptr->invincibletime;
			}
			d_ptr = d_ptr->next;
		}
		CMissle* mi_ptr = missle;
		while (mi_ptr != nullptr) {
			if (iscollided(e_ptr->position, mi_ptr->position, e_ptr->radius + mi_ptr->radius)) {
				e_ptr->health -= 1;
				mi_ptr->health -= 1;
			}
			mi_ptr = mi_ptr->next;
		}
		e_ptr = e_ptr->next;
	}
	printf("%d", player->health);
}
bool iscollided(vec2 a, vec2 b,float rad) {
	if (powf(a.x - b.x,2) + powf(a.y - b.y,2) < rad*rad) return true;
	else return false;
}
/*
vec2 normalize(vec2 a) {
	float c = sqrtf(powf(a.x, 2) + powf(a.y, 2));
	return vec2(a.x / c, a.y / c);
}
*/
void Win_PassiveMotion(int x, int y) {
	g_fTx = 12.0f * (x - HALF_SIZE) / (HALF_SIZE);
	g_fTy = -12.0f * (y - HALF_SIZE) / (HALF_SIZE);
	translate_player[0] = g_fTx;
	translate_player[1] = g_fTy;
	lastx = g_fTx;
	lasty = g_fTy;
}
// The motion callback for a window is called when the mouse moves within the window while one or more mouse buttons are pressed.
void Win_MouseMotion(int x, int y) {
	g_fTx = 12.0f * (x - HALF_SIZE) / (HALF_SIZE);
	g_fTy = -12.0f * (y - HALF_SIZE) / (HALF_SIZE);
	translate_player[0] = g_fTx;
	translate_player[1] = g_fTy;
	lastx = g_fTx;
	lasty = g_fTy;
}

//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	mat4 rx, ry, rz;
	switch(key) {
		case GLUT_KEY_LEFT:		// 目前按下的是向左方向鍵，移動 Red 往左
			translate_player[0] -= 0.25;
			player->mplayertranslate = Translate(translate_player[0],translate_player[1],translate_player[2]);
			UpdateMatrix();
			break;
		case GLUT_KEY_RIGHT:		// 目前按下的是向右方向鍵，移動 Red 往右
			translate_player[0] += 0.25;
			player->mplayertranslate = Translate(translate_player[0],translate_player[1],translate_player[2]);
			UpdateMatrix();
			break;
		case GLUT_KEY_UP:		// 目前按下的是向右方向鍵，移動 Red 往右
			translate_player[1] += 0.25;
			player->mplayertranslate = Translate(translate_player[0],translate_player[1],translate_player[2]);
			UpdateMatrix();
			break;
		case GLUT_KEY_DOWN:		// 目前按下的是向右方向鍵，移動 Red 往右
			translate_player[1] -= 0.25;
			player->mplayertranslate = Translate(translate_player[0],translate_player[1],translate_player[2]);
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
	glutPassiveMotionFunc(Win_PassiveMotion);
    glutKeyboardFunc( Win_Keyboard );	// 處理 ASCII 按鍵如 A、a、ESC 鍵...等等
	glutSpecialFunc( Win_SpecialKeyboard);	// 處理 NON-ASCII 按鍵如 F1、Home、方向鍵...等等
    glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	
    glutMainLoop();
    return 0;
}
