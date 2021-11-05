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

    void DrawColumn(double side, double height);
    void DrawPyramid(double side, double height, int n);
    void Draw2Pyramid(double side, double height);
    void DrawFigure(float aS, float hS, float aR, float size, float height, float offset, float angle);
    void RotateView(int x, int y);


protected:
    HGLRC m_hrc;
    int xRot;
    int yRot;
};

