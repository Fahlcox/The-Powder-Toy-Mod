#pragma once
#include "gui/interface/Window.h"

namespace ui
{
	class Textbox;
}

class AutoBuilderPrompt : public ui::Window
{
	ui::Textbox * textField;

public:
	AutoBuilderPrompt();
	virtual ~AutoBuilderPrompt() = default;

	void OnDraw() override;
};
