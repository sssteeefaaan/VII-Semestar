#include "pch.h"
#include "GLRenderer.h"
#include "DImage.h"
#include <gl\GL.h>
#include <gl\GLU.h>

GLRenderer::GLRenderer(void)
{
    rotX = 0;
    rotY = 0;
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
    //glEnable(GL_TEXTURE_2D);
    double l = 0;

    float ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    float diffuse[] = { 0.7, 0.7, 0.0, 1.0 }; //pise da se nalazi usmereni izvor svetlosti, zute boje
    float specular[] = { 1.0, 1.0, 0.6, 1.0 }; // sto 0.6, tj. sto uopste ove vrednosti?
    GLfloat position[] = { 5.0, 5.0, 10.0, 1.0 };  // usmeren je ka tacki koja je 10 jedinica ispred postamtraca??? sta znaci to?
    float direction[] = { -5.0, -5.0, -10.0 }; // ovo il ono dole sto kaze ugao kupe koji definise osvetljeni prostor je 20 stepeni
                                                // pogled posmatraca je usmeren u centru torusa koji se otkotrljao duz x ose za 20 jedinica ???????/
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);


    double theta = atan(l / 10);   // cemu sluzi ovo??

    glRotatef(theta * (180 / piconst), 0.0, 1.0, 0.0);  // i bez to daje istu sliku

    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(rotX, 1.0, 0.0, 0.0);
    glRotatef(rotY, 0.0, 1.0, 0.0);

    SetThorusMat();
    /*int t = LoadTexture(".\\Resources\\brick.png");
    glBindTexture(GL_TEXTURE_2D, t);*/
    RotateThorus(l);

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

void GLRenderer::DrawThorus(double R, double r)
{
    int n = 50;   // sta je n??
    double currB = 0;
    double angleStep = (2 * piconst) / n;

    double* vertices = new double[(n + 1) * (n + 1) * 3]; // sto ima ovoliko ovih tacaka i kod normala i kod tex?
    double* normals = new double[(n + 1) * (n + 1) * 3];
    double* textures = new double[(n + 1) * (n + 1) * 2];
    UINT* indices = new UINT[n * n * 4];

    double textureStep = 1.0 / (float)n;

    for (int i = 0; i < n + 1; i++)
    {
        double currA = 0;
        for (int j = 0; j < n + 1; j++)
        {
            double nextA = currA + angleStep;
            double nextB = currB + angleStep;
            int baseInd = i * (n + 1) * 3 + j * 3;

            vertices[baseInd] = (R + r * cos(currA)) * cos(currB);
            vertices[baseInd + 1] = (R + r * cos(currA)) * sin(currB);
            vertices[baseInd + 2] = -r * sin(currA);

            normals[baseInd] = cos(currA) * cos(currB);
            normals[baseInd + 1] = cos(currA) * sin(currB);
            normals[baseInd + 2] = -sin(currA);

            int baseTexInd = i * (n + 1) * 2 + j * 2;
            textures[baseTexInd] = i * textureStep;
            textures[baseTexInd + 1] = j * textureStep;

            currA += angleStep;
        }
        currB += angleStep;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int baseInd = i * n * 4 + j * 4;  //??????
            indices[baseInd] = i * (n + 1) + j;
            indices[baseInd + 1] = indices[baseInd] + 1;
            indices[baseInd + 3] = (i + 1) * (n + 1) + j;
            indices[baseInd + 2] = indices[baseInd + 3] + 1;
            int a = 2;
        }
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glNormalPointer(GL_DOUBLE, 0, normals);
    glTexCoordPointer(2, GL_DOUBLE, 0, textures);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);
    glDrawElements(GL_QUADS, n * n * 4, GL_UNSIGNED_INT, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GLRenderer::RotateView(int x, int y)
{
    rotX += x;
    if (rotX > 360)
        rotX -= 360;
    else if (rotX < 0)
        rotX += 360;

    rotY += y;
    if (rotY > 360)
        rotY -= 360;
    else if (rotY < 0)
        rotY += 360;
}

UINT GLRenderer::LoadTexture(char* fileName)
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
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_RGBA, GL_UNSIGNED_BYTE, img.GetDIBBits());
    return texId;
}

void GLRenderer::SetThorusMat()
{
    float ambient[] = { 0.2, 0.0, 0.2, 1.0 }; // "vrlo tamna ambijetalna komponenta" gde smo postavili ljubicastu boju?
    float diffuse[] = { 0.8, 0.0, 0.8, 1.0 }; //ovde?
    float specular[] = { 1.0, 0.6, 1.0, 1.0 };
    int shininess = 120;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMateriali(GL_FRONT, GL_SHININESS, shininess);
}

void GLRenderer::RotateThorus(double L)
{
    glTranslatef(L, 0.0, 0.0);
    double R = 2; //ovo znaci iz DRAWScene teksta, da se otkotrljao za 20 jedinica?
    double angle = L / R;
    glRotatef(-angle, 0.0, 0.0, 1.0);
    DrawThorus(R, 0.5);
}






