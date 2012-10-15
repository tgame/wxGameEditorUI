.PHONY: clean All

All:
	@echo ----------Building project:[ wxGameEditorUITest - Debug ]----------
	@"$(MAKE)" -f "wxGameEditorUITest.mk"
clean:
	@echo ----------Cleaning project:[ wxGameEditorUITest - Debug ]----------
	@"$(MAKE)" -f "wxGameEditorUITest.mk" clean
