/********************************************************************
	created:	2011/08/25
	created:	25:8:2011   0:28
	filename: 	g:\Temp\GuiLib1.5\MyTest\IGuiPropertyDescriptor.h
	file path:	g:\Temp\GuiLib1.5\MyTest
	file base:	IGuiPropertyDescriptor
	file ext:	h
	author:		tgame
	
	purpose:	
*********************************************************************/
#pragma once
#ifndef _25_8_2011_IGuiPropertyDescriptor
#define _25_8_2011_IGuiPropertyDescriptor

class IGuiPropertyProvider;

enum ENPropertyDescAttrib
{
	//!是否可以编辑
	enPropertyDescReadOnlyAttrib=0x1<<1,
	//!改变时,重新绘制所有值
	enPropertyDescRedraw=0x1<<2,
};

class IGuiPropertyDescriptor
{
public:
	IGuiPropertyDescriptor(void){}
	virtual ~IGuiPropertyDescriptor(void){}

	//!获取描述
	virtual const std::string& GetDesc(void) = 0;
	//!获取显示名字
	virtual const std::string& GetDisplayName(void) = 0;
	//!获取编辑器类型
	virtual const std::string& GetEditorType(void) = 0;
	//!获取分类
	virtual const std::string& GetCategory(void)=0;

	//!是否支持标准值
	virtual bool GetStandardValuesSupported(void) = 0;
	//!返回true表示不允许用户输入标准值之外的值
	virtual bool GetStandardValuesExclusive(void) = 0;
	//!获取标准值列表
	virtual std::vector<std::string>* GetStandardValues(void) = 0;
	//!获取当前值
	virtual const std::string& GetValue(void) = 0;
	//!设置当前值
	virtual void SetValue(const std::string& value) = 0;
	//!是否只读
	virtual bool IsReadOnly(void)const=0;
	//!返回true表示修改值或者ReadOnly属性时,会导致本属性表刷新
	virtual bool CauseRefresh(void)=0;
	//!改变只读属性
	virtual void SetReadOnly(bool isReadOnly)=0;
	//!是否包含属性
	virtual bool HaveAttrib(ENPropertyDescAttrib attrib) = 0;

	//!获取子属性提供器
	virtual IGuiPropertyProvider* GetChildrenPropertyProvider(void) = 0;
};



#endif