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
    gluLookAt(0.00, 0.00, 20.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(NULL, NULL);
}

void GLRenderer::DrawScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, -6, 0.0);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    LoadTexture(".\\Resources\\OpenGL.bmp");
    glColor3f(0.5, 0.4, 0.2);

    glBegin(GL_LINES);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(10.0, 0.0, 0.0);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 10.0);
    }
    glEnd();

    //DrawSide(4, 5, 4, 5, 5, 3);
    //DrawBox(3, 4, 5, 5, 7, 3, 4, 9, 7);
    //DrawBasket(4, 5, 0.5);
    DrawFigure(0.5, 10, 5, 6, 30, 10, -45);

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

void GLRenderer::DrawSide(float x, float y, int nPartX, int nPartY, int nTexX, int nTexY)
{
    float xOffset = x / nPartX;
    float yOffset = y / nPartY;

    float xTexStep = (float)nTexX / (float)nPartX;
    float yTexStep = (float)nTexY / (float)nPartY;

    float currY = y / 2.0;
    float z = 0;

    float currTexY = 0.0;

    glNormal3f(0.0, 0.0, 1.0);
    for (int i = 0; i < nPartY; i++)
    {
        float currX = -x / 2.0;
        float currTexX = 0.0;
        glBegin(GL_QUAD_STRIP);
        {
            for (int i = 0; i < nPartX + 1; i++)
            {
                glTexCoord2f(currTexX, currTexY);
                glVertex3f(currX, currY, z);

                glTexCoord2f(currTexX, currTexY + yTexStep);
                glVertex3f(currX, currY - yOffset, z);

                currX += xOffset;
                currTexX += xTexStep;
            }
        }
        glEnd();

        currY -= yOffset;
        currTexY += yTexStep;
    }
}

void GLRenderer::DrawBox(float x, float y, float z, int nPartX, int nPartY, int nPartZ, int nTexX, int nTexY, int nTexZ)
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, z / 2);
    DrawSide(x, y, nPartX, nPartY, nTexX, nTexY);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, x / 2);
    DrawSide(z, y, nPartZ, nPartY, nTexZ, nTexY);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, z / 2);
    DrawSide(x, y, nPartX, nPartY, nTexX, nTexY);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, x / 2);
    DrawSide(z, y, nPartZ, nPartY, nTexZ, nTexY);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, y / 2);
    DrawSide(x, z, nPartX, nPartZ, nTexX, nTexZ);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, y / 2);
    DrawSide(x, z, nPartX, nPartZ, nTexX, nTexZ);
    glPopMatrix();
}

void GLRenderer::DrawBasket(float w, float h, float d)
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, w / 2 - d / 2);
    DrawBox(w, h, d, 10, 20, 1, 10, 20, 1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, w / 2 - d / 2);
    DrawBox(w, h, d, 10, 20, 1, 10, 20, 1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, w / 2 - d / 2);
    DrawBox(w - 2 * d, h, d, 10 - 2, 20, 1, 10 - 2, 20, 1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, w / 2 - d / 2);
    DrawBox(w - 2 * d, h, d, 10 - 2, 20, 1, 10 - 2, 20, 1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, h / 2 - d / 2);
    DrawBox(w - 2 * d, w - 2 * d, d, 10 - 2, 10 - 2, 1, 10 - 2, 10 - 2, 1);
    glPopMatrix();
}

