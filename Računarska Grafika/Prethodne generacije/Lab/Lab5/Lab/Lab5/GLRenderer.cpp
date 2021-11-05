#include "pch.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
//#pragma comment(lib, "GL\\glut32.lib")
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif // !_USE_MATH_DEFINES
#include <math.h>
#include "GLMaterial.h"

CGLRenderer::CGLRenderer()
{
	firstMouse = true;
	camX = 5.4;
	camY = 10.5;
	camZ = 0.0;
	camYaw = 0.0f;
	cameraDistanceFromCoordinateOrigin = sqrt(pow(camX, 2) + pow(camY, 2));
	cameraPitch = asin(camY / cameraDistanceFromCoordinateOrigin) * 180 / M_PI;
	camY *= 1.4;
	normalsOn = true;
	crvenoSvetlo = true;
	zelenoSvetlo = true;
	plavoSvetlo = true;
}

CGLRenderer::~CGLRenderer(void)
{
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
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc) return false;

	return true;
}

void CGLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glLoadIdentity();

	gluLookAt(camX, camY, camZ,
		0.0, 6.0, 0.0,
		0.0, 1.0, 0.0);

	glPushMatrix();
	DrawSvetlo();
	glPopMatrix();

	SetRoomLightning();
	DrawCoordinateLines();
	DrawRoom();
	DrawBase();
	glTranslatef(0.0f, 1.5f, 0.0f);

	DrawVase();

	glFlush();
	//---------------------------------
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	double aspect = (double)w / (double)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::MoveCamera(CPoint cursorPoint) // https://learnopengl.com/Getting-started/Camera
{
	if (firstMouse)
	{
		lastPoint.x = cursorPoint.x;
		lastPoint.y = cursorPoint.y;
		firstMouse = false;
	}

	float xoffset = lastPoint.x - cursorPoint.x; // moving left moves camera to the right
	float yoffset = cursorPoint.y - lastPoint.y; // moving up moves camera down (mouse y grows going down)
	lastPoint.x = cursorPoint.x;
	lastPoint.y = cursorPoint.y;

	float sensitivity = 0.5f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camYaw += xoffset;
	cameraPitch += yoffset;

	if (cameraPitch > 89.0f)
		cameraPitch = 89.0f;
	if (cameraPitch < -89.0f)
		cameraPitch = -89.0f;

	double xPos = cos(camYaw * M_PI / 180.0) * cos(cameraPitch * M_PI / 180.0);
	double yPos = sin(cameraPitch * M_PI / 180.0);
	double zPos = -sin(camYaw * M_PI / 180.0) * cos(cameraPitch * M_PI / 180.0);
	camX = 0.9 * cameraDistanceFromCoordinateOrigin * xPos;
	if (camX >= 10.0f)
		camX = 9.5f;
	camY = 1.4 * cameraDistanceFromCoordinateOrigin * yPos;
	camZ = cameraDistanceFromCoordinateOrigin * zPos;
}

void CGLRenderer::StopMovingCamera()
{
	firstMouse = true;
}

void CGLRenderer::PromeniNormale()
{
	normalsOn = !normalsOn;
}

void CGLRenderer::PromeniCrvenoSvetlo()
{
	crvenoSvetlo = !crvenoSvetlo;
}

void CGLRenderer::PromeniZelenoSvetlo()
{
	zelenoSvetlo = !zelenoSvetlo;
}

void CGLRenderer::PromeniPlavoSvetlo()
{
	plavoSvetlo = !plavoSvetlo;
}

int CGLRenderer::mod(int k, int n) { return ((k %= n) < 0) ? k + n : k; }

void CGLRenderer::DrawBase()
{
	GLMaterial sphereMat;
	sphereMat.SetAmbient(0.7f, 0.7f, 0.7f, 1.0f);
	sphereMat.SetDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	sphereMat.SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);

	sphereMat.SelectFront();
	DrawHalfSphere(2.0f);
}

void CGLRenderer::DrawHalfSphere(float r)
{
	glBegin(GL_QUAD_STRIP);
	for (float alpha = 0.0f; alpha < 90.0f; alpha++)
	{
		double alphaRadians = alpha * M_PI / 180.0;
		double alphaPlusOneRadians = (alpha + 1.0) * M_PI / 180.0;

		for (float beta = 0.0f; beta <= 360.0f; beta++)
		{
			double betaRadians = beta * M_PI / 180.0;

			float x1 = r * cos(alphaRadians) * cos(betaRadians);
			float y1 = r * sin(alphaRadians);
			float z1 = r * cos(alphaRadians) * sin(betaRadians);

			float normal1X = cos(betaRadians);
			float normal1Y = sin(alphaRadians);
			float normal1Z = sin(betaRadians);

			float x2 = r * cos(alphaPlusOneRadians) * cos(betaRadians);
			float y2 = r * sin(alphaPlusOneRadians);
			float z2 = r * cos(alphaPlusOneRadians) * sin(betaRadians);

			float normal2X = cos(betaRadians);
			float normal2Y = sin(alphaPlusOneRadians);
			float normal2Z = sin(betaRadians);

			glNormal3f(normal1X, normal1Y, normal1Z);
			glVertex3f(x1, y1, z1);

			glNormal3f(normal2X, normal2Y, normal2Z);
			glVertex3f(x2, y2, z2);
		}
	}
	glEnd();
}

