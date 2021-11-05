#include "pch.h"
#include "GLRenderer.h"
#include <gl\GL.h>
#include <gl\GLU.h>

GLRenderer::GLRenderer(void)
{
	currentPt = new CPoint();
	xRotationAngle = 0;
	yRotationAngle = 0;
	memXRotationAngle = 0;
	memYRotationAngle = 0;
	yOffset = -6.2;

	redOn = true;
	greenOn = true;
	blueOn = true;
}

GLRenderer::~GLRenderer(void)
{
}

bool GLRenderer::CreateGLContext(CDC* pDC)
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

void GLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	wglMakeCurrent(NULL, NULL);
}

void GLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, (double)w / (double)h, 0.1, 100);
	gluLookAt(15.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
	glMatrixMode(GL_MODELVIEW);


	wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	double xAngle = memXRotationAngle + xRotationAngle;
	double yAngle = memYRotationAngle + yRotationAngle;
	glRotatef(yAngle, 0.0, 0.0, 1.0);
	glRotatef(xAngle, 0.0, 1.0, 0.0);

	glTranslatef(0.0, yOffset, 0.0);

	glLineWidth(1);
	glPointSize(10);

	double green[3] = { 0.0, 0.8, 0.0 };
	double yellow[3] = { 0.901, 0.722, 0.0 };
	double white[3] = { 1.0, 1.0, 1.0 };
	double elementHeight = 1.4;
	double bigElementRadius = sqrt(2) / 2;
	double smallElementRadius = 0.3;
	double offsetPlusRadius = elementHeight / 2 + smallElementRadius;

	glBegin(GL_LINES);
	{
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 10.0);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
	}
	glEnd();
	glFlush();



	glEnable(GL_LIGHTING);

	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	GLfloat light0_position[] = { 5.0, 40.0, 30.0, 0.0 };
	GLfloat light0_ambient[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat light0_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light0_specular[] = { 0.6, 0.6, 0.6, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glEnable(GL_LIGHT0);

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

	//crveno poziciono svetlo
	if (redOn)
	{
		mat_dif[0] = 1.0; mat_dif[1] = 0.0; mat_dif[2] = 0.0;
		mat_amb[0] = mat_amb[1] = mat_amb[2] = 0.0;
		mat_emm[0] = mat_emm[3] = 1.0; mat_emm[1] = 0.47; mat_emm[2] = 0.47;
		mat_spec[0] = mat_spec[1] = mat_spec[2] = 0.0;
		mat_shin = 0.0;
		GLMaterial redLightBulbMaterial(mat_amb, mat_dif, mat_spec, mat_emm, mat_shin);
		redLightBulbMaterial.Select();

		glPushMatrix();
		glTranslatef(0, 10, 11);
		DrawSphere(12, 12, 0.5, green);
		glPopMatrix();

		GLfloat light1_ambient[] = { 0.2, 0.0, 0.0, 1.0 };
		GLfloat light1_diffuse[] = { 0.8, 0.0, 0.0, 1.0 };
		GLfloat light1_specular[] = { 1.0, 0.0, 0.0, 1.0 };
		GLfloat light1_position[] = { 0.0, 10.0, 11.0, 1.0 };
		GLfloat light1_direction[] = { 0.0, 0.0, -1.0 };

		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

		//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
		//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
		//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);

		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.0);

		glEnable(GL_LIGHT1);

	}
	else
		glDisable(GL_LIGHT1);


	//zeleno poziciono svetlo
	if (greenOn)
	{

		mat_dif[0] = 0.0; mat_dif[1] = 1.0; mat_dif[2] = 0.0;
		mat_amb[0] = 0.0; mat_amb[1] = 0.0; mat_amb[2] = 0.0;
		mat_emm[0] = 0.47; mat_emm[1] = 1.0; mat_emm[2] = 0.47;
		mat_spec[0] = 0.0; mat_spec[1] = 0.0; mat_spec[2] = 0.0;
		mat_shin = 0.0;
		GLMaterial greenLightBulbMaterial(mat_amb, mat_dif, mat_spec, mat_emm, mat_shin);
		greenLightBulbMaterial.Select();

		glPushMatrix();
		glTranslatef(0, 10, -11);
		DrawSphere(12, 12, 0.5, green);
		glPopMatrix();

		//GLfloat light2_ambient[] = { 0.2, 0.6, 0.2, 1.0 };
		//GLfloat light2_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
		//GLfloat light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		//GLfloat light2_position[] = { 29.0, 30.0, 0.0, 1.0 };
		//GLfloat light2_direction[] = { -1.0, 0.0, 0.0 };
		GLfloat light2_ambient[] = { 0.0, 0.2, 0.0, 1.0 };
		GLfloat light2_diffuse[] = { 0.0, 0.8, 0.0, 1.0 };
		GLfloat light2_specular[] = { 0.0, 1.0, 0.0, 1.0 };
		GLfloat light2_position[] = { 0.0, 10.0, -11.0, 1.0 };
		GLfloat light2_direction[] = { 0.0, 0.0, 1.0 };

		glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
		glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);

		//glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
		//glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0);
		//glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);

		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);
		//glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.0);

		glEnable(GL_LIGHT2);

	}
	else
		glDisable(GL_LIGHT2);


	//plavo poziciono svetlo
	if (blueOn)
	{
		mat_dif[0] = 0.0; mat_dif[1] = 0.0; mat_dif[2] = 1.0;
		mat_amb[0] = mat_amb[1] = mat_amb[2] = 0.0;
		mat_emm[0] = 0.47; mat_emm[1] = 0.47; mat_emm[2] = 1.0;
		mat_spec[0] = mat_spec[1] = mat_spec[2] = 0.0;
		mat_shin = 0.0;
		GLMaterial blueLightBulbMaterial(mat_amb, mat_dif, mat_spec, mat_emm, mat_shin);
		blueLightBulbMaterial.Select();

		glPushMatrix();
		glTranslatef(0, 19, 0);
		DrawSphere(12, 12, 0.5, green);
		glPopMatrix();

		GLfloat light3_ambient[] = { 0.0, 0.0, 0.2, 1.0 };
		GLfloat light3_diffuse[] = { 0.0, 0.2, 0.8, 1.0 };
		GLfloat light3_specular[] = { 0.0, 0.0, 1.0, 1.0 };
		GLfloat light3_position[] = { 0.0, 19.0, 0.0, 1.0 };
		GLfloat light3_direction[] = { 0.0, -1.0, 0.0 };

		glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
		glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
		glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);

		//glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0);
		//glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0);
		//glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0);

		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_direction);
		glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 0.0);

		glEnable(GL_LIGHT3);
	}
	else
		glDisable(GL_LIGHT3);

	tableMaterial.Select();

	glPushMatrix();
	DrawHalfSphere(15, 10, 2, green);

	glTranslatef(0, 2.5, 0);
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
	radius += 2*upperPtXDist;
	DrawConePart(32, angle, partLen, radius);

	glRotatef(180, 1.0, 0, 0);
	glTranslatef(0, 1 * upperPtYDist, 0);
	radius += upperPtXDist;
	DrawConePart(32, angle, partLen, radius);
	
	glPopMatrix();

	glPopMatrix();


	glEnable(GL_CULL_FACE);
	tableMaterial.Select();

	//dalji zid po z osi
	glPushMatrix();
	glTranslatef(-12, 0.0, -12);
	DrawWall(20, 25, 100, 100);
	glPopMatrix();

	//blizi zid po z osi
	glPushMatrix();
	glRotatef(180, 0, 1.0, 0);
	glTranslatef(-12, 0.0, -12);
	DrawWall(20, 25, 100, 100);
	glPopMatrix();

	//desni zid
	glPushMatrix();
	glRotatef(-90, 0, 1.0, 0);
	glTranslatef(-12, 0.0, -12);
	DrawWall(20, 25, 100, 100);
	glPopMatrix();

	//levi zid
	glPushMatrix();
	glRotatef(90, 0, 1.0, 0);
	glTranslatef(-12, 0.0, -12);
	DrawWall(20, 25, 100, 100);
	glPopMatrix();

	//tavanica
	glPushMatrix();
	glRotatef(90, 1.0, 0, 0);
	glTranslatef(-12, -12.0, -19);
	DrawWall(25, 25, 100, 100);
	glPopMatrix();

	//pod
	glPushMatrix();
	glRotatef(-90, 1.0, 0, 0);
	glTranslatef(-12, -12.0, 0);
	DrawWall(25, 25, 100, 100);
	glPopMatrix();

	glDisable(GL_CULL_FACE);

	glDisable(GL_LIGHTING);

	glFlush();
	SwapBuffers(pDC->m_hDC);

	wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void GLRenderer::RotateView(CPoint* newPoint)
{
	xRotationAngle = (double)(newPoint->x - currentPt->x);
	yRotationAngle = (double)(currentPt->y - newPoint->y);
}

