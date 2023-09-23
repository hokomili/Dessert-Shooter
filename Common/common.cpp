#include <iostream>
#include <cmath>
#include <ctime>
#include "Timer.h"
#include <string.h>
#include "..\GL\glut.h"

#define ORTHO_WIDTH 0

char g_strFPS[9] = "FPS:0000";
int g_ifps;
int g_icount = 0;
double g_ckStart = -1;
double g_felapse;
double g_fprev;

Timer g_Timer;

extern void onFrameMove(float delta);
void displayFSP(int ifps);
void drawText(float x, float y, char *string);

void IdleProcess()
{
	float delta;
	double ckNow; 
	g_icount++;
	if( g_ckStart == -1 ) {
		g_fprev = g_ckStart = g_Timer.getElapsedTimeInMilliSec(); //clock(); //�}�l�p��
		onFrameMove(0);
	}
	else {
		ckNow = g_Timer.getElapsedTimeInMilliSec();
		g_felapse = (ckNow - g_ckStart);
		if( g_felapse >= 1000.0 ) {
			g_ifps = g_icount;
			g_icount = 0;
			g_ckStart += g_felapse;
		}
		delta = (float)((ckNow - g_fprev)/1000.0); // �p�ⶡ�j���ɶ�
		g_fprev = ckNow; // �O���o�����ɶ��A���e�@�����ɶ�
		onFrameMove(delta);
		//printf("%d\n",g_ifps);
	}
	glutPostRedisplay(); // �I�s Rendering ��s�ù�
}

//--------------------------------------------------------------------------------
// �H�U�S���Ψ�A�L���z�|
void drawText(float x, float y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);  // GLUT_BITMAP_TIMES_ROMAN_24
	}
}

void displayFSP(int ifps)
{
	int i;
	
	glColor3f(1.0, 1.0, 1.0);
	i = ifps/1000;
	g_strFPS[4] = i+48;
	ifps = ifps - i*1000;
	i = ifps/100;
	g_strFPS[5] = i+48;
	ifps = ifps - i*100;
	g_strFPS[6] = ifps/10+48;
	g_strFPS[7] = ifps%10+48;
	glColor3f(0.5, 0.8, 0.5);
	drawText(0, ORTHO_WIDTH, g_strFPS);	// �b���w����m�B�A��ܫ��w���r�ꤺ�e
}

//--------------------------------------------------------------------------------