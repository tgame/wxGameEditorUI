//tgame
#ifndef _H_20121017_PropertyHelperFunc
#define _H_20121017_PropertyHelperFunc



struct ColorSliderParam 
{
	double m_value;
	double m_minValue;
	double m_maxValue;
	double m_stepValue;
};

class PropertyHelperFunc
{
public:
	static void StringToFloatArray(std::vector<ColorSliderParam>& output,const std::string& str);
	static void FloatArrayToString(const std::vector<ColorSliderParam>& output,std::string& str);
	static void StringToColor(std::vector<ColorSliderParam>& output,const std::string& str);
	static void ColorToString(const std::vector<ColorSliderParam>& output,std::string& str);
};









#endif