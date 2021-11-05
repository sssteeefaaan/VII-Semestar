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
    void DrawSide(float x, float y, int nPartX, int nPartY, int nTexX, int nTexY);
    void DrawBox(float x, float y, float z, int nPartX, int nPartY, int nPartZ, int nTexX, int nTexY, int nTexZ);
    void DrawBasket(float w, float h, float d);
    void SetMaterial(float r, float g, float b);
    void DrawRoller(float r, float h, int n);
    void DrawFigure(float w, float h, float d, float r, float alpha, float beta, float gama);
    void LoadTexture(char* fileName);


protected:
    HGLRC m_hrc;
    int xRot;
    int yRot;
};

