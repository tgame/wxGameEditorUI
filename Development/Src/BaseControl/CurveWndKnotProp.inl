T_PropDefine(CurveProps_Impl_InterpMode,CurveProps_Impl,GetInterpMode,SetInterpMode);
T_Set_Prop(CurveProps_Impl_InterpMode,"插值模式","选中点","ComboBox");
T_Set_Prop_Custom(CurveProps_Impl_InterpMode,Config_CurveProps_Impl_InterpMode);

T_PropDefine_Convert(CurveProps_Impl_Value,CurveProps_Impl,GetValue,SetValue,ConvHelper::Float2String,ConvHelper::String2Float)
T_Set_Prop(CurveProps_Impl_Value,"值(0~1)","选中点","Editbox");


T_PropDefine_Convert(CurveProps_Impl_Time,CurveProps_Impl,GetTime,SetTime,ConvHelper::Float2String,ConvHelper::String2Float)
T_Set_Prop(CurveProps_Impl_Time,"时间(0~1)","选中点","Editbox");

T_PropDefine_Convert(CurveProps_Impl_Arrive,CurveProps_Impl,GetArriveTangent,SetArriveTangent,ConvHelper::Float2String,ConvHelper::String2Float)
T_Set_Prop(CurveProps_Impl_Arrive,"进入切向(0~1)","选中点","Editbox");

T_PropDefine_Convert(CurveProps_Impl_Leave,CurveProps_Impl,GetLeaveTangent,SetLeaveTangent,ConvHelper::Float2String,ConvHelper::String2Float)
T_Set_Prop(CurveProps_Impl_Leave,"离开切向(0~1)","选中点","Editbox");
