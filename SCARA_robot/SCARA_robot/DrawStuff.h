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

#pragma once
#include "stdafx.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "STL_File.h"
#define pi 3.1414159265f

class DrawStuff
{
public:
	int m_count;
	int m_time;
	int m_time1;
	int m_q1 = 0;
	int m_q2 = 0;
	int m_q3 = 0;
	//float x=0, y=0, z=0;


	CSTL_File stl[4];//khai bao mang so phan tu khau
	DrawStuff(void);
	~DrawStuff(void);
	void Draw(int object);
	void Cube();
	void Composition();
	void Chessboard();
	void load_stl();
	void ve_hinh_tron();
	void ve_heart();
	void ve_ellipse();
	void asix();
	void ve_xoan_ren();
	void Hupocycloid();
	void Dieu_chinh_robot();
};
