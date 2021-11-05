#pragma once
#include "GLMaterial.h"
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

    void RotateView(CPoint* newPoint);
    inline void SetCurrentPt(CPoint* pt)
    {
        currentPt->x = pt->x;
        currentPt->y = pt->y;
    }
    inline void ToggleRed()
    {
        redOn = !redOn;
    }
    inline void ToggleGreen()
    {
        greenOn = !greenOn;
    }
    inline void ToggleBlue()
    {
        blueOn = !blueOn;
    }
    inline void ToggleNormals()
    {
        normalsOn = !normalsOn;
    }



    void SetMemAngles();

    void DrawHalfSphere(int horizontalPrecision, int verticalPrecision, double radius, double* color);
    void DrawSphere(int horizontalPrecision, int verticalHalfPrecision, double radius, double* color);
    void DrawPrismC(int numOfSides, double height, double radius, double* color);
    void DrawPrism(int numOfSides, double height, double radius, double* color);
    void DrawCylinder(int precision, double height, double radius, double* color);
    void DrawConePart(int precision, double angle, double partLen, double radius);
    void DrawWall(double height, double width, double heightPrecision, double widthPrecision);
    void DrawWallPart(double quadHeight, double quadWidth, double quadNum, double startingHeight);
    void DrawTry(int numOfSides, double height, double radius, double* color);

protected:
    HGLRC m_hrc;
    double xRotationAngle;
    double yRotationAngle;
    double memXRotationAngle;
    double memYRotationAngle;
    double yOffset;
    CPoint* currentPt;

    bool redOn, greenOn, blueOn, normalsOn;
};

