/**********************************************************************

DrawStuff
Release Date: 2010/12/31
Copyright (C) 2010	Zhijie Lee
email: onezeros.lee@gmail.com
web: http://blog.csdn.net/onezeros

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

**********************************************************************/

#include "StdAfx.h"
#include "DrawStuff.h"


enum Aspect { FRONT, BACK, LEFT, RIGHT, UP, DOWN };
enum Color { BLUE, GREEN, RED, ORANGE, WHITE, YELLOW };
const GLubyte colorTable[6][3] = {
	{ 0,0,255 },{ 0,255,0 },{ 255,0,0 },{ 255,102,0 },{ 255,255,255 },{ 255,255,0 }
};

DrawStuff::DrawStuff(void)
{
}

DrawStuff::~DrawStuff(void)
{
}

void DrawStuff::Cube()
{
	//draw cube
	GLint vertices[8][3] = {
		{ -1,-1,-1 },{ 1,-1,-1 },{ -1,-1,1 },{ 1,-1,1 },
		{ -1,1,-1 },{ 1,1,-1 },{ -1,1,1 },{ 1,1,1 }
	};

	//in order:	front ,back ,left  ,right,top,bottom
	GLubyte vertIndex[6][4] = {
		6,2,3,7,
		5,1,0,4,
		4,0,2,6,
		7,3,1,5,
		7,5,4,6,
		2,0,1,3
	};
	for (int i = 0;i<6;i++) {
		glColor3ubv(colorTable[i]);
		glBegin(GL_QUADS);
		for (int j = 0;j<4;j++) {
			glVertex3iv(vertices[vertIndex[i][j]]);
		}
		glEnd();
	}
}

void DrawStuff::Composition()
{
	//a little complicated object
	GLint vertices[8][3] = {
		{ -1,-1,-1 },{ 1,-1,-1 },{ -1,-1,1 },{ 1,-1,1 },
		{ -1,1,-1 },{ 1,1,-1 },{ -1,1,1 },{ 1,1,1 }
	};

	//in order:	front ,back ,left  ,right,top,bottom
	GLubyte vertIndex[6][4] = {
		6,2,3,7,
		5,1,0,4,
		4,0,2,6,
		7,3,1,5,
		7,5,4,6,
		2,0,1,3
	};
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	float translateMat[3][3] = { { 0,0,0 },{ 0,0,2 },{ 0,2,-2 } };
	for (int t = 0;t<3;t++) {
		glTranslatef(translateMat[t][0], translateMat[t][1], translateMat[t][2]);
		for (int i = 0;i<6;i++) {
			glColor3ubv(colorTable[i]);
			glBegin(GL_QUADS);
			for (int j = 0;j<4;j++) {
				glVertex3iv(vertices[vertIndex[i][j]]);
			}
			glEnd();
		}
	}
	glPopMatrix();
}

void DrawStuff::Chessboard()
{
	//chess board
	float latticeLen = 30.0f;
	for (int z = -20;z<20;z++) {
		for (int x = -20;x<20;x++) {
			if ((x + z) % 2) {
				glColor3ub(255, 255, 255);
			}
			else {
				glColor3ub(255, 255, 255);
			}
			glBegin(GL_LINE_STRIP);
			glVertex3f(x*latticeLen, 50, z*latticeLen);
			glVertex3f((x + 1)*latticeLen, 50, z*latticeLen);
			glVertex3f((x + 1)*latticeLen, 50, (z + 1)*latticeLen);
			glVertex3f(x*latticeLen, 50, (z + 1)*latticeLen);
			glEnd();
		}
	}
}

void DrawStuff::asix()
{
	//truc x
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-200.0, -200.0, 0.0);
	glVertex3f(-150.0, -200.0, 0.0);
	glEnd();

	//truc y
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-200.0, -200.0, 0.0);
	glVertex3f(-200.0, -150.0, 0.0);
	glEnd();

	//truc z
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-200.0, -200.0, 0.0);
	glVertex3f(-200.0, -200.0, 50.0);
	glEnd();
}

