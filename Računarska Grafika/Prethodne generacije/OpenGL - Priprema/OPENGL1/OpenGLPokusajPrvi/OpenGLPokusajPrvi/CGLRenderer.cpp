#include "stdafx.h"
#include "CGLRenderer.h"

#include <gl/GL.h>
#include <gl/GLU.h>


CGLRenderer::CGLRenderer()
{
	rotacija = -45;
	rotacija2 = 0;
	rotacija3 = 0;
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24; //ne 32, to je greska na slajd
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
	if (nPixelFormat == 0)
		return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult)
		return false;

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc)
		return false;

	return true;
}

void CGLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	wglMakeCurrent(NULL, NULL);

}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);

	wglMakeCurrent(NULL, NULL);

	if (this->m_hrc)
	{
		wglDeleteContext(this->m_hrc);
		this->m_hrc = NULL;
	}

}
void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(40, (double)w / (double)h, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);

	wglMakeCurrent(NULL, NULL);   
}
//// /// /// /// /// /// /// /// /// /// /// /// /// ///
void CGLRenderer::DrawScene(CDC* pDC)
{
	
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
///*
	glTranslatef(0.0, -7.0, -45.0);
	glRotatef(20.0, 1.0, 0.0, 0.0);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	//k.sis.
	glBegin(GL_LINES);
	//drawGrid(20, 5);

	glLineWidth(10.0f);
	glColor3f(1, 0, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 19.0);
	glVertex3f(0.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 18.0, 0.0);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(19.0, 0.0, 0.0);

	glEnd();

	//crtanje
	glColor3f(0.5f, 0.35f, 0.05f);
	glTranslatef(0.0, -0.5, 0.0);
	Valjak(pDC, 3, 4, 6);
	glTranslatef(0.0, 2.5, 0.0);
	Valjak(pDC, 4, 2, 8);
	glTranslatef(0.0, 1.0, 0.0);

	glColor3f(0.2f, 1.0f, 0.3f);

	///////////////////////////////
	
	glTranslatef(0.0, 1.0, 0.0);
	Valjak(pDC, 1.5, 2.5, 4);
	glTranslatef(0.0, 1.0, 0.0);

	glTranslatef(0.0, 2.9, 0.0);
	Sfera(pDC, 1);
	glTranslatef(0.0, 1.0, 0.0);

	////////////////////////////////////
	glPushMatrix();

	glRotatef(-45, 0.0, 0.0, 1.0);

	glTranslatef(0.5, 0.8, -2.0);
	Kupa(pDC, 1.3, 3.2, 6);
	glTranslatef(0.0, 1.5, 0.0);


	glTranslatef(0.0, 1.0, 0.0);
	Sfera(pDC, 1);
	glTranslatef(0.0, 1.0, 0.0);


	glTranslatef(0.0, 0.3, 0.0);
	Valjak(pDC, 1.5, 2.5, 4);
	glTranslatef(0.0, 1.0, 0.0);

	glTranslatef(0.0, 2.9, 0.0);
	Sfera(pDC, 1);
	glTranslatef(0.0, 1.0, 0.0);

	glPopMatrix();

	////////////////////////////////
	glPushMatrix();

	glRotatef(45, 0.0, 0.0, 1.0);

	glTranslatef(0.0, 1.5, 1.0);
	Kupa(pDC, 1.3, 3.2, 6);
	glTranslatef(0.0, 1.5, 0.0);


	glTranslatef(0.0, 1.0, 0.0);
	Sfera(pDC, 1);
	glTranslatef(0.0, 1.0, 0.0);

	glPushMatrix();
	///////////////////////////////// zuta kupa dobro
	//glRotatef(rotacija, 0.0, 0.0, 1.0);
	glRotatef(rotacija3, 0.0, 0.0, 1.0);
	glRotatef(rotacija2, 0.0, 1.0, 0.0);
	glRotatef(rotacija, 0.0, 0.0, 1.0);
	glColor3f(1.0f, 1.0f, 0.5f);
	glTranslatef(1.0, 1.7, 0.0);
	Kupa(pDC, 1, 3, 50);
	glTranslatef(0.0, 1.5, 0.0);

	glColor3f(0.2f, 1.0f, 0.3f);
	glTranslatef(0.0, 1.0, 0.0);
	Sfera(pDC, 1);
	glTranslatef(0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	Valjak(pDC, 1, 2, 4);
	glTranslatef(0.0, 2.0, 0.0);

	glTranslatef(0.0, 1.0, 0.0);
	Sfera(pDC, 1);
	glPopMatrix();


	glPushMatrix();
	glRotatef(45, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 1.7, 1.0);
	Kupa(pDC, 1, 3, 50);
	glTranslatef(0.0, 2.0, 0.0);

	glTranslatef(0.0, 0.5, 0.0);
	Sfera(pDC, 1);
	glPopMatrix();

	glTranslatef(1.0, 0.0, 0.0);
	glRotatef(-50, 0.0, 0.0, 1.0);
	Valjak(pDC, 1, 2, 4);
	glTranslatef(0.0, 2.0, 0.0);

	glTranslatef(0.0, 1.0, 0.0);
	Sfera(pDC, 1);
	
	glPopMatrix();

	///////////////////////////////////////////// dobro

	glPushMatrix();
	glTranslatef(0.0, 0.5, 0.0);
	
	Valjak(pDC, 1, 2, 4);
	glTranslatef(0.0, 2.0, 0.0);

	glTranslatef(0.0, 1.0, 0.0);
	Sfera(pDC, 1);
	glPopMatrix();

	
	///////////////////////////////////////// dobro
	glRotatef(45, 0.0, 0.0, 1.0);

	glPushMatrix();

	glTranslatef(0.0, 0.0, 1.0);
	Valjak(pDC, 1, 2, 4);
	glTranslatef(0.0, 1.0, 0.0);

	glTranslatef(0.0, 2.5, 0.0);
	Sfera(pDC, 1);
	glTranslatef(0.0, 1.5, 0.0);

	Valjak(pDC, 1, 2, 4);
	

	glTranslatef(0.0, 3.5, 0.0);
	Sfera(pDC, 1);
	glTranslatef(0.0, 1.0, 0.0);

	glPopMatrix();

	////////////////////////////////////////

	glFlush();

	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Kocka(CDC* pDC, float a)
{

	glBegin(GL_QUADS);
	// back
	//glColor3f(0.70f, 0.70f, 0.70f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(a / 2, a / 2, -a / 2);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glVertex3f(-a / 2, a / 2, -a / 2);

	glEnd();
	glBegin(GL_QUADS);
	// top
	glColor3f(0.70f, 0.70f, 0.70f);

	float v1[3];
	float v2[3];
	float* nor;
	nor = new float[3];
	v1[0] = -a / 2; v1[1] = 0; v1[2] = a / 2;
	v2[0] = a / 2; v2[1] = 0; v2[2] = a / 2;
	nor = normcrossprod(v1, v2, nor);

	glNormal3fv(nor);

	//top
	//glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-a / 2, a / 2, a / 2);
	glVertex3f(a / 2, a / 2, a / 2);
	glVertex3f(a / 2, a / 2, -a / 2);
	glVertex3f(-a / 2, a / 2, -a / 2);

	glEnd();
	glBegin(GL_QUADS);
	// bottom
	glColor3f(0.70f, 0.70f, 0.70f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(a / 2, -a / 2, a / 2);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glVertex3f(a / 2, -a / 2, -a / 2);

	glEnd();

	glBegin(GL_QUADS);
	// right
	glColor3f(0.70f, 0.70f, 0.70f);
	glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(a / 2, a / 2, -a / 2);
	glVertex3f(a / 2, a / 2, a / 2);
	glVertex3f(a / 2, -a / 2, a / 2);
	glVertex3f(a / 2, -a / 2, -a / 2);

	glEnd();

	glBegin(GL_QUADS);
	// left
	glColor3f(0.70f, 0.70f, 0.70f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glVertex3f(-a / 2, a / 2, a / 2);
	glVertex3f(-a / 2, a / 2, -a / 2);
	glVertex3f(-a / 2, -a / 2, -a / 2);

	glEnd();

	glBegin(GL_QUADS);
	// front
	glColor3f(0.70f, 0.70f, 0.70f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(a / 2, -a / 2, a / 2);
	glVertex3f(a / 2, a / 2, a / 2);
	glVertex3f(-a / 2, a / 2, a / 2);
	glVertex3f(-a / 2, -a / 2, a / 2);

	glEnd();
	
	glEnable(GL_NORMALIZE);

}
void CGLRenderer::Sfera(CDC* pDC, float r)
{
	int n = 100;
	float obim = 2.0 * r * 3.14;
	float l = obim / (float)n / 2;

	glPushMatrix();
	for (int j = 0; j < n; j++)
	{
		glRotatef((360.0 / (float)n), 0.0, 0.0, 1.0);

		for (int i = 0; i < n; i++)
		{
			glRotatef((360.0 / (float)n), 0.0, 1.0, 0);

			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(l, -l, r);
			glVertex3f(l, l, r);
			glVertex3f(-l, l, r);
			glVertex3f(-l, -l, r);
			glEnd();
		}
	}
	glPopMatrix();
}

float* CGLRenderer::normcrossprod(float v1[3], float v2[3], float out[3])
{
	GLint i, j;
	GLfloat length;
	out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	out[2] = v1[0] * v2[1] - v1[1] * v2[0];
	normalize(out);
	return out;
}
void CGLRenderer::normalize(float v[3]) {
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d == 0.0) {
		return;
	}
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
}

void CGLRenderer::Valjak(CDC* pDC, float r, float visina, int brDelova)
{
	glPushMatrix();

	float* vectorX, *vectorZ;
	vectorX = new float[brDelova];
	vectorZ = new float[brDelova];

	float pomeraj = 360 / brDelova;
	float toRad = 3.14 / 180;
	//donja osnova
	for (int i = 0; i < brDelova; i++)
	{
		vectorX[i] = r * cos(pomeraj * i * toRad);
		vectorZ[i] = r * sin(pomeraj * i * toRad);
	}
	glBegin(GL_POLYGON);

	glNormal3f(0.0, -1.0, 0.0);

	for (int i = 0; i < brDelova; i++)
	{
		glVertex3f(vectorX[i], 0.0, vectorZ[i]);
	}
	glEnd();

	glTranslatef(0, visina, 0);

	glBegin(GL_POLYGON);
	//gornja osnova
	glNormal3f(0.0, 1.0, 0.0);
	for (int i = 0; i < brDelova; i++)
	{
		glVertex3f(vectorX[i], 0.0, vectorZ[i]);
	}

	glEnd();

	//omotac
	glBegin(GL_QUADS);
	for (int i = 0; i < brDelova; i++)
	{
		float v1[3], v2[3];
	
		glPushMatrix();

		glTranslatef(vectorX[i], 0, vectorZ[i]);

		v1[0] = 0; v1[1] = -visina; v1[2] = 0;
		if (i != brDelova - 1)
		{
			v2[0] = vectorX[i + 1]; v2[1] = 0; v2[2] = vectorZ[i + 1];
		}
		else
		{
			
			v2[0] = vectorX[0]; v2[1] = 0; v2[2] = vectorZ[0];
		}
		float* norm = new float[3];
		norm = this->normcrossprod(v1, v2, norm);
		glNormal3fv(norm);
		glPopMatrix();

		if (i != brDelova - 1)
		{
			glVertex3f(vectorX[i], 0, vectorZ[i]);
			glVertex3f(vectorX[i], -visina, vectorZ[i]);
			glVertex3f(vectorX[i + 1], -visina, vectorZ[i + 1]);
			glVertex3f(vectorX[i + 1], 0, vectorZ[i + 1]);
		}
		else
		{
			glVertex3f(vectorX[i], 0, vectorZ[i]);
			glVertex3f(vectorX[i], -visina, vectorZ[i]);
			glVertex3f(vectorX[0], -visina, vectorZ[0]);
			glVertex3f(vectorX[0], 0, vectorZ[0]);
		}
	}
	glEnd();

	glPopMatrix();
}
void CGLRenderer::Kupa(CDC* pDC, float baza, float visina, int n)
{
	glPushMatrix();
	glTranslatef(0, -visina / 2, 0);

	double angle = 360 / n;

	float* x = new float[n];
	float* y = new float[n];

	float toRad = 3.14 / 180;

	//baza,  je pp
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	for (int i = 0; i < n; i++)
	{
		x[i] = baza * cos((i * angle) * toRad);
		y[i] = baza * sin((i * angle) * toRad);

		glVertex3f(x[i], 0.0, y[i]);
	}
	glEnd();

	//omotac
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, visina, 0.0);

	for (int i = 0; i < n; i++)
	{
		float v1[3];
		float v2[3];
		float* nor;
		nor = new float[3];
		v1[0] = 0; v1[1] = visina; v1[2] = 0;
		v2[0] = x[i]; v2[1] = 0; v2[2] = y[i];
		nor = normcrossprod(v1, v2, nor);

		glNormal3fv(nor);

		glVertex3f(x[i], 0, y[i]);
	}
	
	float v1[3];
	float v2[3];
	float* nor;
	nor = new float[3];
	v1[0] = 0; v1[1] = visina; v1[2] = 0;
	v2[0] = x[0]; v2[1] = 0; v2[2] = y[0];
	nor = normcrossprod(v1, v2, nor);

	glNormal3fv(nor);
	glVertex3f(x[0], 0, y[0]);
	glEnd();

	glPopMatrix();
}



void drawGrid(int size, int nbSubdivisions)
{
	GLboolean lighting;
	glGetBooleanv(GL_LIGHTING, &lighting);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	for (int i = 0; i <= nbSubdivisions; ++i) {
		const float pos = size * (2.0 * i / nbSubdivisions - 1.0);
		glVertex2d(pos, -size);
		glVertex2d(pos, +size);
		glVertex2d(-size, pos);
		glVertex2d(size, pos);
	}
	glEnd();
	if (lighting)
		glEnable(GL_LIGHTING);

}