void CGLRenderer::DrawRoom()
{
	DrawLeviZid();
	DrawPrednjiZid();
	DrawDesniZid();
	DrawZadnjiZid();
	DrawGornjiZid();
	DrawDonjiZid();
}



void CGLRenderer::DrawDesniZid()
{
	float side = 20.0f;
	u_short resolution = 100;
	float topLeftX = -10.0f;
	float topLeftY = 20.0f;
	float topLeftZ = -10.0f;
	GLMaterial wallMat;
	wallMat.SetAmbient(0.8f, 0.8f, 0.8f, 1.0f);
	wallMat.SetDiffuse(0.8f, 0.8f, 0.8f, 1.0f);

	float step = side / resolution;

	wallMat.SelectFront();
	glBegin(GL_QUADS);
	{
		for (u_short i = 0; i < resolution; i++)
		{
			for (u_short j = 0; j < resolution; j++)
			{
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f(topLeftX + step * j, topLeftY - step * i, topLeftZ);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f(topLeftX + step * (j + 1), topLeftY - step * i, topLeftZ);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f(topLeftX + step * (j + 1), topLeftY - step * (i + 1), topLeftZ);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f(topLeftX + step * j, topLeftY - step * (i + 1), topLeftZ);
			}
		}
	}
	glEnd();
}

void CGLRenderer::DrawZadnjiZid()
{
	float side = 20.0f;
	u_short resolution = 100;
	float topLeftX = 10.0f;
	float topLeftY = 20.0f;
	float topLeftZ = -10.0f;
	GLMaterial wallMat;
	wallMat.SetAmbient(0.8f, 0.8f, 0.8f, 1.0f);
	wallMat.SetDiffuse(0.8f, 0.8f, 0.8f, 1.0f);

	float step = side / resolution;

	wallMat.SelectFront();
	glBegin(GL_QUADS);
	{
		for (u_short i = 0; i < resolution; i++)
		{
			for (u_short j = 0; j < resolution; j++)
			{
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glVertex3f(topLeftX, topLeftY - step * i, topLeftZ + step * j);
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glVertex3f(topLeftX, topLeftY - step * i, topLeftZ + step * (j + 1));
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glVertex3f(topLeftX, topLeftY - step * (i + 1), topLeftZ + step * (j + 1));
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glVertex3f(topLeftX, topLeftY - step * (i + 1), topLeftZ + step * j);
			}
		}
	}
	glEnd();
}

void CGLRenderer::DrawLeviZid()
{
	float side = 20.0f;
	u_short resolution = 100;
	float topLeftX = 10.0f;
	float topLeftY = 20.0f;
	float topLeftZ = 10.0f;
	GLMaterial wallMat;
	wallMat.SetAmbient(0.8f, 0.8f, 0.8f, 1.0f);
	wallMat.SetDiffuse(0.8f, 0.8f, 0.8f, 1.0f);

	float step = side / resolution;

	wallMat.SelectFront();
	glBegin(GL_QUADS);
	{
		for (u_short i = 0; i < resolution; i++)
		{
			for (u_short j = 0; j < resolution; j++)
			{
				glNormal3f(0.0f, 0.0f, -1.0f);
				glVertex3f(topLeftX - step * j, topLeftY - step * i, topLeftZ);
				glNormal3f(0.0f, 0.0f, -1.0f);
				glVertex3f(topLeftX - step * (j + 1), topLeftY - step * i, topLeftZ);
				glNormal3f(0.0f, 0.0f, -1.0f);
				glVertex3f(topLeftX - step * (j + 1), topLeftY - step * (i + 1), topLeftZ);
				glNormal3f(0.0f, 0.0f, -1.0f);
				glVertex3f(topLeftX - step * j, topLeftY - step * (i + 1), topLeftZ);
			}
		}
	}
	glEnd();
}

