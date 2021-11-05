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
    void DrawPatch(double R, int n);
    void DrawPatch2(double R, int n);
    void DrawPatchA(double R, int n);
    void DrawEarth(double R, int tes);
    void DrawMoon(double R, int tes);
    void DrawSpace(double R, int tes);
    void RotateView(int xAngle, int yAngle);
    void Zoom(float zoomAmount);
    void RotateMoon(int yAngle);
    void inline ToggleLight()
    {
        lightOn = !lightOn;
    }


protected:
    HGLRC m_hrc;
    UINT T[6];
    UINT S[6];
    UINT M[6];
    int xRotationAngle;
    int yRotationAngle;
    float zoom;
    int moonYRotationAngle;
    bool lightOn;
};

