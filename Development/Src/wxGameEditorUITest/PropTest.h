
namespace _Test
{
	class TestPropertyDesc
		:public IGuiPropertyDescriptor
	{
	public:
		std::string m_editorType;
		std::string m_value;
		std::string m_category;
		std::string m_name;
		std::vector<std::string>	m_stdValues;
		TestPropertyDesc(void){
			m_value="我是字符串";
			m_editorType="Editbox";
		}
		//!获取描述
		virtual const std::string& GetDesc(void){
			static std::string d("这里显示描述");
			return d;
		}
		//!获取显示名字
		virtual const std::string& GetDisplayName(void){
			static std::string d("属性名字");
			return m_name;
		}
		//!获取编辑器类型
		virtual const std::string& GetEditorType(void){
			return m_editorType;
		}
		virtual const std::string& GetCategory(void){
			return m_category;
		}


		//!是否支持标准值
		virtual bool GetStandardValuesSupported(void){
			return !m_stdValues.empty();
		}

		//!返回true表示不允许用户输入标准值之外的值
		virtual bool GetStandardValuesExclusive(void){
			return false;
		}
		//!获取标准值列表
		virtual std::vector<std::string>* GetStandardValues(void){
			return &m_stdValues;
		}
		//!获取当前值
		virtual const std::string& GetValue(void){
			return m_value;
		}
		//!设置当前值
		virtual void SetValue(const std::string& value){
			m_value = value;
		}
		//!是否只读
		virtual bool IsReadOnly(void)const{
			return false;
		}
		//!返回true表示修改值或者ReadOnly属性时,会导致本属性表刷新
		virtual bool CauseRefresh(void){
			return false;
		}
		//!改变只读属性
		virtual void SetReadOnly(bool isReadOnly){
			
		}
		virtual bool HaveAttrib(ENPropertyDescAttrib attrib){
			return false;
		}
		//!获取子属性提供器
		virtual IGuiPropertyProvider* GetChildrenPropertyProvider(void){ 
			return 0;}
	protected:
	private:
	};

	class TestPropertyProvider
		:public IGuiPropertyProvider
	{
		std::vector<IGuiPropertyDescriptor*>	m_props;
	public:
		TestPropertyProvider(void)
		{
			std::vector<std::string> stdValues;
			for (unsigned int i=0;i<3;i++)
			{
				TestPropertyDesc* prop =new TestPropertyDesc;
				prop->m_name="文本属性";
				prop->m_category="文本分组";
				char buf[128];
				sprintf(buf,"SSS文本Value_%d",i);
				prop->m_value=buf;
				stdValues.push_back(prop->m_value);
				prop->m_stdValues=stdValues;
				m_props.push_back(prop);
			}
			const char* v[]={"FF00FF00","FF0000FF","FFFF0000","FF000000","FFFFFFFF"};
			for (unsigned int i=0;i<1;i++)
			{
				TestPropertyDesc* prop =new TestPropertyDesc; 
				prop->m_editorType = "ColorSlider";
				prop->m_value=v[i];
				prop->m_category="颜色分组";
				prop->m_name="颜色属性";
				m_props.push_back(prop);
			}
			const char* vFloatArray[2]={"3.13,0.13={1,20,1},{0.0,1.0,0.01}"
				,"3.13={1,20,1}"};
			for (unsigned int i=0;i<1;i++)
			{
				TestPropertyDesc* prop =new TestPropertyDesc; 
				prop->m_editorType = "FloatSlider";
				prop->m_value=vFloatArray[i];
				prop->m_category="浮点数分组";
				prop->m_name="浮点数属性";
				m_props.push_back(prop);
			}
		}
		virtual std::vector<IGuiPropertyDescriptor*>& GetDesciptorList(void)
		{
			return m_props;
		}
		virtual void Update(void){}
	};
}
using namespace _Test;