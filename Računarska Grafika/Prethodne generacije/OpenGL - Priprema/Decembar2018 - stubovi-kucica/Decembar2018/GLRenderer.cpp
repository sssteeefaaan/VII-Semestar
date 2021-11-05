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

    glClearColor(0.5, 0.5, 0.5, 1.0);
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
    gluPerspective(45, (double)w / (double)h, 0.1, 100);
    //gluLookAt(0.00, 0.00, 8.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DrawScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    SetLight();

    glTranslatef(0.0, 0.0, -40.0);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);

    //DrawBox(3, 4, 5);
    //DrawCylinder(0.5, 8, 20);
    //DrawColumn(0.5, 8, 20);
    DrawTemple();

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

void GLRenderer::RotateScene(int x, int y)
{
    xRot += x;
    if (xRot < 0)
        xRot += 360;
    else if (xRot > 360)
        xRot -= 360;

    yRot += y;
    if (yRot < 0)
        yRot += 360;
    else if (yRot > 360)
        yRot -= 360;
}


void GLRenderer::SetLight()
{
    float ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float position[] = { 0.0, 0.0, 0.0, 1.0 }; //postavlja svetlo na poziciji posmatraca, tako da uvek prati poziciju posmatraca  
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void GLRenderer::DrawBox(double a, double b, double c)
{

    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(-a / 2, b / 2, c / 2);
        glVertex3f(-a / 2, -b / 2, c / 2);
        glVertex3f(a / 2, -b / 2, c / 2);
        glVertex3f(a / 2, b / 2, c / 2);

        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(a / 2, b / 2, c / 2);
        glVertex3f(a / 2, -b / 2, c / 2);
        glVertex3f(a / 2, -b / 2, -c / 2);
        glVertex3f(a / 2, b / 2, -c / 2);

        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(a / 2, b / 2, -c / 2);
        glVertex3f(a / 2, -b / 2, -c / 2);
        glVertex3f(-a / 2, -b / 2, -c / 2);
        glVertex3f(-a / 2, b / 2, -c / 2);

        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(-a / 2, b / 2, -c / 2);
        glVertex3f(-a / 2, -b / 2, -c / 2);
        glVertex3f(-a / 2, -b / 2, c / 2);
        glVertex3f(-a / 2, b / 2, c / 2);

        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(a / 2, b / 2, c / 2);
        glVertex3f(a / 2, b / 2, -c / 2);
        glVertex3f(-a / 2, b / 2, -c / 2);
        glVertex3f(-a / 2, b / 2, c / 2);

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-a / 2, -b / 2, c / 2);
        glVertex3f(-a / 2, -b / 2, -c / 2);
        glVertex3f(a / 2, -b / 2, -c / 2);
        glVertex3f(a / 2, -b / 2, c / 2);
    }
    glEnd();
}

void GLRenderer::DrawCylinder(double r, double h, int steps)
{
    double angStep = (2 * piconst) / (double)steps;
    double currAng = 0;
    glBegin(GL_QUAD_STRIP);
    {
        for (int i = 0; i < steps + 1; i++)
        {
            double x = r * cos(currAng);
            double z = -r * sin(currAng);
            double nx = x / r;
            double nz = z / r;
            glNormal3f(nx, 0.0, nz);
            glVertex3f(x, h / 2.0, z);
            glVertex3f(x, -h / 2.0, z);

            currAng += angStep;
        }
    }
    glEnd();
}

void GLRenderer::DrawColumn(double r, double h, int steps)
{
    DrawCylinder(r, h, steps);
    glPushMatrix();
    glTranslatef(0.0, h / 2.0 + 0.25 * r, 0.0);
    DrawBox(2.5 * r, 0.5 * r, 2.5 * r);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, -h / 2.0 - 0.15 * r, 0.0);
    DrawBox(3 * r, 0.3 * r, 3 * r);
    glTranslatef(0.0, -0.3 * r, 0.0);
    DrawBox(4 * r, 0.3 * r, 4 * r);
    glPopMatrix();
}

void GLRenderer::DrawTemple()
{
    glPushMatrix();
    glTranslatef(-10.5, 0.0, 4.5);
    for (int i = 0; i < 2; i++)
    {
        glPushMatrix();
        glTranslatef(0.0, 0.0, -i * 9.0);
        for (int j = 0; j < 8; j++)
        {
            glPushMatrix();
            glTranslatef(j * 3, 0.0, 0.0);
            DrawColumn(0.5, 8, 20);
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(0.0, 0.0, -3.0);
    DrawColumn(0.5, 8, 20);
    glTranslatef(0.0, 0.0, -3.0);
    DrawColumn(0.5, 8, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7 * 3, 0.0, -3.0);
    DrawColumn(0.5, 8, 20);
    glTranslatef(0.0, 0.0, -3.0);
    DrawColumn(0.5, 8, 20);
    glPopMatrix();
    glPopMatrix();

}






