/********************************************************************
	created:	2011/08/25
	created:	25:8:2011   0:27
	filename: 	g:\Temp\GuiLib1.5\MyTest\IGuiPropertyProvider.h
	file path:	g:\Temp\GuiLib1.5\MyTest
	file base:	IGuiPropertyProvider
	file ext:	h
	author:		tgame
	
	purpose:	
*********************************************************************/
#pragma once
#ifndef _25_8_2011_IGuiPropertyProvider
#define _25_8_2011_IGuiPropertyProvider

class IGuiPropertyDescriptor;

class IGuiPropertyProvider
{
public:
	IGuiPropertyProvider(void){}
	virtual ~IGuiPropertyProvider(void){}

	virtual std::vector<IGuiPropertyDescriptor*>& GetDesciptorList(void)=0;
	virtual void Update(void)=0;
};



#endif