void GLRenderer::SetMemAngles()
{
	memXRotationAngle += xRotationAngle;
	if (memXRotationAngle >= 360)
		memXRotationAngle -= 360;
	else if (memXRotationAngle <= -360)
		memXRotationAngle += 360;
	xRotationAngle = 0;

	memYRotationAngle += yRotationAngle;
	if (memYRotationAngle >= 360)
		memYRotationAngle -= 360;
	else if (memYRotationAngle <= -360)
		memYRotationAngle += 360;
	yRotationAngle = 0;
}

void GLRenderer::DrawHalfSphere(int horizontalPrecision, int verticalPrecision, double radius, double* color)
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

void GLRenderer::DrawSphere(int horizontalPrecision, int verticalHalfPrecision, double radius, double* color)
{
	int arraySize = ((verticalHalfPrecision - 2) * horizontalPrecision + 2) * 3;
	double* vertices = new double[arraySize];
	double* normals = new double[arraySize];
	double* colors = new double[arraySize];
	BYTE* topTrianglesInd = new BYTE[horizontalPrecision + 2];
	BYTE* bottomTrianglesInd = new BYTE[horizontalPrecision + 2];
	BYTE* quadsInd = new BYTE[4 * horizontalPrecision * (verticalHalfPrecision - 3)];
	double yAngleStep = piconst / (verticalHalfPrecision - 1);
	double yAngle = piconst / 2 - yAngleStep;
	double xAngleStep = (2 * piconst) / horizontalPrecision;
	double xAngle = 0;
	double yAngCos, yAngSin, xAngCos, xAngSin, x, y, z, xNor, yNor, zNor;

	for (int i = 1; i < verticalHalfPrecision - 1; i++)
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
	int peakStartingInd = (verticalHalfPrecision - 2) * horizontalPrecision * 3;
	vertices[peakStartingInd] = 0;
	vertices[peakStartingInd + 1] = radius;
	vertices[peakStartingInd + 2] = 0;

	normals[peakStartingInd] = 0;
	normals[peakStartingInd + 1] = 1;
	normals[peakStartingInd + 2] = 0;

	vertices[peakStartingInd + 3] = 0;
	vertices[peakStartingInd + 4] = -radius;
	vertices[peakStartingInd + 5] = 0;

	normals[peakStartingInd + 3] = 0;
	normals[peakStartingInd + 4] = -1;
	normals[peakStartingInd + 5] = 0;

	for (int i = 0; i < verticalHalfPrecision - 3; i++)
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

	int numOfPointsNoPeaks = (verticalHalfPrecision - 2) * horizontalPrecision;
	topTrianglesInd[0] = numOfPointsNoPeaks;
	bottomTrianglesInd[0] = numOfPointsNoPeaks + 1;
	int i = 0;
	for (i = 0; i < horizontalPrecision; i++)
	{
		topTrianglesInd[i + 1] = i;
		bottomTrianglesInd[i + 1] = numOfPointsNoPeaks - 1 - i;
	}
	topTrianglesInd[i + 1] = 0;
	bottomTrianglesInd[i + 1] = numOfPointsNoPeaks - 1;

	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glNormalPointer(GL_DOUBLE, 0, normals);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glDrawElements(GL_QUADS, 4 * horizontalPrecision * (verticalHalfPrecision - 3), GL_UNSIGNED_BYTE, quadsInd);
	glDrawElements(GL_TRIANGLE_FAN, horizontalPrecision + 2, GL_UNSIGNED_BYTE, topTrianglesInd);
	glDrawElements(GL_TRIANGLE_FAN, horizontalPrecision + 2, GL_UNSIGNED_BYTE, bottomTrianglesInd);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void GLRenderer::DrawPrismC(int numOfSides, double height, double radius, double* color)
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

void GLRenderer::DrawPrism(int numOfSides, double height, double radius, double* color)
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

void GLRenderer::DrawCylinder(int precision, double height, double radius, double* color)
{
	DrawPrismC(precision, height, radius, color);
}

void GLRenderer::DrawConePart(int precision, double angle, double partLen, double radius)
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

void GLRenderer::DrawWall(double height, double width, double heightPrecision, double widthPrecision)
{
	double heightStep = height / heightPrecision;
	double widthStep = width / widthPrecision;

	for (int i = 0; i < heightPrecision - 1; i++)
	{
		DrawWallPart(heightStep, widthStep, widthPrecision - 1, i * heightStep);
	}
}

void GLRenderer::DrawWallPart(double quadHeight, double quadWidth, double quadNum, double startingHeight)
{
	double* vertices = new double[(quadNum + 1) * 2 * 3];
	BYTE* indices = new BYTE[(quadNum + 1) * 2];
	double* normals = new double[(quadNum + 1) * 2 * 3];

	double higherY = startingHeight + quadHeight;

	for (int i = 0; i < (quadNum + 1); i++)
	{
		int startingInd = i * 6;
		double xCoo = i * quadWidth;

		vertices[startingInd] = xCoo;
		vertices[startingInd + 1] = higherY;
		vertices[startingInd + 2] = 0;

		normals[startingInd] = 0;
		normals[startingInd + 1] = 0;
		normals[startingInd + 2] = 1;

		indices[i * 2] = i * 2;

		vertices[startingInd + 3] = xCoo;
		vertices[startingInd + 4] = startingHeight;
		vertices[startingInd + 5] = 0;

		normals[startingInd + 3] = 0;
		normals[startingInd + 4] = 0;
		normals[startingInd + 5] = 1;

		indices[i * 2 + 1] = i * 2 + 1;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glNormalPointer(GL_DOUBLE, 0, normals);

	glDrawElements(GL_QUAD_STRIP, (quadNum + 1) * 2, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	if (vertices != nullptr)
		delete[] vertices;

	if (normals != nullptr)
		delete[] normals;

	if (indices != nullptr)
		delete[] indices;
}

void GLRenderer::DrawTry(int numOfSides, double height, double radius, double* color)
{
	int arraySize = numOfSides * 2 * 3;
	double* vertices = new double[arraySize];
	double* colors = new double[arraySize];
	BYTE* sidesIndices = new BYTE[numOfSides * 4];
	BYTE* basesIndices = new BYTE[numOfSides * 2];
	double currentAngle = 0;
	double angleStep = (2 * piconst) / numOfSides;
	double x, z, xNor, zNor;
	for (int i = 0; i < numOfSides; i++)
	{
		currentAngle = i * angleStep;
		x = (double)0 + radius * cos(currentAngle);
		z = (double)0 - radius * sin(currentAngle);

		xNor = cos(currentAngle);
		zNor = sin(currentAngle);

		int startingInd = i * 3;

		vertices[startingInd] = radius * xNor;
		vertices[startingInd + 1] = -height / 2;
		vertices[startingInd + 2] = -radius * zNor;

		colors[startingInd] = color[0];
		colors[startingInd + 1] = color[1];
		colors[startingInd + 2] = color[2];

		int startingInd2 = (numOfSides + i) * 3;

		vertices[startingInd2] = vertices[startingInd];
		vertices[startingInd2 + 1] = height / 2;
		vertices[startingInd2 + 2] = -vertices[startingInd + 2];

		colors[startingInd2] = color[0];
		colors[startingInd2 + 1] = color[1];
		colors[startingInd2 + 2] = color[2];
	}

	for (int i = 0; i < numOfSides; i++)
	{
		int startingInd = i * 4;
		sidesIndices[startingInd] = i;
		sidesIndices[startingInd + 1] = (i == 0) ? numOfSides : (2 * numOfSides - i);
		sidesIndices[startingInd + 2] = (i == 0) ? (2 * numOfSides - 1) : (sidesIndices[startingInd + 1] - 1);
		sidesIndices[startingInd + 3] = (i + 1) % numOfSides;
	}

	for (int i = 0; i < numOfSides; i++)
	{
		basesIndices[numOfSides - 1 - i] = i;
		basesIndices[numOfSides + i] = numOfSides + i;
	}

	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glColorPointer(3, GL_DOUBLE, 0, colors);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glDrawElements(GL_QUADS, numOfSides * 4, GL_UNSIGNED_BYTE, sidesIndices);
	glDrawElements(GL_POLYGON, numOfSides, GL_UNSIGNED_BYTE, basesIndices);
	glDrawElements(GL_POLYGON, numOfSides, GL_UNSIGNED_BYTE, basesIndices + numOfSides);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	if (vertices != nullptr)
		delete[] vertices;

	if (colors != nullptr)
		delete[] colors;

	if (sidesIndices != nullptr)
		delete[] sidesIndices;

	if (basesIndices != nullptr)
		delete[] basesIndices;
}
