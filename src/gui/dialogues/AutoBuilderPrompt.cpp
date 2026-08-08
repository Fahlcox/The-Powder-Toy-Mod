#include "AutoBuilderPrompt.h"

#include "gui/interface/Label.h"
#include "gui/interface/Button.h"
#include "gui/interface/Engine.h"
#include "gui/interface/Textbox.h"

#include "gui/Style.h"
#include "graphics/Graphics.h"
#include "lua/CommandInterface.h"

AutoBuilderPrompt::AutoBuilderPrompt():
	ui::Window(ui::Point(-1, -1), ui::Point(440, 250))
{
	ui::Label * titleLabel = new ui::Label(ui::Point(8, 6), ui::Point(Size.X-16, 18), "Auto Builder & Lua Code Mod Loader");
	titleLabel->SetTextColour(style::Colour::WarningTitle);
	titleLabel->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
	titleLabel->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
	AddComponent(titleLabel);

	ui::Label * messageLabel = new ui::Label(ui::Point(8, 26), ui::Point(Size.X-16, 16), "Input Lua code (Full power TPT API: tpt.create, sim.*, etc.):");
	messageLabel->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
	messageLabel->Appearance.VerticalAlign = ui::Appearance::AlignTop;
	AddComponent(messageLabel);

	textField = new ui::Textbox(ui::Point(8, 44), ui::Point(Size.X-16, 120), 
		"-- Auto Builder Lua Script\n"
		"for x = 200, 420, 4 do\n"
		"  tpt.create(x, 150, \"STNE\")\n"
		"  tpt.create(x, 260, \"METL\")\n"
		"end\n"
		"tpt.create(310, 200, \"PLUT\")\n"
		"tpt.log(\"Auto Builder structure built!\")", 
		"Enter Lua code here...");
	textField->SetMultiline(true);
	textField->Appearance.VerticalAlign = ui::Appearance::AlignTop;
	textField->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
	AddComponent(textField);
	FocusComponent(textField);

	// Presets
	ui::Button * presetReactor = new ui::Button(ui::Point(8, 170), ui::Point(98, 16), "Preset: Reactor");
	presetReactor->SetActionCallback({ [this] {
		textField->SetText(
			"-- Reactor Core Preset\n"
			"for y = 140, 260 do\n"
			"  for x = 280, 420 do\n"
			"    tpt.create(x, y, \"METL\")\n"
			"  end\n"
			"end\n"
			"for y = 150, 250 do\n"
			"  for x = 290, 410 do\n"
			"    tpt.create(x, y, \"NEUT\")\n"
			"  end\n"
			"end\n"
			"tpt.create(350, 200, \"PLUT\")\n"
			"tpt.log(\n"
			"  \"Reactor built!\"\n"
			")"
		);
	} });
	AddComponent(presetReactor);

	ui::Button * presetPyramid = new ui::Button(ui::Point(110, 170), ui::Point(98, 16), "Preset: Pyramid");
	presetPyramid->SetActionCallback({ [this] {
		textField->SetText(
			"-- Pyramid Preset\n"
			"for h = 0, 80 do\n"
			"  local y = 300 - h\n"
			"  for x = 300 - h, 300 + h do\n"
			"    tpt.create(x, y, \"SAND\")\n"
			"  end\n"
			"end\n"
			"tpt.log(\"Pyramid built!\")"
		);
	} });
	AddComponent(presetPyramid);

	ui::Button * presetClear = new ui::Button(ui::Point(212, 170), ui::Point(98, 16), "Preset: Clear");
	presetClear->SetActionCallback({ [this] {
		textField->SetText("sim.reset()\ntpt.log(\"Simulation reset.\")");
	} });
	AddComponent(presetClear);

	ui::Button * cancelButton = new ui::Button(ui::Point(0, Size.Y-18), ui::Point(Size.X/2, 18), "Cancel");
	cancelButton->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
	cancelButton->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
	cancelButton->SetActionCallback({ [this] {
		CloseActiveWindow();
		SelfDestruct();
	} });
	AddComponent(cancelButton);
	SetCancelButton(cancelButton);

	ui::Button * runButton = new ui::Button(ui::Point(Size.X/2, Size.Y-18), ui::Point(Size.X/2, 18), "Build / Run Lua");
	runButton->Appearance.HorizontalAlign = ui::Appearance::AlignRight;
	runButton->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
	runButton->Appearance.TextInactive = style::Colour::WarningTitle;
	runButton->SetActionCallback({ [this] {
		String code = textField->GetText();
		CloseActiveWindow();
		CommandInterface::Ref().Command(code);
		SelfDestruct();
	} });
	AddComponent(runButton);
	SetOkayButton(runButton);

	MakeActiveWindow();
}

void AutoBuilderPrompt::OnDraw()
{
	Graphics * g = GetGraphics();
	g->DrawFilledRect(RectSized(Position - Vec2{ 1, 1 }, Size + Vec2{ 2, 2 }), 0x000000_rgb);
	g->DrawRect(RectSized(Position, Size), 0xC8C8C8_rgb);
}
