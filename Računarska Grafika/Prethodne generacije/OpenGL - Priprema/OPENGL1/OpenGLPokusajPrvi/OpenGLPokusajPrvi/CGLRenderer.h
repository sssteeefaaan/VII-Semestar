

class CGLRenderer
{
protected:
	HGLRC m_hrc;
private:
	
public:
	float rotacija;
	float rotacija2;
	float rotacija3;

	CGLRenderer();
	
	void DrawScene(CDC* pDC);
	void Reshape(CDC* pDC, int w, int h);
	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void DestroyScene(CDC* pDC);

	void Kocka(CDC* pDC, float a);
	void Sfera(CDC* pDC, float r);
	void Kupa(CDC* pDC, float base, float height, int slices);
	void Valjak(CDC* pDC, float r, float visina, int brDelova);

	float* normcrossprod(float v1[3], float v2[3], float out[3]);
	void normalize(float v[3]);
};