void CGLRenderer::DrawPrednjiZid()
{
	float side = 20.0f;
	u_short resolution = 100;
	float topLeftX = -10.0f;
	float topLeftY = 20.0f;
	float topLeftZ = 10.0f;
	GLMaterial wallMat;
	wallMat.SetAmbient(0.8f, 0.8f, 0.8f, 1.0f);
	wallMat.SetDiffuse(0.8f, 0.8f, 0.8f, 1.0f);

	float step = side / resolution;

	wallMat.SelectFront();
	glBegin(GL_QUADS);
	{
		for (u_short i = 0; i < resolution; i++)
		{
			for (u_short j = 0; j < resolution; j++)
			{
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3f(topLeftX, topLeftY - step * i, topLeftZ - step * j);
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3f(topLeftX, topLeftY - step * i, topLeftZ - step * (j + 1));
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3f(topLeftX, topLeftY - step * (i + 1), topLeftZ - step * (j + 1));
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3f(topLeftX, topLeftY - step * (i + 1), topLeftZ - step * j);
			}
		}
	}
	glEnd();
}

void CGLRenderer::DrawGornjiZid()
{
	float side = 20.0f;
	u_short resolution = 100;
	float topLeftX = 10.0f;
	float topLeftY = 20.0f;
	float topLeftZ = 10.0f;
	GLMaterial wallMat;
	wallMat.SetAmbient(0.3f, 0.3f, 0.3f, 1.0f);
	wallMat.SetDiffuse(0.3f, 0.3f, 0.3f, 1.0f);

	float step = side / resolution;

	wallMat.SelectFront();
	glBegin(GL_QUADS);
	{
		for (u_short i = 0; i < resolution; i++)
		{
			for (u_short j = 0; j < resolution; j++)
			{
				glNormal3f(0.0f, -1.0f, 0.0f);
				glVertex3f(topLeftX - step * i, topLeftY, topLeftZ - step * j);
				glNormal3f(0.0f, -1.0f, 0.0f);
				glVertex3f(topLeftX - step * i, topLeftY, topLeftZ - step * (j + 1));
				glNormal3f(0.0f, -1.0f, 0.0f);
				glVertex3f(topLeftX - step * (i + 1), topLeftY, topLeftZ - step * (j + 1));
				glNormal3f(0.0f, -1.0f, 0.0f);
				glVertex3f(topLeftX - step * (i + 1), topLeftY, topLeftZ - step * j);
			}
		}
	}
	glEnd();
}

void CGLRenderer::DrawDonjiZid()
{
	float side = 20.0f;
	u_short resolution = 100;
	float topLeftX = -10.0f;
	float topLeftY = 0.0f;
	float topLeftZ = 10.0f;
	GLMaterial wallMat;
	wallMat.SetAmbient(0.7f, 0.7f, 0.7f, 1.0f);
	wallMat.SetDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	float step = side / resolution;

	wallMat.SelectFront();
	glBegin(GL_QUADS);
	{
		for (u_short i = 0; i < resolution; i++)
		{
			for (u_short j = 0; j < resolution; j++)
			{
				glNormal3f(0.0f, 1.0f, 0.0f);
				glVertex3f(topLeftX + step * i, topLeftY, topLeftZ - step * j);
				glNormal3f(0.0f, 1.0f, 0.0f);
				glVertex3f(topLeftX + step * i, topLeftY, topLeftZ - step * (j + 1));
				glNormal3f(0.0f, 1.0f, 0.0f);
				glVertex3f(topLeftX + step * (i + 1), topLeftY, topLeftZ - step * (j + 1));
				glNormal3f(0.0f, 1.0f, 0.0f);
				glVertex3f(topLeftX + step * (i + 1), topLeftY, topLeftZ - step * j);
			}
		}
	}
	glEnd();
}



