##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=wxGameEditorUITest
ConfigurationName      :=Debug
WorkspacePath          := "E:\Github\wxGameEditorUI\Development\Src"
ProjectPath            := "E:\Github\wxGameEditorUI\Development\Src"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Administrator
Date                   :=2012-10-15
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="E:\Github\wxGameEditorUI\Development\Src\wxGameEditorUITest.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
LinkOptions            :=  -mwindows $(shell wx-config --debug=yes --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)wxmsw29ud_propgrid 
ArLibs                 :=  "libwxmsw29ud_propgrid" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
WXWIN:=C:\wxWidgets-2.9.4
PATH:=$(WXWIN)\lib\gcc_dll;$(PATH)
WXCFG:=gcc_dll\mswu
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
Objects=$(IntermediateDirectory)/wxGameEditorUITest_main$(ObjectSuffix) $(IntermediateDirectory)/wxGameEditorUITest_gui$(ObjectSuffix) $(IntermediateDirectory)/BaseControl_PropertywxConnector$(ObjectSuffix) $(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/wxGameEditorUITest_main$(ObjectSuffix): wxGameEditorUITest/main.cpp $(IntermediateDirectory)/wxGameEditorUITest_main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/wxGameEditorUI/Development/Src/wxGameEditorUITest/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxGameEditorUITest_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxGameEditorUITest_main$(DependSuffix): wxGameEditorUITest/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxGameEditorUITest_main$(ObjectSuffix) -MF$(IntermediateDirectory)/wxGameEditorUITest_main$(DependSuffix) -MM "E:/Github/wxGameEditorUI/Development/Src/wxGameEditorUITest/main.cpp"

$(IntermediateDirectory)/wxGameEditorUITest_main$(PreprocessSuffix): wxGameEditorUITest/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxGameEditorUITest_main$(PreprocessSuffix) "E:/Github/wxGameEditorUI/Development/Src/wxGameEditorUITest/main.cpp"

$(IntermediateDirectory)/wxGameEditorUITest_gui$(ObjectSuffix): wxGameEditorUITest/gui.cpp $(IntermediateDirectory)/wxGameEditorUITest_gui$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/wxGameEditorUI/Development/Src/wxGameEditorUITest/gui.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxGameEditorUITest_gui$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxGameEditorUITest_gui$(DependSuffix): wxGameEditorUITest/gui.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxGameEditorUITest_gui$(ObjectSuffix) -MF$(IntermediateDirectory)/wxGameEditorUITest_gui$(DependSuffix) -MM "E:/Github/wxGameEditorUI/Development/Src/wxGameEditorUITest/gui.cpp"

$(IntermediateDirectory)/wxGameEditorUITest_gui$(PreprocessSuffix): wxGameEditorUITest/gui.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxGameEditorUITest_gui$(PreprocessSuffix) "E:/Github/wxGameEditorUI/Development/Src/wxGameEditorUITest/gui.cpp"

$(IntermediateDirectory)/BaseControl_PropertywxConnector$(ObjectSuffix): BaseControl/PropertywxConnector.cpp $(IntermediateDirectory)/BaseControl_PropertywxConnector$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/wxGameEditorUI/Development/Src/BaseControl/PropertywxConnector.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BaseControl_PropertywxConnector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BaseControl_PropertywxConnector$(DependSuffix): BaseControl/PropertywxConnector.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BaseControl_PropertywxConnector$(ObjectSuffix) -MF$(IntermediateDirectory)/BaseControl_PropertywxConnector$(DependSuffix) -MM "E:/Github/wxGameEditorUI/Development/Src/BaseControl/PropertywxConnector.cpp"

$(IntermediateDirectory)/BaseControl_PropertywxConnector$(PreprocessSuffix): BaseControl/PropertywxConnector.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BaseControl_PropertywxConnector$(PreprocessSuffix) "E:/Github/wxGameEditorUI/Development/Src/BaseControl/PropertywxConnector.cpp"

$(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(ObjectSuffix): BaseControl/DlgPropertyEditors.cpp $(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/wxGameEditorUI/Development/Src/BaseControl/DlgPropertyEditors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(DependSuffix): BaseControl/DlgPropertyEditors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(ObjectSuffix) -MF$(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(DependSuffix) -MM "E:/Github/wxGameEditorUI/Development/Src/BaseControl/DlgPropertyEditors.cpp"

$(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(PreprocessSuffix): BaseControl/DlgPropertyEditors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(PreprocessSuffix) "E:/Github/wxGameEditorUI/Development/Src/BaseControl/DlgPropertyEditors.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/wxGameEditorUITest_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/wxGameEditorUITest_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/wxGameEditorUITest_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/wxGameEditorUITest_gui$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/wxGameEditorUITest_gui$(DependSuffix)
	$(RM) $(IntermediateDirectory)/wxGameEditorUITest_gui$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/BaseControl_PropertywxConnector$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/BaseControl_PropertywxConnector$(DependSuffix)
	$(RM) $(IntermediateDirectory)/BaseControl_PropertywxConnector$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(DependSuffix)
	$(RM) $(IntermediateDirectory)/BaseControl_DlgPropertyEditors$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) "E:\Github\wxGameEditorUI\Development\Src\.build-debug\wxGameEditorUITest"


