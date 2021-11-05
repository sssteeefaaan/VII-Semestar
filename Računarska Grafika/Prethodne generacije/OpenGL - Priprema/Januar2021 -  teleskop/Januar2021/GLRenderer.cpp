#include "pch.h"
#include "GLRenderer.h"
#include "DImage.h"
#include <gl\GL.h>
#include <gl\GLU.h>

GLRenderer::GLRenderer(void)
{
    xRot = 0;
    yRot = 0;
    alpha = 30;
    dHolder = 2;
    dHidden = 0;
    dVizor = 0;
    angleVer = 0;
    angleHor = 0;
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
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::Reshape(CDC* pDC, int w, int h)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, (double)w / (double)h, 0.1, 100);
    //gluLookAt(0.00, 0.00, 10.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
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

    float position[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);

    //DrawCylinder(0.5, 4, 20, 5);
    DrawTelescope(0.5, 4, 20, 5);

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

void GLRenderer::DrawCylinder(float r, float h, float nr, float nh, bool axes)
{
    float texStepY = 1.0 / nh;
    float texStepX = 1.0 / nr;
    float texY = 0;
    float angStep = (2 * piconst) / nr; //za x i z(i nalazenje normala)
   // float yStep = h / nh;
    //float startY = (((int)nh % 2) == 0) ? (((int)nh / 2) * yStep) : (((int)nh / 2) + 0.5) * yStep;
   // float currY = startY;
    for (int i = 0; i < nh; i++)
    {
        float currAng = 0;
        float texX = 0;
        glBegin(GL_QUAD_STRIP);
        {
            for (int j = 0; j < nr + 1; j++)
            {
                float x = r * cos(currAng);
                float z = -r * sin(currAng);
                float nx = x / r;
                float nz = z / r;
                glNormal3f(nx, 0, nz);
                glTexCoord2f(texX, texY);
                glVertex3f(x, h/2, z);
                glTexCoord2f(texX, texY + texStepY);
                glVertex3f(x, -h/2, z);
                texX += texStepX;
                currAng += angStep;
            }
        }
        glEnd();
        texY += texStepY;
       // currY -= yStep;
    }

    glBegin(GL_TRIANGLE_FAN);
    {
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, h / 2, 0);
        float currAng = 0;
        for (int i = 0; i < nr + 1; i++)
        {
            float x = r * cos(currAng);
            float z = -r * sin(currAng);
            float texX = 0.5 + 0.5 * cos(currAng); //zasto ovo prvo 0.5 + za x i - za y?? i sto uopste koristimo 0.5???
            texY = 0.5 - 0.5 * sin(currAng);
            glTexCoord2f(texX, texY);
            glVertex3f(x, h / 2, z);
            currAng += angStep;
        }
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    {
        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, -h / 2, 0);
        float currAng = 0;
        for (int i = 0; i < nr + 1; i++)
        {
            float x = r * cos(currAng);
            float z = r * sin(currAng);
            float texX = 0.5 + 0.5 * cos(currAng);
            texY = 0.5 - 0.5 * sin(currAng);
            glTexCoord2f(texX, texY);
            glVertex3f(x, -h / 2, z);
            currAng += angStep;
        }
    }
    glEnd();

    if(axes)
    {
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);
        {
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(r + 1, 0.0, 0.0);

            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, h / 2 + 1, 0.0);

            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, r + 1);
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }
}

void GLRenderer::DrawTelescope(float r, float h, float nr, float nh)
{
    for (int i = 0; i < 3; i++)
    {
        glPushMatrix();
        glRotatef(i * 120, 0.0, 1.0, 0.0);
        glRotatef(alpha, 1.0, 0.0, 0.0);
        glTranslatef(0.0, -0.6 * h, 0.0);
        DrawCylinder(0.1 * r, 1.2 * h, nr, nh, false);
        glPopMatrix();
    }

    glPushMatrix();
    glRotatef(-90, 0.0, 0.0, 1.0);
    glRotatef(angleHor, 1.0, 0.0, 0.0);
    glRotatef(angleVer, 0.0, 0.0, 1.0);
    glTranslatef(0.0, (h / 2) - dHolder, 0.0);
    DrawCylinder(r, h, nr, nh, true);
    glPushMatrix();
    glTranslatef(0.0, h / 2 + 0.4 * h - dHidden, 0.0);
    DrawCylinder(0.8 * r, 0.8 * h, nr, nh, false);
    glPopMatrix();
    glTranslatef(0.0, -h / 2 + dVizor, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    glTranslatef(0.0, (0.2 / 2.0) * h, 0.0);
    DrawCylinder(0.1 * r, 0.2 * h, nr, nh, false);
    glTranslatef(0.0, (0.2 / 2.0) * h + (0.1 / 2.0) * r, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);
    DrawCylinder(0.1 * r, 0.3 * h, nr, nh, false);
    glPopMatrix();
}






