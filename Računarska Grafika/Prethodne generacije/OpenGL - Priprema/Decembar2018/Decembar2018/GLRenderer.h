#pragma once
#define piconst acos(-1)

class GLRenderer
{
public:
    GLRenderer(void);
    virtual ~GLRenderer(void);

    bool CreateGLContext(CDC* pDC);
    void PrepareScene(CDC* pDC);
    void Reshape(CDC* pDC, int w, int h);
    void DrawScene(CDC* pDC);
    void DestroyScene(CDC* pDC);

    void RotateScene(int x, int y);
    void SetLight();
    void DrawBox(double a, double b, double c);
    void DrawCylinder(double r, double h, int steps);
    void DrawColumn(double r, double h, int steps);
    void DrawTemple();

protected:
    HGLRC m_hrc;
    int xRot, yRot;
};

