#include "stdafx.h"
#include "PropertyHelperFunc.h"



std::string& MyStringFormat(std::string& result,const char* pszFormat, ... )
{
	char* buf = (char*)new char[32*1024];
	va_list argList;
	va_start( argList, pszFormat );
	//vsprintf_s
	int spSize = vsnprintf( buf,1024*32*sizeof(char), pszFormat, argList );
	result.assign(buf,spSize);
	va_end( argList );
	delete []buf;
	return result;
}
std::string& MyStringAppendFormat(std::string& result,const char* pszFormat, ... )
{
	char* buf = (char*)new char[32*1024];
	va_list argList;
	va_start( argList, pszFormat );
	int spSize = vsnprintf( buf,1024*32*sizeof(char), pszFormat, argList );
	result.append(buf,spSize);
	////#else
	//int spSize=wvnsprintf( m_buf,255*sizeof(CharType),pszFormat, argList );
	////#endif
	va_end( argList );
	delete []buf;
	return result;
}

enum ENParser_State_GuiPropertyEditorColorSlider
{
	enParser_State_ValueNumber,
	enParser_State_MinMaxStep,
	enParser_State_MinNumber,
	enParser_State_MaxNumber,
	enParser_State_StepNumber,
	enParser_State_End,
};
void PropertyHelperFunc::StringToFloatArray(std::vector<ColorSliderParam>& output,const std::string& str)
{
	output.clear();
	ColorSliderParam param;
	
	std::string number;
	unsigned int curOperatorParamIdx=0;
	ENParser_State_GuiPropertyEditorColorSlider state = enParser_State_ValueNumber;
	for (unsigned int i=0;i<str.size();++i)
	{
		if (enParser_State_End==state)
		{
			break;
		}
		switch (state)
		{
		case enParser_State_ValueNumber:
			if (str[i] ==',')
			{
				param.m_value=atof(number.c_str());
				output.push_back(param);
				number.clear();
			}
			else if (str[i]=='=')
			{
				param.m_value=atof(number.c_str());
				output.push_back(param);
				number.clear();
				state=enParser_State_MinMaxStep;
				curOperatorParamIdx=0;
			}
			else
			{
				number.push_back(str[i]);
			}
			break;
		case enParser_State_MinMaxStep:
			if (str[i]=='{')
			{
				state=enParser_State_MinNumber;
			}
			break;
		case enParser_State_MinNumber:
			if (str[i] ==',')
			{
				ColorSliderParam& editParam = output[curOperatorParamIdx];
				editParam.m_minValue=atof(number.c_str());
				number.clear();
				state = enParser_State_MaxNumber;
			}
			else
			{
				number.push_back(str[i]);
			}
			break;
		case enParser_State_MaxNumber:
			if (str[i] ==',')
			{
				ColorSliderParam& editParam = output[curOperatorParamIdx];
				editParam.m_maxValue=atof(number.c_str());
				number.clear();
				state = enParser_State_StepNumber;
			}
			else
			{
				number.push_back(str[i]);
			}
			break;
		case enParser_State_StepNumber:
			if (str[i] ==','||str[i]=='}')
			{
				ColorSliderParam& editParam = output[curOperatorParamIdx];
				editParam.m_stepValue=atof(number.c_str());
				number.clear();
				curOperatorParamIdx++;
				if (curOperatorParamIdx<output.size())
				{
					state = enParser_State_MinMaxStep;
				}
				else
				{
					state=enParser_State_End;
				}
			}
			else
			{
				number.push_back(str[i]);
			}
			break;
		}
	}
	if (enParser_State_ValueNumber==state && !number.empty())
	{
		param.m_value=atof(number.c_str());
		output.push_back(param);
		number.clear();
	}
}
void PropertyHelperFunc::FloatArrayToString(const std::vector<ColorSliderParam>& output,std::string& str)
{
	std::string valueField;
	std::string ruleField;
	for (unsigned int i=0;i<output.size();i++)
	{
		const ColorSliderParam& param = output[i];
		if (i!=0)
		{
			valueField+=",";
			ruleField+=",";
		}
		MyStringAppendFormat(valueField,"%g",param.m_value);
		MyStringAppendFormat(ruleField,"{%g,%g,%g}",param.m_minValue,param.m_maxValue,param.m_stepValue);
	}
	valueField+="=";
	valueField+=ruleField;
	str = valueField;
}
void PropertyHelperFunc::StringToColor(std::vector<ColorSliderParam>& output,const std::string& str)
{
	int v[4]={0,0,0,0};
	unsigned int argb = 0;
	sscanf(str.c_str(),"%8x",&argb);

	v[0] = (argb&0xFF000000)>>24;
	v[1] = (argb&0x00FF0000)>>16;
	v[2] = (argb&0x0000FF00)>>8;
	v[3] = argb&0x000000FF;
	output.resize(4);
	for (unsigned int i=0;i<4;i++)
	{
		output[i].m_minValue=0.0;
		output[i].m_maxValue=1.0;
		output[i].m_stepValue=1.0/255.0;
		output[i].m_value=(double)v[(i+1)%4]/255.0;
	}
}
void PropertyHelperFunc::ColorToString(const std::vector<ColorSliderParam>& output,std::string& str)
{
	int v[4]={0,0,0,0};
	for (unsigned int i=0;i<output.size();i++)
	{
		const ColorSliderParam& param = output[i];
		v[(i+1)%4] = param.m_value*255.0;
	}
	char buf[250]="";
	//std::string value;
	//value.Format("%.2X%.2X%.2X%.2X",v[0],v[1],v[2],v[3]);
	sprintf(buf,"%.2X%.2X%.2X%.2X",v[0],v[1],v[2],v[3]);
	str=buf;
}


