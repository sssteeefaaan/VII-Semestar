#pragma once
#include "GLMaterial.h"
#define piconst acos(-1)

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
		
	bool CreateGLContext(CDC* pDC);			
	void PrepareScene(CDC* pDC);			
	void Reshape(CDC* pDC, int w, int h);	
	void DrawScene(CDC* pDC);				
	void DestroyScene(CDC* pDC);			
	void MoveCamera(CPoint cursorPoint);
	void StopMovingCamera();
	void PromeniCrvenoSvetlo();
	void PromeniPlavoSvetlo();
	void PromeniZelenoSvetlo();
	
	void PromeniNormale();

	void DrawConePart(int precision, double angle, double partLen, double radius);

	int mod(int k, int n);

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
	short rotateX;
	short rotateY;
	double cameraDistanceFromCoordinateOrigin;
	bool normalsOn;
	bool crvenoSvetlo;
	bool zelenoSvetlo;
	bool plavoSvetlo;

	void DrawHalfSphere(float r);

private:
	CPoint lastPoint;
	bool firstMouse;
	float cameraPitch;
	float camYaw;
	float camX;
	float camY;
	float camZ;

	void DrawSvetlo();
	void DrawCoordinateLines();
	void SetRoomLightning();
	void DrawPrismC(int numOfSides, double height, double radius, double* color);
	void DrawCylinder(int precision, double height, double radius, double* color);
	void DrawHalfSphere(int horizontalPrecision, int verticalPrecision, double radius, double* color);
	void DrawPrism(int numOfSides, double height, double radius, double* color);
	void DrawRoom();
	void DrawLeviZid();
	void DrawPrednjiZid();
	void DrawGornjiZid();
	void DrawDonjiZid();
	void DrawDesniZid();
	void DrawZadnjiZid();
	void DrawBase();
	void DrawVase();


};


