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

    UINT LoadTexture(char* fileName);
    void DrawCube(double a);
    void DrawTube(double r1, double r2, double h, int n);
    void DrawCone(double r, double h, int n);
    void DrawCone2(double r, double h, int n);
    void DrawPaddle(double length, double width);
    void RotateView(int xAngle, int yAngle);
    void RotatePaddles(int angle);
    float toRad(float angle);

protected:
    HGLRC m_hrc;
    UINT envTex;
    UINT brickTex;
    int xRotAngle;
    int yRotAngle;
    float pi;
    int paddleRotAngle;
};

