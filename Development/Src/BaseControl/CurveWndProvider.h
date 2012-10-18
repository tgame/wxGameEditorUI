///////////////////////////////////////////////////////////////	
//	
// FileName :  d:\Codes\MFC\CCurveDlg -  Project\CurveWndProvider.h
// Creator  :  tgame
// Date    	:  2012/04/03
// Comment  :  
//	
///////////////////////////////////////////////////////////////	
#pragma once
#ifndef H_2012_3_4_CurveWndProvider
#define H_2012_3_4_CurveWndProvider

#include "CoreGraphics/EngineMath/GEMath.h"

struct CurveWndKnotPoint
{
	float x;
	float y;
};
//Knot Class
class CurveWndKnot
{
public :
	float  x;
	float  y;
	DWORD dwData;
public :
	CurveWndKnot() : x(0), y(0), dwData(true) {}	//Constructors	
	CurveWndKnot(int ptX, int ptY):x(ptX), y(ptY), dwData(0)  {}

	void SetPoint(wxPoint pt)  {	x = pt.x; y = pt.y;}	//Setting
	void SetData(DWORD data)  { dwData = data;}
	void GetPoint(LPPOINT pt) { pt->x = x; pt->y = y;}	//Extraction
	void GetPoint(CurveWndKnotPoint* pt) { pt->x = x; pt->y = y;}	//Extraction
};

//!
class _CommoneEditor_Export_ CurveWndProvider
{
public:
	CurveWndProvider(void);
	~CurveWndProvider(void);
	void ChangeViewport(CRect* rc){
		m_viewportRect = *rc;
	}

	virtual size_t GetKnotCount(void)=0;
	virtual CurveWndKnot* GetKnot(size_t idx)=0;
	virtual unsigned int GetCurveY(unsigned int x)=0;
	virtual unsigned int InsertKnot(wxPoint& point)=0;
	virtual void RemoveKnot(size_t idx)=0;
	virtual void MoveKnot(CurveWndKnotPoint pt, size_t idx)=0;
protected:
	CRect	m_viewportRect;
	float ViewX2Time(float x){
		return (float)(x-m_viewportRect.left)/(float)m_viewportRect.Width();
	}
	float Time2ViewX(float t){
		return t*(float)m_viewportRect.Width()+m_viewportRect.left;
	}
	float ViewY2Value(float y){
		return 1.0f-(float)(y-m_viewportRect.top)/(float)m_viewportRect.Height();
	}
	float Value2ViewY(float v){
		return ((1.0f-v)*(float)m_viewportRect.Height()+m_viewportRect.top);
	}
};

class FInterpCurveWndProvider
	:public CurveWndProvider
{
	CurveWndKnot	m_knotTemp;
public:
	void CreateTestCurve(void){
		m_curveImpl = new FInterpCurve<float>;
		m_curveImpl->AddPoint(0.0f,0.0f);
		m_curveImpl->m_points[0].InterpMode=CIM_CurveAuto;
		m_curveImpl->AddPoint(1.0f,1.0f);
		m_curveImpl->m_points[1].InterpMode=CIM_CurveAuto;
	}
	FInterpCurve<float>* m_curveImpl;
	virtual size_t GetKnotCount(void){
		return m_curveImpl->m_points.size();
	}
	virtual CurveWndKnot* GetKnot(size_t idx){
		if (idx<m_curveImpl->m_points.size())
		{
			FInterpCurvePoint<float>& p = m_curveImpl->m_points[idx];
			m_knotTemp.dwData = 0;
			m_knotTemp.x = Time2ViewX(p.InVal);
			m_knotTemp.y = Value2ViewY(p.OutVal);
			float inV = ViewX2Time(m_knotTemp.x);
			float outV = ViewY2Value(m_knotTemp.y);
			return &m_knotTemp;
		}
		return &m_knotTemp;
	}
	virtual unsigned int GetCurveY(unsigned int x){
		float t = ViewX2Time(x);
		float defaultValue = 1.0f;
		float v = m_curveImpl->Eval(t,defaultValue);
		return Value2ViewY(v);
	}
	virtual unsigned int InsertKnot(wxPoint& point){
		float t = ViewX2Time(point.x);
		float v = ViewY2Value(point.y);
		unsigned int idx = m_curveImpl->AddPoint(t,v);
		FInterpCurvePoint<float>& p = m_curveImpl->m_points[idx];
		p.InterpMode = CIM_CurveAuto;
		return idx;
	}
	virtual void RemoveKnot(size_t idx){
		m_curveImpl->m_points.erase_keep_order(idx);
	}
	virtual void MoveKnot(CurveWndKnotPoint pt, size_t idx){
		float t = ViewX2Time(pt.x);
		float v = ViewY2Value(pt.y);
		unsigned int idxMoved = m_curveImpl->MovePoint(idx,t);
		FInterpCurvePoint<float>& p = m_curveImpl->m_points[idxMoved];
		p.OutVal = v;
	}
};



#endif