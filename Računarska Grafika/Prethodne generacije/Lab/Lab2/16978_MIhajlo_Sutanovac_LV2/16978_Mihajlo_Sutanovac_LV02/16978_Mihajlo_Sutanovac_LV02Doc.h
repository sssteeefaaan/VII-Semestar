
// 16978_Mihajlo_Sutanovac_LV02Doc.h : interface of the CMy16978MihajloSutanovacLV02Doc class
//


#pragma once


class CMy16978MihajloSutanovacLV02Doc : public CDocument
{
protected: // create from serialization only
	CMy16978MihajloSutanovacLV02Doc() noexcept;
	DECLARE_DYNCREATE(CMy16978MihajloSutanovacLV02Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMy16978MihajloSutanovacLV02Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