void CGLRenderer::DrawVase()
{
	GLfloat mat_amb[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_dif[] = { 0.84, 0.84, 0.84, 1.0 };
	GLfloat mat_emm[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_spec[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shin = 0.0;
	GLMaterial tableMaterial(mat_amb, mat_dif, mat_spec, mat_emm, mat_shin);

	mat_amb[0] = mat_amb[1] = 0.36; mat_amb[2] = 0.55;
	mat_dif[0] = mat_dif[1] = 0.56; mat_dif[2] = 0.84;
	mat_spec[0] = mat_spec[1] = mat_spec[2] = 0.2;
	mat_shin = 112.0;
	GLMaterial lightVasePartMaterial(mat_amb, mat_dif, mat_spec, mat_emm, mat_shin);


	mat_dif[0] = mat_dif[1] = 0.39; mat_dif[2] = 0.84;
	mat_amb[0] = mat_amb[1] = 0.25; mat_amb[2] = 0.54;
	mat_spec[0] = mat_spec[1] = mat_spec[2] = 0.2;
	mat_shin = 112.0;
	GLMaterial darkVasePartMaterial(mat_amb, mat_dif, mat_spec, mat_emm, mat_shin);

	double green[3] = { 0.0, 0.8, 0.0 };

	glPushMatrix();


	glTranslatef(0, 1.5, 0);
	DrawCylinder(12, 3, 1, green);

	glTranslatef(0, 1.5, 0);
	glPushMatrix();
	glRotatef(45, 0, 1.0, 0);
	DrawPrism(4, 1, 3.5, green);
	glPopMatrix();

	double partLen = 0.6;
	double angle = piconst / 4;
	double angleCos = cos(angle);
	double angleSin = sin(angle);
	double radius = 1.7;
	double upperPtXDist = partLen * angleCos;
	double upperPtYDist = partLen * angleSin;

	//svetli delovi vaze
	glPushMatrix();
	lightVasePartMaterial.Select();
	glTranslatef(0, 0.5, 0);
	DrawConePart(32, angle, partLen, radius);

	glTranslatef(0, 2 * upperPtYDist, 0);
	radius -= 2 * upperPtXDist;
	DrawConePart(32, piconst / 2, upperPtYDist, radius);

	glRotatef(180, 1.0, 0, 0);
	glTranslatef(0, -3 * upperPtYDist, 0);
	radius += upperPtXDist;
	DrawConePart(32, angle, partLen, radius);

	glRotatef(180, 1.0, 0, 0);
	glTranslatef(0, 0.0, 0);
	DrawConePart(32, angle, partLen, radius);

	glRotatef(180, 1.0, 0, 0);
	glTranslatef(0, -2 * upperPtYDist, 0);
	DrawConePart(32, angle, partLen, radius);

	glRotatef(180, 1.0, 0, 0);
	glTranslatef(0, 0.0, 0);
	DrawConePart(32, angle, partLen, radius);

	glRotatef(180, 1.0, 0, 0);
	glTranslatef(0, -2 * upperPtYDist, 0);
	DrawConePart(32, angle, partLen, radius);

	glRotatef(180, 1.0, 0, 0);
	glTranslatef(0, 0.0, 0);
	DrawConePart(32, angle, partLen, radius);

	glRotatef(180, 1.0, 0, 0);
	glTranslatef(0, -2 * upperPtYDist, 0);
	DrawConePart(32, angle, partLen, radius);

	glTranslatef(0, -2 * upperPtYDist, 0);
	radius += 2 * upperPtXDist;
	DrawConePart(32, angle, partLen, radius);

	glPopMatrix();



	//tamniji delovi vaze
	glPushMatrix();
	radius = 1.7;
	darkVasePartMaterial.Select();
	glTranslatef(0, 0.5 + upperPtYDist, 0);
	radius -= upperPtXDist;
	DrawConePart(32, angle, partLen, radius);

	glTranslatef(0, 2 * upperPtYDist, 0);
	radius -= upperPtXDist;
	DrawConePart(32, piconst / 2, upperPtYDist, radius);

	glRotatef(180, 0.0, 0, 0);
	glTranslatef(0, -9 * upperPtYDist, 0);
	radius += 2 * upperPtXDist;
	DrawConePart(32, angle, partLen, radius);

	glRotatef(180, 1.0, 0, 0);
	glTranslatef(0, 1 * upperPtYDist, 0);
	radius += upperPtXDist;
	DrawConePart(32, angle, partLen, radius);

	glPopMatrix();

	glPopMatrix();

}





void CGLRenderer::DrawSvetlo()
{
	glEnable(GL_LIGHTING);
	if (crvenoSvetlo)
	{
		GLMaterial redLight;
		redLight.SetEmission(1.0f, 0.0f, 0.0f, 1.0f);
		redLight.SetAmbient(0.0f, 0.0f, 0.0f, 1.0f);
		redLight.SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
		redLight.SetDiffuse(0.0f, 0.0f, 0.0f, 1.0f);
		redLight.SelectFront();

		GLfloat spot_direction[] = { 0.0f, 0.0f, -1.0f };
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);

		glPushMatrix();
		glTranslatef(0.0f, 10.0f, 9.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		float light_ambient[] = { 0.1, 0.0, 0.0, 1.0 };
		DrawHalfSphere(.4f);
		float light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
		float light_emission[] = { 1.0, 0.0, 0.0, 1.0 };
		float light_specular[] = { 0.0f, 0.0f, 0.0f, 1.0 };
		float light_position[] = { 0.0f, 0.0f, 0.0f, 1.0 };
		glLightfv(GL_LIGHT1, GL_POSITION, light_position);
		glLightfv(GL_LIGHT1, GL_EMISSION, light_emission);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25);

		glEnable(GL_LIGHT1);
		glPopMatrix();
	}
	else
		glDisable(GL_LIGHT1);
	if (zelenoSvetlo)
	{
		GLMaterial greenLight;
		greenLight.SetEmission(0.0f, 1.0f, 0.0f, 1.0f);
		greenLight.SetAmbient(0.0f, 0.0f, 0.0f, 1.0f);
		greenLight.SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
		greenLight.SetDiffuse(0.0f, 0.0f, 0.0f, 1.0f);
		greenLight.SelectFront();

		GLfloat spot_direction[] = { 0.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);

		glPushMatrix();
		glTranslatef(0.0f, 10.0f, -9.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		DrawHalfSphere(.4f);
		float light_ambient[] = { 0.0, 0.1, 0.0, 1.0 };
		float light_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
		float light_emission[] = { 0.0, 1.0, 0.0, 1.0 };
		float light_specular[] = { 0.0f, 0.0f, 0.0f, 1.0 };
		float light_position[] = { 0.0f, 0.0f, 0.0f, 1.0 };
		glLightfv(GL_LIGHT2, GL_POSITION, light_position);
		glLightfv(GL_LIGHT2, GL_EMISSION, light_emission);
		glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25);

		glEnable(GL_LIGHT2);
		glPopMatrix();
	}
	else
		glDisable(GL_LIGHT2);
	if (plavoSvetlo)
	{
		GLMaterial blueLight;
		blueLight.SetEmission(0.0f, 0.0f, 1.0f, 1.0f);
		blueLight.SetAmbient(0.0f, 0.0f, 0.0f, 1.0f);
		blueLight.SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
		blueLight.SetDiffuse(0.0f, 0.0f, 0.0f, 1.0f);
		blueLight.SelectFront();

		GLfloat spot_direction[] = { 0.0f, -1.0f, 0.0f };
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
		glPushMatrix();
		glTranslatef(0.0f, 20.0f, 0.0f);
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		DrawHalfSphere(.4f);
		float light_ambient[] = { 0.0, 0.0, 0.1, 1.0 };
		float light_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
		float light_emission[] = { 0.0, 0.0, 1.0, 1.0 };
		float light_specular[] = { 0.0f, 0.0f, 0.0f, 1.0 };
		float light_position[] = { 0.0f, 0.0f, 0.0f, 1.0 };
		glLightfv(GL_LIGHT3, GL_POSITION, light_position);
		glLightfv(GL_LIGHT3, GL_EMISSION, light_emission);
		glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 25);

		glEnable(GL_LIGHT3);
		glPopMatrix();
	}
	else
		glDisable(GL_LIGHT3);
}

void CGLRenderer::SetRoomLightning()
{
	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	float light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_emission[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_specular[] = { 0.0f, 0.0f, 0.0f, 1.0 };
	float light_position[] = { 6.0f, 7.0f, 8.0f, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_EMISSION, light_emission);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//GLfloat spot_direction[] = { -1.0f, -1.0f, -1.0f };
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);

	glEnable(GL_LIGHT0);
}

void CGLRenderer::DrawHalfSphere(int horizontalPrecision, int verticalPrecision, double radius, double* color)
{
	int arraySize = ((verticalPrecision - 1) * horizontalPrecision + 1) * 3;
	double* vertices = new double[arraySize];
	//double* colors = new double[arraySize];
	double* normals = new double[arraySize];
	BYTE* topTrianglesInd = new BYTE[horizontalPrecision + 2];
	BYTE* quadsInd = new BYTE[4 * horizontalPrecision * (verticalPrecision - 2)];
	double yAngleStep = (piconst / 2) / (verticalPrecision - 1);
	double yAngle = piconst / 2 - yAngleStep;
	double xAngleStep = (2 * piconst) / horizontalPrecision;
	double xAngle = 0;
	double yAngCos, yAngSin, xAngCos, xAngSin, x, y, z, xNor, yNor, zNor;

	for (int i = 1; i < verticalPrecision; i++)
	{
		for (int j = 0; j < horizontalPrecision; j++)
		{
			yAngCos = cos(yAngle);
			yAngSin = sin(yAngle);
			xAngCos = cos(xAngle);
			xAngSin = sin(xAngle);

			xNor = yAngCos * xAngCos;
			yNor = yAngSin;
			zNor = yAngCos * xAngSin;

			x = radius * xNor;
			y = radius * yNor;
			z = radius * zNor;

			int startingInd = ((i - 1) * horizontalPrecision + j) * 3;
			vertices[startingInd] = x;
			vertices[startingInd + 1] = y;
			vertices[startingInd + 2] = -z;

			normals[startingInd] = xNor;
			normals[startingInd + 1] = yNor;
			normals[startingInd + 2] = -zNor;

			xAngle += xAngleStep;
		}

		yAngle -= yAngleStep;
	}
	int peakStartingInd = (verticalPrecision - 1) * horizontalPrecision * 3;
	vertices[peakStartingInd] = 0;
	vertices[peakStartingInd + 1] = radius;
	vertices[peakStartingInd + 2] = 0;

	normals[peakStartingInd] = 0;
	normals[peakStartingInd + 1] = 1;
	normals[peakStartingInd + 2] = 0;

	for (int i = 0; i < verticalPrecision - 2; i++)
	{
		for (int j = 0; j < horizontalPrecision; j++)
		{
			int startingInd = (i * horizontalPrecision + j) * 4;
			int startingIndQuarter = startingInd / 4;
			quadsInd[startingInd] = startingIndQuarter;
			quadsInd[startingInd + 1] = startingIndQuarter + horizontalPrecision;
			quadsInd[startingInd + 2] = (i + 1) * horizontalPrecision + (j + 1) % horizontalPrecision;
			quadsInd[startingInd + 3] = quadsInd[startingInd + 2] - horizontalPrecision;
		}
	}

	int numOfPointsNoPeaks = (verticalPrecision - 1) * horizontalPrecision;
	topTrianglesInd[0] = numOfPointsNoPeaks;
	int i = 0;
	for (i = 0; i < horizontalPrecision; i++)
	{
		topTrianglesInd[i + 1] = i;
	}
	topTrianglesInd[i + 1] = 0;

	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glNormalPointer(GL_DOUBLE, 0, normals);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glDrawElements(GL_QUADS, 4 * horizontalPrecision * (verticalPrecision - 2), GL_UNSIGNED_BYTE, quadsInd);
	glDrawElements(GL_TRIANGLE_FAN, horizontalPrecision + 2, GL_UNSIGNED_BYTE, topTrianglesInd);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	if (vertices != nullptr)
		delete vertices;

	if (normals != nullptr)
		delete normals;

	if (quadsInd != nullptr)
		delete quadsInd;

	if (topTrianglesInd != nullptr)
		delete topTrianglesInd;
}

void CGLRenderer::DrawCoordinateLines()
{
	glLineWidth(2.0);
	GLMaterial xMat, yMat, zMat;
	xMat.SetDiffuse(1.0f, 0.0f, 0.0f, 1.0f);
	xMat.SetAmbient(1.0f, 0.0f, 0.0f, 1.0f);
	xMat.SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
	yMat.SetDiffuse(0.0f, 1.0f, 0.0f, 1.0f);
	yMat.SetAmbient(0.0f, 1.0f, 0.0f, 1.0f);
	yMat.SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
	zMat.SetDiffuse(0.0f, 0.0f, 1.0f, 1.0f);
	zMat.SetAmbient(0.0f, 0.0f, 1.0f, 1.0f);
	zMat.SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	{
		xMat.SelectFront();
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0.0);

		yMat.SelectFront();
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);

		zMat.SelectFront();
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 10.0);
	}
	glEnd();
}


