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
	//!�Ƿ���Ա༭
	enPropertyDescReadOnlyAttrib=0x1<<1,
	//!�ı�ʱ,���»�������ֵ
	enPropertyDescRedraw=0x1<<2,
};

class IGuiPropertyDescriptor
{
public:
	IGuiPropertyDescriptor(void){}
	virtual ~IGuiPropertyDescriptor(void){}

	//!��ȡ����
	virtual const std::string& GetDesc(void) = 0;
	//!��ȡ��ʾ����
	virtual const std::string& GetDisplayName(void) = 0;
	//!��ȡ�༭������
	virtual const std::string& GetEditorType(void) = 0;
	//!��ȡ����
	virtual const std::string& GetCategory(void)=0;

	//!�Ƿ�֧�ֱ�׼ֵ
	virtual bool GetStandardValuesSupported(void) = 0;
	//!����true��ʾ�������û������׼ֵ֮���ֵ
	virtual bool GetStandardValuesExclusive(void) = 0;
	//!��ȡ��׼ֵ�б�
	virtual std::vector<std::string>* GetStandardValues(void) = 0;
	//!��ȡ��ǰֵ
	virtual const std::string& GetValue(void) = 0;
	//!���õ�ǰֵ
	virtual void SetValue(const std::string& value) = 0;
	//!�Ƿ�ֻ��
	virtual bool IsReadOnly(void)const=0;
	//!����true��ʾ�޸�ֵ����ReadOnly����ʱ,�ᵼ�±����Ա�ˢ��
	virtual bool CauseRefresh(void)=0;
	//!�ı�ֻ������
	virtual void SetReadOnly(bool isReadOnly)=0;
	//!�Ƿ��������
	virtual bool HaveAttrib(ENPropertyDescAttrib attrib) = 0;

	//!��ȡ�������ṩ��
	virtual IGuiPropertyProvider* GetChildrenPropertyProvider(void) = 0;
};



#endif