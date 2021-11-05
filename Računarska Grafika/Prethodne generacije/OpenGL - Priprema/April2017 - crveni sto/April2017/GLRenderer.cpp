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
    gluLookAt(0.00, 0.00, 15.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DrawScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);

    PrepareTextures(CString(".\\Resources\\OpenGL.bmp"));

    //DrawRoller(1, 3, 20);
    CString texs[2];
    DrawFigure(4, 0.7, piconst / 4, piconst / 4, 1, texs);

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

void GLRenderer::DrawRoller(float r, float h, int n)
{
    glColor3f(1.0, 0.0, 0.0);
    float angleStep = (piconst * 2) / n;
    float texStep = 1.0 / (float)n;
    float currAngle = 0;
    float currTex = 0;

    glBegin(GL_QUAD_STRIP);
    {
        for (int i = 0; i < n + 1; i++)
        {
            float x = r * cos(currAngle);
            float z = -r * sin(currAngle);

            glNormal3f(x / r, 0, z / r);

            glTexCoord2f(currTex, 0);
            glVertex3f(x, h / 2, z);

            glTexCoord2f(currTex, 1);
            glVertex3f(x, -h / 2, z);

            currAngle += angleStep;
            currTex += texStep;
        }
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);

    currAngle = 0;
    glBegin(GL_TRIANGLE_FAN);
    {
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, h / 2, 0.0);

        for (int i = 0; i < n + 1; i++)
        {
            float x = r * cos(currAngle);
            float z = -r * sin(currAngle);

            glVertex3f(x, h / 2, z);

            currAngle += angleStep;
        }
    }
    glEnd();

    currAngle = 0;
    glBegin(GL_TRIANGLE_FAN);
    {
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, -h / 2, 0.0);

        for (int i = 0; i < n + 1; i++)
        {
            float x = r * cos(currAngle);
            float z = r * sin(currAngle);

            glVertex3f(x, -h / 2, z);

            currAngle += angleStep;
        }
    }
    glEnd();

    glEnable(GL_TEXTURE_2D);
}

void GLRenderer::PrepareTextures(CString strTex)
{
    UINT texId;
    DImage img;
    img.Load(strTex);
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_RGBA, GL_UNSIGNED_BYTE, img.GetDIBBits());
}

void GLRenderer::DrawFigure(float h, float dx, float alpha, float beta, float dt, CString arTex[])
{
    int n = 20;

    glPushMatrix();
    glRotatef(dt * (alpha * (180 / piconst)), 0.0, 1.0, 0.0);
    DrawRoller(dx, 0.2 * h, n);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -0.2 * h, 0.0);
    glRotatef(dt * (alpha * (180 / piconst)), 0.0, 1.0, 0.0);
    DrawRoller(10 * dx, 0.2 * h, n);
    glPopMatrix();

    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glTranslatef(0.0, -0.1 * h - 0.2 * h - h / 2, 0.0);
        glRotatef(dt * (alpha * (180 / piconst)) + i * 90, 0.0, 1.0, 0.0);
        glTranslatef(3 * dx, 0.0, 0.0);
        glRotatef(dt * (beta * (180 / piconst)), 0.0, 1.0, 0.0);

        DrawRoller(dx, h, n);

        glTranslatef(0.0, -h / 2 - 0.1 * h, 0.0);
        DrawRoller(2 * dx, 0.2 * h, n);
        glPopMatrix();
    }

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






