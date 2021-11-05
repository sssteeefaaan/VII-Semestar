#include "pch.h"
#include "GLRenderer.h"
#include "DImage.h"
#include <gl\GL.h>
#include <gl\GLU.h>

GLRenderer::GLRenderer(void)
{
    xRot = 0;
    yRot = 0;
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

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::Reshape(CDC* pDC, int w, int h)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, (double)w / (double)h, 0.1, 100);
    gluLookAt(0.00, 0.00, 12.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DrawScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glTranslatef(0.0, -3.0, 0.0);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);

    float ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.5, 0.5, 1.0, 0.0 };

    glColor3f(0.4, 0.5, 0.7);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    //DrawColumn(0.5, 5);
    //DrawPyramid(1, 4, 5);
    //Draw2Pyramid(1, 4);
    DrawFigure(0.5, 5, 1.5, 1, 0.9, 2, 20);

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

void GLRenderer::DrawColumn(double side, double height)
{
    double a = side / 2;
    double h = height / 2;
    glBegin(GL_QUADS);
    {
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(a, h, a);
        glVertex3f(a, -h, a);
        glVertex3f(a, -h, -a);
        glVertex3f(a, h, -a);

        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(a, h, -a);
        glVertex3f(a, -h, -a);
        glVertex3f(-a, -h, -a);
        glVertex3f(-a, h, -a);

        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(-a, h, -a);
        glVertex3f(-a, -h, -a);
        glVertex3f(-a, -h, a);
        glVertex3f(-a, h, a);

        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(-a, h, a);
        glVertex3f(-a, -h, a);
        glVertex3f(a, -h, a);
        glVertex3f(a, h, a);

        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(a, h, a);
        glVertex3f(a, h, -a);
        glVertex3f(-a, h, -a);
        glVertex3f(-a, h, a);

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(a, -h, a);
        glVertex3f(-a, -h, a);
        glVertex3f(-a, -h, -a);
        glVertex3f(a, -h, -a);
    }
    glEnd();
}

void GLRenderer::DrawPyramid(double side, double height, int n)
{
    double angleStep = (2 * piconst) / n;
    double currAngle = 0;

    double halfAngle = angleStep / 2;
    double r = (side / 2) / tan(halfAngle);
    double L = sqrt(r * r + height * height);
    double R = sqrt(r * r + (side / 2) * (side / 2));
    float ny = r / L;
    float nr = height / L;

    glBegin(GL_TRIANGLES);
    {
        for (int i = 0; i < n; i++)
        {
            glNormal3f(nr * cos(currAngle + (angleStep / 2)), ny, -nr * sin(currAngle + (angleStep / 2)));

            float x1 = R * cos(currAngle);
            float x2 = R * cos(currAngle + angleStep);
            float z1 = -R * sin(currAngle);
            float z2 = -R * sin(currAngle + angleStep);

            glVertex3f(0, height, 0);
            glVertex3f(x1, 0, z1);
            glVertex3f(x2, 0, z2);

            currAngle += angleStep;
        }
    }
    glEnd();

    currAngle = 0;
    glBegin(GL_TRIANGLE_FAN);
    {
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        for (int i = 0; i < n + 1; i++)
        {
            glVertex3f(R * cos(currAngle), 0.0, R * sin(currAngle));
            currAngle += angleStep;
        }
    }
    glEnd();
}

void GLRenderer::Draw2Pyramid(double side, double height)
{
    int n = 5;
    DrawPyramid(side, height, n);
    glPushMatrix();
    glRotatef(180, 1.0, 0.0, 0.0);
    DrawPyramid(side, height, n);
    glPopMatrix();
}

void GLRenderer::DrawFigure(float aS, float hS, float aR, float size, float height, float offset, float angle)
{
    glPushMatrix();
    glTranslatef(-hS / 2 + aS / 2, hS / 2, 0.0);
    DrawColumn(aS, hS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(hS / 2 - aS / 2, hS / 2, 0.0);
    DrawColumn(aS, hS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, hS + aS / 2, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    DrawColumn(aS, hS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-hS / 2 + aS / 2 + offset, hS - aS / 2, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    DrawColumn(aR, aS);
    glPopMatrix();

    glTranslatef(-hS / 2 + aS / 2 + offset, hS - aS, 0.0);

    glPushMatrix();
    glBegin(GL_LINES);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, -2 * height, 0.0);
    }
    glEnd();

    glTranslatef(0.0, -2 * height - height, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    Draw2Pyramid(size, height);
    glPopMatrix();
}

void GLRenderer::RotateView(int x, int y)
{
    xRot += x;
    if (xRot > 360)
        xRot -= 360;
    else if (xRot < 0)
        xRot += 360;

    yRot += y;
    if (yRot > 360)
        yRot -= 360;
    else if (yRot < 0)
        yRot += 360;
}