void CGLRenderer::DrawPrism(int numOfSides, double height, double radius, double* color)
{
	int arraySize = numOfSides * 4 * 3;
	double* vertices = new double[arraySize];
	double* sidesNormals = new double[arraySize];
	BYTE* sidesIndices = new BYTE[numOfSides * 4];

	double currentAngle = 0;
	double angleStep = (2 * piconst) / numOfSides;
	double x, z, polygonAngleHalf, normalAngle;

	normalAngle = (piconst / 2) - ((piconst - angleStep) / 2);

	for (int i = 0; i < numOfSides; i++)
	{
		currentAngle = i * angleStep;

		x = cos(currentAngle);
		z = sin(currentAngle);

		double x1Nor = cos(currentAngle + normalAngle);
		double z1Nor = sin(currentAngle + normalAngle);
		double x2Nor = cos(currentAngle - normalAngle);
		double z2Nor = sin(currentAngle - normalAngle);

		int startingInd = i * 12;

		vertices[startingInd] = vertices[startingInd + 3] = x * radius;
		vertices[startingInd + 1] = vertices[startingInd + 4] = -height / 2;
		vertices[startingInd + 2] = vertices[startingInd + 5] = radius * z;

		sidesNormals[startingInd] = x1Nor; sidesNormals[startingInd + 1] = 0; sidesNormals[startingInd + 2] = z1Nor;
		sidesNormals[startingInd + 3] = x2Nor; sidesNormals[startingInd + 4] = 0; sidesNormals[startingInd + 5] = z2Nor;

		vertices[startingInd + 6] = vertices[startingInd + 9] = vertices[startingInd];
		vertices[startingInd + 7] = vertices[startingInd + 10] = height / 2;
		vertices[startingInd + 8] = vertices[startingInd + 11] = vertices[startingInd + 2];

		sidesNormals[startingInd + 6] = x1Nor; sidesNormals[startingInd + 7] = 0; sidesNormals[startingInd + 8] = z1Nor;
		sidesNormals[startingInd + 9] = x2Nor; sidesNormals[startingInd + 10] = 0; sidesNormals[startingInd + 11] = z2Nor;
	}

	for (int i = 0; i < numOfSides; i++)
	{
		int startingInd = i * 4;
		sidesIndices[startingInd] = startingInd;
		sidesIndices[startingInd + 1] = startingInd + 2;
		sidesIndices[startingInd + 2] = ((i + 2) * 4 - 1) % (numOfSides * 4);
		sidesIndices[startingInd + 3] = sidesIndices[startingInd + 2] - 2;
	}

	double* topSideVertices = new double[numOfSides * 3];
	double* topSideNormals = new double[numOfSides * 3];
	BYTE* topSideIndices = new BYTE[numOfSides];

	double* bottomSideVertices = new double[numOfSides * 3];
	double* bottomSideNormals = new double[numOfSides * 3];
	BYTE* bottomSideIndices = new BYTE[numOfSides];

	currentAngle = 0;
	angleStep = (2 * piconst) / numOfSides;
	for (int i = 0; i < numOfSides; i++)
	{
		int ind = i * 3;
		topSideVertices[ind] = radius * cos(currentAngle);
		topSideVertices[ind + 1] = height / 2;
		topSideVertices[ind + 2] = -radius * sin(currentAngle);

		bottomSideVertices[ind] = radius * cos(currentAngle);
		bottomSideVertices[ind + 1] = -height / 2;
		bottomSideVertices[ind + 2] = radius * sin(currentAngle);

		topSideNormals[ind] = 0;
		topSideNormals[ind + 1] = 1;
		topSideNormals[ind + 2] = 0;

		bottomSideNormals[ind] = 0;
		bottomSideNormals[ind + 1] = -1;
		bottomSideNormals[ind + 2] = 0;

		topSideIndices[i] = i;
		bottomSideIndices[i] = i;
		currentAngle += angleStep;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glNormalPointer(GL_DOUBLE, 0, sidesNormals);
	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glDrawElements(GL_QUADS, numOfSides * 4, GL_UNSIGNED_BYTE, sidesIndices);

	glNormalPointer(GL_DOUBLE, 0, topSideNormals);
	glVertexPointer(3, GL_DOUBLE, 0, topSideVertices);
	glDrawElements(GL_POLYGON, numOfSides, GL_UNSIGNED_BYTE, topSideIndices);

	glNormalPointer(GL_DOUBLE, 0, bottomSideNormals);
	glVertexPointer(3, GL_DOUBLE, 0, bottomSideVertices);
	glDrawElements(GL_POLYGON, numOfSides, GL_UNSIGNED_BYTE, bottomSideIndices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	if (vertices != nullptr)
		delete[] vertices;

	if (sidesIndices != nullptr)
		delete[] sidesIndices;
}


void CGLRenderer::DrawConePart(int precision, double angle, double partLen, double radius)
{
	int arraySize = precision * 2 * 3;
	double* vertices = new double[arraySize];
	double* normals = new double[arraySize];
	BYTE* indices = new BYTE[(precision + 1) * 2];
	double currentAngle = 0;
	double angleStep = (2 * piconst) / precision;
	double lowerX, lowerZ, higherX, higherZ;
	double fullConeHeight, fullConeSideLen, upperPtXDist, upperPtYDist, nr, ny;
	double angleSin = sin(angle);
	double angleCos = cos(angle);
	fullConeSideLen = radius / angleCos;
	fullConeHeight = fullConeSideLen * angleSin;
	upperPtXDist = partLen * angleCos;
	upperPtYDist = partLen * angleSin;
	nr = fullConeHeight / fullConeSideLen;
	ny = radius / fullConeSideLen;

	double smallerRadius = radius - upperPtXDist;


	for (int i = 0; i < precision; i++)
	{
		currentAngle = i * angleStep;

		angleCos = cos(currentAngle);
		angleSin = sin(currentAngle);

		lowerX = radius * angleCos;
		lowerZ = radius * angleSin;
		higherX = smallerRadius * angleCos;
		higherZ = smallerRadius * angleSin;

		int sixI = i * 6;
		int twoI = i * 2;

		vertices[sixI] = lowerX;
		vertices[sixI + 1] = 0;
		vertices[sixI + 2] = lowerZ;
		vertices[sixI + 3] = higherX;
		vertices[sixI + 4] = upperPtYDist;
		vertices[sixI + 5] = higherZ;

		indices[twoI] = twoI;
		indices[twoI + 1] = twoI + 1;

		normals[sixI] = normals[sixI + 3] = nr * angleCos;
		normals[sixI + 1] = normals[sixI + 4] = ny;
		normals[sixI + 2] = normals[sixI + 5] = nr * angleSin;
	}

	indices[precision * 2] = 0;
	indices[precision * 2 + 1] = 1;

	if (normalsOn)
	{
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		{
			glColor3f(0, 1.0, 0);
			for (int i = 0; i < precision; i++)
			{
				int sixI = i * 6;
				glVertex3f(vertices[sixI], vertices[sixI + 1], vertices[sixI + 2]);
				glVertex3f(vertices[sixI] + normals[sixI], vertices[sixI + 1] + normals[sixI + 1], vertices[sixI + 2] + normals[sixI + 2]);

				glVertex3f(vertices[sixI + 3], vertices[sixI + 4], vertices[sixI + 5]);
				glVertex3f(vertices[sixI + 3] + normals[sixI + 3], vertices[sixI + 4] + normals[sixI + 4], vertices[sixI + 5] + normals[sixI + 5]);
			}
		}
		glEnd();
		glFlush();
		glEnable(GL_LIGHTING);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glNormalPointer(GL_DOUBLE, 0, normals);

	glDrawElements(GL_QUAD_STRIP, (precision + 1) * 2, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	if (vertices != nullptr)
		delete[] vertices;

	if (normals != nullptr)
		delete[] normals;

	if (indices != nullptr)
		delete[] indices;
}


void CGLRenderer::DrawCylinder(int precision, double height, double radius, double* color)
{
	DrawPrismC(precision, height, radius, color);
}

void CGLRenderer::DrawPrismC(int numOfSides, double height, double radius, double* color)
{
	int arraySize = numOfSides * 2 * 3;
	double* vertices = new double[arraySize];
	double* sidesNormals = new double[arraySize];
	BYTE* sidesIndices = new BYTE[numOfSides * 4];

	double currentAngle = 0;
	double angleStep = (2 * piconst) / numOfSides;
	double xNor, zNor;
	for (int i = 0; i < numOfSides; i++)
	{
		currentAngle = i * angleStep;

		xNor = cos(currentAngle);
		zNor = sin(currentAngle);

		int startingInd = i * 3;

		vertices[startingInd] = xNor * radius;
		vertices[startingInd + 1] = height / 2;
		vertices[startingInd + 2] = -radius * zNor;

		sidesNormals[startingInd] = xNor;
		sidesNormals[startingInd + 1] = 0;
		sidesNormals[startingInd + 2] = -zNor;

		int startingInd2 = (numOfSides + i) * 3;

		vertices[startingInd2] = vertices[startingInd];
		vertices[startingInd2 + 1] = -height / 2;
		vertices[startingInd2 + 2] = -vertices[startingInd + 2];

		sidesNormals[startingInd2] = xNor;
		sidesNormals[startingInd2 + 1] = 0;
		sidesNormals[startingInd2 + 2] = zNor;
	}

	for (int i = 0; i < numOfSides; i++)
	{
		int startingInd = i * 4;
		sidesIndices[startingInd] = i;
		sidesIndices[startingInd + 1] = (i == 0) ? numOfSides : (2 * numOfSides - i);
		sidesIndices[startingInd + 2] = (i == 0) ? (2 * numOfSides - 1) : (sidesIndices[startingInd + 1] - 1);
		sidesIndices[startingInd + 3] = (i + 1) % numOfSides;
	}

	double* topSideVertices = new double[numOfSides * 3];
	double* topSideNormals = new double[numOfSides * 3];
	BYTE* topSideIndices = new BYTE[numOfSides];

	double* bottomSideVertices = new double[numOfSides * 3];
	double* bottomSideNormals = new double[numOfSides * 3];
	BYTE* bottomSideIndices = new BYTE[numOfSides];

	currentAngle = 0;
	angleStep = (2 * piconst) / numOfSides;
	for (int i = 0; i < numOfSides; i++)
	{
		int ind = i * 3;
		topSideVertices[ind] = radius * cos(currentAngle);
		topSideVertices[ind + 1] = height / 2;
		topSideVertices[ind + 2] = -radius * sin(currentAngle);

		bottomSideVertices[ind] = radius * cos(currentAngle);
		bottomSideVertices[ind + 1] = -height / 2;
		bottomSideVertices[ind + 2] = radius * sin(currentAngle);

		topSideNormals[ind] = 0;
		topSideNormals[ind + 1] = 1;
		topSideNormals[ind + 2] = 0;

		bottomSideNormals[ind] = 0;
		bottomSideNormals[ind + 1] = -1;
		bottomSideNormals[ind + 2] = 0;

		topSideIndices[i] = i;
		bottomSideIndices[i] = i;
		currentAngle += angleStep;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glNormalPointer(GL_DOUBLE, 0, sidesNormals);
	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glDrawElements(GL_QUADS, numOfSides * 4, GL_UNSIGNED_BYTE, sidesIndices);

	glNormalPointer(GL_DOUBLE, 0, topSideNormals);
	glVertexPointer(3, GL_DOUBLE, 0, topSideVertices);
	glDrawElements(GL_POLYGON, numOfSides, GL_UNSIGNED_BYTE, topSideIndices);

	glNormalPointer(GL_DOUBLE, 0, bottomSideNormals);
	glVertexPointer(3, GL_DOUBLE, 0, bottomSideVertices);
	glDrawElements(GL_POLYGON, numOfSides, GL_UNSIGNED_BYTE, bottomSideIndices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	if (vertices != nullptr)
		delete[] vertices;

	if (sidesIndices != nullptr)
		delete[] sidesIndices;
}