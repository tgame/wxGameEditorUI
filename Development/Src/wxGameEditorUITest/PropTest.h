
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
			m_value="�����ַ���";
			m_editorType="Editbox";
		}
		//!��ȡ����
		virtual const std::string& GetDesc(void){
			static std::string d("������ʾ����");
			return d;
		}
		//!��ȡ��ʾ����
		virtual const std::string& GetDisplayName(void){
			static std::string d("��������");
			return m_name;
		}
		//!��ȡ�༭������
		virtual const std::string& GetEditorType(void){
			return m_editorType;
		}
		virtual const std::string& GetCategory(void){
			return m_category;
		}


		//!�Ƿ�֧�ֱ�׼ֵ
		virtual bool GetStandardValuesSupported(void){
			return !m_stdValues.empty();
		}

		//!����true��ʾ�������û������׼ֵ֮���ֵ
		virtual bool GetStandardValuesExclusive(void){
			return false;
		}
		//!��ȡ��׼ֵ�б�
		virtual std::vector<std::string>* GetStandardValues(void){
			return &m_stdValues;
		}
		//!��ȡ��ǰֵ
		virtual const std::string& GetValue(void){
			return m_value;
		}
		//!���õ�ǰֵ
		virtual void SetValue(const std::string& value){
			m_value = value;
		}
		//!�Ƿ�ֻ��
		virtual bool IsReadOnly(void)const{
			return false;
		}
		//!����true��ʾ�޸�ֵ����ReadOnly����ʱ,�ᵼ�±����Ա�ˢ��
		virtual bool CauseRefresh(void){
			return false;
		}
		//!�ı�ֻ������
		virtual void SetReadOnly(bool isReadOnly){
			
		}
		virtual bool HaveAttrib(ENPropertyDescAttrib attrib){
			return false;
		}
		//!��ȡ�������ṩ��
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
				prop->m_name="�ı�����";
				prop->m_category="�ı�����";
				char buf[128];
				sprintf(buf,"SSS�ı�Value_%d",i);
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
				prop->m_category="��ɫ����";
				prop->m_name="��ɫ����";
				m_props.push_back(prop);
			}
			const char* vFloatArray[2]={"3.13,0.13={1,20,1},{0.0,1.0,0.01}"
				,"3.13={1,20,1}"};
			for (unsigned int i=0;i<1;i++)
			{
				TestPropertyDesc* prop =new TestPropertyDesc; 
				prop->m_editorType = "FloatSlider";
				prop->m_value=vFloatArray[i];
				prop->m_category="����������";
				prop->m_name="����������";
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