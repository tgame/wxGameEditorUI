//tgame
#pragma once
#ifndef _20121016_PropertywxConnector_
#define _20121016_PropertywxConnector_

class wxPropertyGrid;
class MyPGProperty;

class PropertywxConnector
{
public:
	PropertywxConnector(void);
	~PropertywxConnector(void);
	void AssignwxControl(wxPropertyGrid* grid);
	void Update(void);
	void ShowPropertyProvider(IGuiPropertyProvider* provider);
protected:
	void AddChildPropertyProvider(MyPGProperty* parent,IGuiPropertyProvider* provider);
	wxPropertyGrid*	m_wxGrid;
	IGuiPropertyProvider*	m_currentProvider;
};





#endif