void GLRenderer::SetMaterial(float r, float g, float b)
{
    float diffuse[] = { r, g, b, 1.0 };
    float ambient[] = { 0.5 * r, 0.5 * g, 0.5 * b, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float emission[] = { 0.0, 0.0, 0.0, 1.0 };
    int shininess = 15;

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMateriali(GL_FRONT, GL_SHININESS, shininess);
}

void GLRenderer::DrawRoller(float r, float h, int n)
{
    //glColor3f(1.0, 0.0, 0.0);
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

void GLRenderer::DrawFigure(float w, float h, float d, float r, float alpha, float beta, float gama)
{
    /*int n = 20;
    glPushMatrix();
    glRotatef(alpha, 0.0, 1.0, 0.0);
    DrawRoller(r, 2 * w, n);

    glTranslatef(0.0, w + d / 2, 0.0);
    DrawBox(w, d, w, 1, 20, 1, 1, 20, 1);

    glTranslatef(0.0, d / 2 + 0.75 * w, 0.0);
    DrawBox(1.5, 1.5, 1.5, 1, 1, 1, 1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(alpha, 0.0, 1.0, 0.0);
    glTranslatef(0.75 * w, w + d + 0.75 * w, 0.0);
    glRotatef(beta, 0.0, 0.0, 1.0);
    glTranslatef(d / 2, 0.0, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);
    DrawBox(w, d, w, 1, 20, 1, 1, 20, 1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(alpha, 0.0, 1.0, 0.0);
    glTranslatef(0.0, w + d + 0.75 * w, 0.0);
    glRotatef(beta, 0.0, 0.0, 1.0);
    glTranslatef(0.75 * w + d + 0.75 * w, 0.0, 0.0);
    glRotatef(-beta, 0.0, 0.0, 1.0);
    DrawBox(1.5, 1.5, 1.5, 1, 1, 1, 1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(alpha, 0.0, 1.0, 0.0);
    glTranslatef(0.0, w + d + 0.75 * w, 0.0);
    glRotatef(beta, 0.0, 0.0, 1.0);
    glTranslatef(0.75 * w + d + 1.5 * w, 0.0, 0.0);
    glRotatef(gama, 0.0, 0.0, 1.0);
    glTranslatef(d / 2, 0.0, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);
    DrawBox(w, d, w, 1, 20, 1, 1, 20, 1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(alpha, 0.0, 1.0, 0.0);
    glTranslatef(0.0, w + d + 0.75 * w, 0.0);
    glRotatef(beta, 0.0, 0.0, 1.0);
    glTranslatef(0.75 * w + d + 0.75 * w, 0.0, 0.0);
    glRotatef(gama, 0.0, 0.0, 1.0);
    glTranslatef(0.75 * w + d + 3 * w, 0.0, 0.0);
    glRotatef(-beta - gama, 0.0, 0.0, 1.0);
    DrawBasket(6 * w, 0.5 * h, w);
    glPopMatrix();*/

    int n = 20;
    glPushMatrix();
    glRotatef(alpha, 0.0, 1.0, 0.0);
    DrawRoller(r, 2 * w, n);

    glTranslatef(0.0, d / 2 + w, 0.0);
    DrawBox(w, d, w, 1, 20, 1, 1, 20, 1);

    glTranslatef(0.0, d / 2 + 0.75 * w, 0.0);
    DrawBox(1.5 * w, 1.5 * w, 1.5 * w, 1, 1, 1, 1, 1, 1);

    glRotatef(-90 + beta, 0.0, 0.0, 1.0);
    glTranslatef(0.0, d / 2 + 0.75 * w, 0.0);
    DrawBox(w, d, w, 1, 20, 1, 1, 20, 1);

    glTranslatef(0.0, d / 2 + 0.75 * w, 0.0);
    glRotatef(-beta + 90, 0.0, 0.0, 1.0);
    DrawBox(1.5 * w, 1.5 * w, 1.5 * w, 1, 1, 1, 1, 1, 1);

    glRotatef(-90 + gama, 0.0, 0.0, 1.0);
    glTranslatef(0.0, d / 2 + 0.75 * w, 0.0);
    DrawBox(w, d, w, 1, 20, 1, 1, 20, 1);

    glTranslatef(0.0, d / 2 + 3 * w, 0.0);
    glRotatef(90 - gama, 0.0, 0.0, 1.0);
    DrawBasket(6 * w, 0.5 * h, w);
    glPopMatrix();



}

void GLRenderer::LoadTexture(char* fileName)
{
    UINT texId;
    DImage img;
    img.Load(CString(fileName));
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_RGBA, GL_UNSIGNED_BYTE, img.GetDIBBits());
}