void DrawStuff::load_stl()
{

	stl[0].Load("Assem1 - part1-1.STL");
	glColor3f(1, 0, 0);
	stl[0].Draw(false, true);

	stl[1].Load("Assem1 - part2-1.STL");
	glColor3f(0, 1, 0);
	stl[1].Draw(false, true);

	stl[2].Load("Assem1 - part3-1.STL");
	glColor3f(0, 0, 1);
	stl[2].Draw(false, true);

	stl[3].Load("Assem1 - part4-1.STL");
	glColor3f(1, 1, 0);
	stl[3].Draw(false, true);
}

void DrawStuff::ve_hinh_tron()
{
	float x, y, z;
	float c1, s1, c2, s2;
	float q1, q2, q3;
	float d1 = 125, a1 = 150, a2 = 150, d3 = 125;
	float t = m_count*pi / 180;;

	x = 200 * cos(t);
	y = 200 * sin(t);
	z = 50;
	//x = 169 * cos(t);
	//y = 100 * sin(t);

	q3 = z - d1 + d3;
	c2 = (((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2));
	s2 = sqrt(1 - (c2*c2));
	q2 = acos((((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2)));

	c1 = (a1*x + a2*(x*cos(q2) + y*sin(q2))) / (x*x + y*y);
	s1 = (a1*y + a2*(y*cos(q2) - x*sin(q2))) / (x*x + y*y);
	q1 = atan2(s1, c1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///////////////////////////////////////////////////////
	//ve khau gia
	glColor3f(0, 0, 1.0);	//mau do
	stl[0].Draw(false, true);//ve khau gia
							 //ve khau 1

	GLfloat *m_01 = new GLfloat[16];

	for (int i = 0; i < 16; i++) 
	{
		m_01[i] = 0;
	}

	m_01[0] = cos(q1);
	m_01[1] = sin(q1);
	m_01[4] = -sin(q1);
	m_01[5] = cos(q1);
	m_01[10] = 1;
	m_01[12] = a1*cos(q1);
	m_01[13] = a1*sin(q1);
	m_01[14] = d1;
	m_01[15] = 1;

	glPushMatrix();
	glMultMatrixf(m_01); //ap dung ma tran bien doi
	glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 0);
	stl[1].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////////////////
	//ve khau 2
	GLfloat *m_02 = new GLfloat[16];
	for (int i = 0; i < 16; i++) 
	{
		m_02[i] = 0;
	}

	m_02[0] = cos(q1 + q2);
	m_02[1] = sin(q1 + q2);
	m_02[4] = -sin(q1 + q2);
	m_02[5] = cos(q1 + q2);
	m_02[10] = 1;
	m_02[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_02[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_02[14] = d1;
	m_02[15] = 1;

	glPushMatrix();
	glMultMatrixf(m_02); //ap dung ma tran bien doi
						 //glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 1);
	stl[2].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////////////////
	//ve khau 3
	GLfloat *m_03 = new GLfloat[16];

	for (int i = 0; i < 16; i++) 
	{
		m_03[i] = 0;
	}

	m_03[0] = cos(q1 + q2);
	m_03[1] = sin(q1 + q2);
	m_03[4] = -sin(q1 + q2);
	m_03[5] = cos(q1 + q2);
	m_03[10] = 1;
	m_03[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_03[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_03[14] = d1 - d3 + q3;
	m_03[15] = 1;

	glPushMatrix();
	glMultMatrixf(m_03); //ap dung ma tran bien doi
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1 + d3);
	glColor3f(0, 1, 0);
	stl[3].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////
	// Draw identation
	if (m_count > 0)
	{
		for (int i = 1; i < m_count; i++)
		{
			float x1, y1, z1, x2, y2, z2, t1, t2;

			t1 = (i - 1)*pi / 180;
			x1 = 200 * cos(t1);
			y1 = 200 * sin(t1);
			z1 = 50;
			/*x1 = 169 * cos(t1);
			y1 = 100 * sin(t1);*/

			t2 = (i)*pi / 180;
			x2 = 200 * cos(t2);
			y2 = 200 * sin(t2);
			z2 = 50;
			/*x2 = 169 * cos(t2);
			y2 = 100 * sin(t2);*/

			glLineWidth(2.0);
			glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 0.0f);//yellow
			glVertex3f(x1, y1, z1);
			glVertex3f(x2, y2, z2);
			glEnd();
		}
	}
}

void DrawStuff::ve_ellipse()
{
	float x, y, z;
	float c1, s1, c2, s2;
	float q1, q2, q3;
	float d1 = 125, a1 = 150, a2 = 150, d3 = 125;
	float t = m_count*pi / 180;;

	z = 50;
	x = 196 * cos(t);
	y = 121 * sin(t);

	q3 = z - d1 + d3;
	c2 = (((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2));
	s2 = sqrt(1 - (c2*c2));
	q2 = acos((((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2)));

	c1 = (a1*x + a2*(x*cos(q2) + y*sin(q2))) / (x*x + y*y);
	s1 = (a1*y + a2*(y*cos(q2) - x*sin(q2))) / (x*x + y*y);
	q1 = atan2(s1, c1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///////////////////////////////////////////////////////
	//ve khau gia
	glColor3f(0, 0, 1.0);	//mau do
	stl[0].Draw(false, true);//ve khau gia
							 //ve khau 1

	GLfloat *m_01 = new GLfloat[16];

	for (int i = 0; i < 16; i++)
	{
		m_01[i] = 0;
	}

	m_01[0] = cos(q1);
	m_01[1] = sin(q1);
	m_01[4] = -sin(q1);
	m_01[5] = cos(q1);
	m_01[10] = 1;
	m_01[12] = a1*cos(q1);
	m_01[13] = a1*sin(q1);
	m_01[14] = d1;
	m_01[15] = 1;

	glPushMatrix();
	glMultMatrixf(m_01); //ap dung ma tran bien doi
	glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 0);
	stl[1].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////////////////
	//ve khau 2
	GLfloat *m_02 = new GLfloat[16];
	for (int i = 0; i < 16; i++)
	{
		m_02[i] = 0;
	}

	m_02[0] = cos(q1 + q2);
	m_02[1] = sin(q1 + q2);
	m_02[4] = -sin(q1 + q2);
	m_02[5] = cos(q1 + q2);
	m_02[10] = 1;
	m_02[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_02[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_02[14] = d1;
	m_02[15] = 1;

	glPushMatrix();
	glMultMatrixf(m_02); //ap dung ma tran bien doi
						 //glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 1);
	stl[2].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////////////////
	//ve khau 3
	GLfloat *m_03 = new GLfloat[16];

	for (int i = 0; i < 16; i++)
	{
		m_03[i] = 0;
	}

	m_03[0] = cos(q1 + q2);
	m_03[1] = sin(q1 + q2);
	m_03[4] = -sin(q1 + q2);
	m_03[5] = cos(q1 + q2);
	m_03[10] = 1;
	m_03[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_03[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_03[14] = d1 - d3 + q3;
	m_03[15] = 1;

	glPushMatrix();
	glMultMatrixf(m_03); //ap dung ma tran bien doi
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1 + d3);
	glColor3f(0, 1, 0);
	stl[3].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////
	// Draw identation
	if (m_count > 0)
	{
		for (int i = 1; i < m_count; i++)
		{
			float x1, y1, z1, x2, y2, z2, t1, t2;

			t1 = (i - 1)*pi / 180;
			z1 = 50;
			x1 = 196 * cos(t1);
			y1 = 121 * sin(t1);

			t2 = (i)*pi / 180;
			z2 = 50;
			x2 = 196 * cos(t2);
			y2 = 121 * sin(t2);

			glLineWidth(2.0);
			glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 0.0f);//yellow
			glVertex3f(x1, y1, z1);
			glVertex3f(x2, y2, z2);
			glEnd();
		}
	}
}

void DrawStuff::ve_heart()
{
	float x, y, z;
	float c1, s1, c2, s2;
	float q1, q2, q3;
	float d1 = 125, a1 = 150, a2 = 150, d3 = 125;
	float t = m_count*pi / 180;;

	z = 50;
	x = 15 * 16 * sin(t)*sin(t)*sin(t);
	y = 15 * (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));

	q3 = z - d1 + d3;
	c2 = (((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2));
	s2 = sqrt(1 - (c2*c2));
	q2 = acos((((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2)));

	c1 = (a1*x + a2*(x*cos(q2) + y*sin(q2))) / (x*x + y*y);
	s1 = (a1*y + a2*(y*cos(q2) - x*sin(q2))) / (x*x + y*y);
	q1 = atan2(s1, c1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///////////////////////////////////////////////////////
	//ve khau gia
	glColor3f(0, 0, 1.0);	//mau do
	stl[0].Draw(false, true);//ve khau gia
							 //ve khau 1

	GLfloat *m_01 = new GLfloat[16];

	for (int i = 0; i < 16; i++)
	{
		m_01[i] = 0;
	}

	m_01[0] = cos(q1);
	m_01[1] = sin(q1);
	m_01[4] = -sin(q1);
	m_01[5] = cos(q1);
	m_01[10] = 1;
	m_01[12] = a1*cos(q1);
	m_01[13] = a1*sin(q1);
	m_01[14] = d1;
	m_01[15] = 1;

	glPushMatrix();
	glMultMatrixf(m_01); //ap dung ma tran bien doi
	glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 0);
	stl[1].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////////////////
	//ve khau 2
	GLfloat *m_02 = new GLfloat[16];
	for (int i = 0; i < 16; i++)
	{
		m_02[i] = 0;
	}

	m_02[0] = cos(q1 + q2);
	m_02[1] = sin(q1 + q2);
	m_02[4] = -sin(q1 + q2);
	m_02[5] = cos(q1 + q2);
	m_02[10] = 1;
	m_02[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_02[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_02[14] = d1;
	m_02[15] = 1;

	glPushMatrix();
	glMultMatrixf(m_02); //ap dung ma tran bien doi
						 //glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 1);
	stl[2].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////////////////
	//ve khau 3
	GLfloat *m_03 = new GLfloat[16];

	for (int i = 0; i < 16; i++)
	{
		m_03[i] = 0;
	}

	m_03[0] = cos(q1 + q2);
	m_03[1] = sin(q1 + q2);
	m_03[4] = -sin(q1 + q2);
	m_03[5] = cos(q1 + q2);
	m_03[10] = 1;
	m_03[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_03[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_03[14] = d1 - d3 + q3;
	m_03[15] = 1;

	glPushMatrix();
	glMultMatrixf(m_03); //ap dung ma tran bien doi
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1 + d3);
	glColor3f(0, 1, 0);
	stl[3].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////
	// Draw identation
	if (m_count > 0)
	{
		for (int i = 1; i < m_count; i++)
		{
			float x1, y1, z1, x2, y2, z2, t1, t2;

			t1 = (i - 1)*pi / 180;
			z1 = 50;
			x1 = 15 * 16 * sin(t1)*sin(t1)*sin(t1);
			y1 = 15 * (13 * cos(t1) - 5 * cos(2 * t1) - 2 * cos(3 * t1) - cos(4 * t1));

			t2 = (i)*pi / 180;
			z2 = 50;
			x2 = 15 * 16 * sin(t2)*sin(t2)*sin(t2);
			y2 = 15 * (13 * cos(t2) - 5 * cos(2 * t2) - 2 * cos(3 * t2) - cos(4 * t2));

			glLineWidth(2.0);
			glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 0.0f);//yellow
			glVertex3f(x1, y1, z1);
			glVertex3f(x2, y2, z2);
			glEnd();
		}
	}
}

void DrawStuff::ve_xoan_ren()
{
	float x, y, z;
	float c1, s1, c2, s2;
	float q1, q2, q3;
	float d1 = 125, a1 = 150, a2 = 150, d3 = 125;
	float a = 15, b = 43, c = 130;
	float t = m_time*pi / 180;

	x = 20 + a*(cos(t) + t*sin(t));
	y = 10 + a*(sin(t) - t*cos(t));
	z = 20 + 3 * t;

	q3 = z - d1 + d3;
	c2 = (((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2));
	s2 = sqrt(1 - (c2*c2));
	q2 = acos((((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2)));

	c1 = (a1*x + a2*(x*cos(q2) + y*sin(q2))) / (x*x + y*y);
	s1 = (a1*y + a2*(y*cos(q2) - x*sin(q2))) / (x*x + y*y);
	q1 = atan2(s1, c1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///////////////////////////////////////////////////////
	//ve khau gia
	glColor3f(0, 0, 1.0);	//mau do
	stl[0].Draw(false, true);//ve khau gia
							 //ve khau 1

	GLfloat *m_01 = new GLfloat[16];
	for (int i = 0; i < 16; i++) 
	{
		m_01[i] = 0;
	}

	m_01[0] = cos(q1);
	m_01[1] = sin(q1);
	m_01[4] = -sin(q1);
	m_01[5] = cos(q1);
	m_01[10] = 1;
	m_01[12] = a1*cos(q1);
	m_01[13] = a1*sin(q1);
	m_01[14] = d1;
	m_01[15] = 1;

	//ve
	glPushMatrix();
	glMultMatrixf(m_01); //ap dung ma tran bien doi
	glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 0);
	stl[1].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////////////////
	//ve khau 2
	GLfloat *m_02 = new GLfloat[16];
	for (int i = 0; i < 16; i++) 
	{
		m_02[i] = 0;
	}

	m_02[0] = cos(q1 + q2);
	m_02[1] = sin(q1 + q2);
	m_02[4] = -sin(q1 + q2);
	m_02[5] = cos(q1 + q2);
	m_02[10] = 1;
	m_02[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_02[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_02[14] = d1;
	m_02[15] = 1;

	//ve
	glPushMatrix();
	glMultMatrixf(m_02); //ap dung ma tran bien doi
						 //glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 1);
	stl[2].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////////////////
	//ve khau 3
	GLfloat *m_03 = new GLfloat[16];
	for (int i = 0; i < 16; i++) 
	{
		m_03[i] = 0;
	}

	m_03[0] = cos(q1 + q2);
	m_03[1] = sin(q1 + q2);
	m_03[4] = -sin(q1 + q2);
	m_03[5] = cos(q1 + q2);
	m_03[10] = 1;
	m_03[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_03[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_03[14] = d1 - d3 + q3;
	m_03[15] = 1;

	//ve
	glPushMatrix();
	glMultMatrixf(m_03); //ap dung ma tran bien doi
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1 + d3);
	glColor3f(0, 1, 0);
	stl[3].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////
	// Draw identation
	if (m_time > 0)
	{
		for (int i = 1; i < m_time; i++)
		{
			float x1, y1, z1, x2, y2, z2, t1, t2;

			t1 = (i - 1)*pi / 180;
			x1 = 20 + a*(cos(t1) + t1*sin(t1));
			y1 = 10 + a*(sin(t1) - t1*cos(t1));
			z1 = 20 + 3 * t1;

			t2 = (i)*pi / 180;
			x2 = 20 + a*(cos(t2) + t2*sin(t2));
			y2 = 10 + a*(sin(t2) - t2*cos(t2));
			z2 = 20 + 3 * t2;

			glLineWidth(2.0);
			glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 0.0f);//yellow
			glVertex3f(x1, y1, z1);
			glVertex3f(x2, y2, z2);
			glEnd();
		}
	}
}

void DrawStuff::Hupocycloid()
{
	float x, y, z;
	float c1, s1, c2, s2;
	float q1, q2, q3;
	float d1 = 125, a1 = 150, a2 = 150, d3 = 125;
	float a = 50 * pi, b = 50, c = 130;
	float t = m_time1*pi / 180;

	x = (a - b)*cos(t) + b*cos(((a / b) - 1)*t);
	y = (a - b)*sin(t) - b*sin(((a / b) - 1)*t);
	z = 50;

	q3 = z - d1 + d3;
	c2 = (((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2));
	s2 = sqrt(1 - (c2*c2));
	q2 = acos((((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2)));

	c1 = (a1*x + a2*(x*cos(q2) + y*sin(q2))) / (x*x + y*y);
	s1 = (a1*y + a2*(y*cos(q2) - x*sin(q2))) / (x*x + y*y);
	q1 = atan2(s1, c1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///////////////////////////////////////////////////////
	//ve khau gia
	glColor3f(0, 0, 1.0);	//mau do
	stl[0].Draw(false, true);//ve khau gia
							 //ve khau 1

	GLfloat *m_01 = new GLfloat[16];
	for (int i = 0; i < 16; i++) 
	{
		m_01[i] = 0;
	}

	m_01[0] = cos(q1);
	m_01[1] = sin(q1);
	m_01[4] = -sin(q1);
	m_01[5] = cos(q1);
	m_01[10] = 1;
	m_01[12] = a1*cos(q1);
	m_01[13] = a1*sin(q1);
	m_01[14] = d1;
	m_01[15] = 1;

	//ve
	glPushMatrix();
	glMultMatrixf(m_01); //ap dung ma tran bien doi
	glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 0);
	stl[1].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////////////////
	//ve khau 2
	GLfloat *m_02 = new GLfloat[16];
	for (int i = 0; i < 16; i++) 
	{
		m_02[i] = 0;
	}

	m_02[0] = cos(q1 + q2);
	m_02[1] = sin(q1 + q2);
	m_02[4] = -sin(q1 + q2);
	m_02[5] = cos(q1 + q2);
	m_02[10] = 1;
	m_02[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_02[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_02[14] = d1;
	m_02[15] = 1;

	//ve
	glPushMatrix();
	glMultMatrixf(m_02); //ap dung ma tran bien doi
						 //glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 1);
	stl[2].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////////////////
	//ve khau 3
	GLfloat *m_03 = new GLfloat[16];
	for (int i = 0; i < 16; i++) 
	{
		m_03[i] = 0;
	}

	m_03[0] = cos(q1 + q2);
	m_03[1] = sin(q1 + q2);
	m_03[4] = -sin(q1 + q2);
	m_03[5] = cos(q1 + q2);
	m_03[10] = 1;
	m_03[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_03[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_03[14] = d1 - d3 + q3;
	m_03[15] = 1;

	//ve
	glPushMatrix();
	glMultMatrixf(m_03); //ap dung ma tran bien doi
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1 + d3);
	glColor3f(0, 1, 0);
	stl[3].Draw(false, true);
	glPopMatrix();

	///////////////////////////////////////////
	// Draw identation
	if (m_time1 > 0)
	{
		for (int i = 1; i < m_time1; i++)
		{
			float x1, y1, z1, x2, y2, z2, t1, t2;

			t1 = (i - 1)*pi / 180;
			x1 = (a - b)*cos(t1) + b*cos(((a / b) - 1)*t1);
			y1 = (a - b)*sin(t1) - b*sin(((a / b) - 1)*t1);
			z1 = 50;

			t2 = (i)*pi / 180;
			x2 = (a - b)*cos(t2) + b*cos(((a / b) - 1)*t2);
			y2 = (a - b)*sin(t2) - b*sin(((a / b) - 1)*t2);
			z2 = 50;

			glLineWidth(2.0);
			glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 0.0f); //yellow
			glVertex3f(x1, y1, z1);
			glVertex3f(x2, y2, z2);
			glEnd();
		}
	}
}

void DrawStuff::Dieu_chinh_robot()
{
	float q1, q2, q3;
	float d1 = 125, a1 = 150, a2 = 150, d3 = 125;

	q1 = (m_q1 + 210)*pi / 180;
	q2 = (m_q2 + 210)*pi / 180;
	q3 = m_q3;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//ve khau gia
	glColor3f(0, 0, 1.0);	//mau do
	stl[0].Draw(false, true);//ve khau gia

							 //ve khau 1
	GLfloat *m_01 = new GLfloat[16];
	for (int i = 0; i < 16; i++) {
		m_01[i] = 0;
	}
	m_01[0] = cos(q1);
	m_01[1] = sin(q1);
	m_01[4] = -sin(q1);
	m_01[5] = cos(q1);
	m_01[10] = 1;
	m_01[12] = a1*cos(q1);
	m_01[13] = a1*sin(q1);
	m_01[14] = d1;
	m_01[15] = 1;

	//ve
	glPushMatrix();
	glMultMatrixf(m_01); //ap dung ma tran bien doi
	glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 0);
	stl[1].Draw(false, true);
	glPopMatrix();
	//ve khau 2
	GLfloat *m_02 = new GLfloat[16];
	for (int i = 0; i < 16; i++) {
		m_02[i] = 0;
	}
	m_02[0] = cos(q1 + q2);
	m_02[1] = sin(q1 + q2);
	m_02[4] = -sin(q1 + q2);
	m_02[5] = cos(q1 + q2);
	m_02[10] = 1;
	m_02[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_02[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_02[14] = d1;
	m_02[15] = 1;

	//ve
	glPushMatrix();
	glMultMatrixf(m_02); //ap dung ma tran bien doi
						 //glTranslatef(-a1, 0, 0); //dua goc khua 2 trung ve khau gia 
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1);
	glColor3f(1, 0, 1);
	stl[2].Draw(false, true);
	glPopMatrix();
	//ve khau 3
	GLfloat *m_03 = new GLfloat[16];
	for (int i = 0; i < 16; i++) {
		m_03[i] = 0;
	}
	m_03[0] = cos(q1 + q2);
	m_03[1] = sin(q1 + q2);
	m_03[4] = -sin(q1 + q2);
	m_03[5] = cos(q1 + q2);
	m_03[10] = 1;
	m_03[12] = a2*cos(q1 + q2) + a1*cos(q1);
	m_03[13] = a2*sin(q1 + q2) + a1*sin(q1);
	m_03[14] = d1 - d3 + q3;
	m_03[15] = 1;

	//ve
	glPushMatrix();
	glMultMatrixf(m_03); //ap dung ma tran bien doi
	glTranslatef(-a2 - a1, 0, 0);
	glTranslatef(0, 0, -d1 + d3);
	glColor3f(0, 1, 0);
	stl[3].Draw(false, true);
	glPopMatrix();

}

void DrawStuff::Draw(int object)
{
	switch (object)
	{
		case COMPOUND:
			Dieu_chinh_robot();
			asix();
			break;
		case CUBE:
			Cube();
			break;
		case ASXIS:
			asix();
			break;
		case LOAD_FILE_STL:
			load_stl();
			asix();
			m_count = 0;
			m_time = 0;
			break;
		case DUONG_TRON:
			ve_hinh_tron();
			asix();
			break;
		case XOAN_REN:
			ve_xoan_ren();
			asix();
			break;
		case TRAI_TIM:
			Hupocycloid();
			asix();
			break;
		case HEART:
			ve_heart();
			asix();
			break;
		case ELLIPSE:
			ve_ellipse();
			asix();
			break;
		default:
			break;
	}
}
