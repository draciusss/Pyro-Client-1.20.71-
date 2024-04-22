#pragma once
#include "../ClickGUIRenderer.hpp"
#include "ClickGUIElements.hpp"

#define colors_text MusuiGUI::HexToColorF(ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("colors_text")->value)
#define o_colors_text ModuleManager::getModule("ClickGUI")->settings.getSettingByName<float>("o_colors_text")->value
#define colors_text_rgb ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("colors_text_rgb")->value

#define colors_primary1 MusuiGUI::HexToColorF(ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("colors_primary1")->value)
#define o_colors_primary1 ModuleManager::getModule("ClickGUI")->settings.getSettingByName<float>("o_colors_primary1")->value
#define colors_primary1_rgb ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("colors_primary1_rgb")->value

#define colors_secondary4 MusuiGUI::HexToColorF(ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("colors_secondary4")->value)
#define o_colors_secondary4 ModuleManager::getModule("ClickGUI")->settings.getSettingByName<float>("o_colors_secondary4")->value
#define colors_secondary4_rgb ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("colors_secondary4_rgb")->value

#define colors_enabled MusuiGUI::HexToColorF(ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("colors_enabled")->value)
#define o_colors_enabled ModuleManager::getModule("ClickGUI")->settings.getSettingByName<float>("o_colors_enabled")->value
#define colors_enabled_rgb ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("colors_enabled_rgb")->value

#define colors_disabled MusuiGUI::HexToColorF(ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("colors_disabled")->value)
#define o_colors_disabled ModuleManager::getModule("ClickGUI")->settings.getSettingByName<float>("o_colors_disabled")->value
#define colors_disabled_rgb ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("colors_disabled_rgb")->value

#define colors_mod1 MusuiGUI::HexToColorF(ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("colors_mod1")->value)
#define o_colors_mod1 ModuleManager::getModule("ClickGUI")->settings.getSettingByName<float>("o_colors_mod1")->value
#define colors_mod1_rgb ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("colors_mod1_rgb")->value

#define colors_mod2 MusuiGUI::HexToColorF(ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("colors_mod2")->value)
#define o_colors_mod2 ModuleManager::getModule("ClickGUI")->settings.getSettingByName<float>("o_colors_mod2")->value
#define colors_mod2_rgb ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("colors_mod2_rgb")->value

#define colors_mod3 MusuiGUI::HexToColorF(ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("colors_mod3")->value)
#define o_colors_mod3 ModuleManager::getModule("ClickGUI")->settings.getSettingByName<float>("o_colors_mod3")->value
#define colors_mod3_rgb ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("colors_mod3_rgb")->value

#define colors_mod4 MusuiGUI::HexToColorF(ModuleManager::getModule("ClickGUI")->settings.getSettingByName<std::string>("colors_mod4")->value)
#define o_colors_mod4 ModuleManager::getModule("ClickGUI")->settings.getSettingByName<float>("o_colors_mod4")->value
#define colors_mod4_rgb ModuleManager::getModule("ClickGUI")->settings.getSettingByName<bool>("colors_mod4_rgb")->value

std::map<std::string, ID2D1Bitmap*> ClickGUIElements::images;
std::vector<D2D1_MATRIX_3X2_F> ClickGUIElements::matrixes;
std::vector<Vec2<float>> sizes;
std::vector<Vec2<float>> shadowSizes;
std::vector<float> searchBarSizes;
std::vector<float> searchCutOutHeights;

std::string ClickGUIElements::SearchBar(int index, std::string& text, int limit, float x, float y) {

	if (ClickGUIRenderer::page.type == "normal" && ClickGUIRenderer::curr == "modules") {

		D2D1_COLOR_F col;

		Vec2<float> round = Constraints::RoundingConstraint(19, 19);

		if (index > searchBarSizes.size() - 1 || index == 0) {
			float nigga = Constraints::RelativeConstraint(0.42, "height");

			searchBarSizes.emplace_back(nigga);
		}

		if (index > searchCutOutHeights.size() - 1 || index == 0) {
			float nigga = Constraints::RelativeConstraint(0.38, "height");

			searchCutOutHeights.emplace_back(nigga);
		}

		if (MusuiGUI::TextBoxes[index].isActive) {
			if (MusuiGUI::TextBoxes[index].isAt1) MusuiGUI::lerp(MusuiGUI::TextBoxes[index].cursorOpac, -1.0f, 0.05f * MusuiGUI::frameFactor);
			else MusuiGUI::lerp(MusuiGUI::TextBoxes[index].cursorOpac, 2.0f, 0.05f * MusuiGUI::frameFactor);
		}
		else MusuiGUI::TextBoxes[index].cursorOpac = 0;

		if (MusuiGUI::TextBoxes[index].cursorOpac > 1) MusuiGUI::TextBoxes[index].isAt1 = true;
		if (MusuiGUI::TextBoxes[index].cursorOpac < 0) MusuiGUI::TextBoxes[index].isAt1 = false;

		if (index <= searchBarSizes.size()) {

			const float textWidth = searchBarSizes[index];
			const float percHeight = Constraints::RelativeConstraint(0.42, "height");

			text = MusuiGUI::TextBox(index, text, limit, x - textWidth, y, textWidth, percHeight);

			if (!text.empty()) MusuiGUI::TextBoxes[index].isActive = true;

            MusuiGUI::lerp(searchBarSizes[index], Constraints::RelativeConstraint(2.7f, "height"),0.12f * MusuiGUI::frameFactor);
            MusuiGUI::lerp(searchCutOutHeights[index], Constraints::RelativeConstraint(0.395, "height"),0.12f * MusuiGUI::frameFactor);

			col = colors_primary1_rgb ? MusuiGUI::rgbColor : colors_primary1;
			col.a = o_colors_primary1;

			D2D1_COLOR_F searchbg = colors_secondary4_rgb ? MusuiGUI::rgbColor : colors_secondary4;
			searchbg.a = o_colors_secondary4;

			MusuiGUI::RoundedRect(x - textWidth, y, searchbg, textWidth, percHeight, round.x,
				round.x);

			D2D::context->PushAxisAlignedClip(D2D1::RectF(x - textWidth, y + percHeight, (x - textWidth) + textWidth,
				y + searchCutOutHeights[index]), D2D1_ANTIALIAS_MODE_ALIASED);
			MusuiGUI::RoundedRect(x - textWidth, y, col, textWidth, percHeight, round.x,
				round.x);
			D2D::context->PopAxisAlignedClip();

			IDWriteTextFormat* textFormat;
			MusuiGUI::writeFactory->CreateTextFormat(
				MusuiGUI::to_wide(Client::settings.getSettingByName<std::string>("fontname")->value).c_str(),
				NULL,
				DWRITE_FONT_WEIGHT_REGULAR,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				Constraints::FontScaler(Constraints::SpacingConstraint(0.60f, textWidth)),
				L"",
				&textFormat
			);
			textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

			IDWriteTextLayout* textLayout;

			MusuiGUI::writeFactory->CreateTextLayout(
				MusuiGUI::to_wide(text).c_str(),
				wcslen(MusuiGUI::to_wide(text).c_str()),
				textFormat,
				textWidth,
				percHeight,
				&textLayout
			);

			DWRITE_TEXT_METRICS textMetrics;
			textLayout->GetMetrics(&textMetrics);
			textLayout->Release();

			D2D1_COLOR_F cursorCol = D2D1::ColorF(D2D1::ColorF::White);

			cursorCol.a = MusuiGUI::TextBoxes[index].cursorOpac;

			MusuiGUI::lerp(MusuiGUI::TextBoxes[index].cursorX, (x - textWidth) + Constraints::RelativeConstraint(0.38, "height") + textMetrics.widthIncludingTrailingWhitespace, 0.420f * MusuiGUI::frameFactor);

			MusuiGUI::RoundedRect(MusuiGUI::TextBoxes[index].cursorX, y + Constraints::RelativeConstraint(0.2f) / 2.0f, cursorCol, Constraints::RelativeConstraint(0.025f), percHeight / 1.9f, 0, 0);

			if (searchBarSizes[index] > Constraints::RelativeConstraint(0.45, "height")) {
				MusuiGUI::MusuiTextWithFont((x - textWidth) + Constraints::RelativeConstraint(0.38, "height"), y,
					MusuiGUI::to_wide(text).c_str(),
					textWidth, percHeight,
					DWRITE_TEXT_ALIGNMENT_LEADING,
					Constraints::SpacingConstraint(0.60f, textWidth),
					DWRITE_FONT_WEIGHT_NORMAL);

			}

			MusuiGUI::Image("\\Musui\\assets\\search.png",
				D2D1::RectF((x - textWidth) + Constraints::RelativeConstraint(0.245, "height") / 2.0f,
					y + Constraints::RelativeConstraint(0.245, "height") / 2.0f,
					((x - textWidth) + Constraints::RelativeConstraint(0.18, "height") / 2.0f) +
					Constraints::RelativeConstraint(0.22, "height"),
					(y + Constraints::RelativeConstraint(0.18, "height") / 2.0f) +
					Constraints::RelativeConstraint(0.22, "height")));
			return "";
		}
	}

	return "";
}


void ClickGUIElements::ModCard(float x, float y, Module* mod, const std::string iconpath, const int index, bool visible)
{
	Vec2<float> round = Constraints::RoundingConstraint(34, 34);


	if (index > sizes.size() - 1 || index == 0) {
		float nigga = Constraints::RelativeConstraint(0.19f, "height", true);
		float gaynigga = Constraints::RelativeConstraint(0.141f, "height", true);

		sizes.emplace_back(nigga, gaynigga);
	}

	if (index > shadowSizes.size() - 1 || index == 0) {
		shadowSizes.emplace_back(0.01, 0.01);
	}

	if (!visible)
		return;

	// Bottom rounded rect
	float BottomRoundedWidth = sizes[index].x;
	float BottomRoundedHeight = sizes[index].y;

	float realY = y;
	float diffX = 0;
	float diffY = 0;

	if (MusuiGUI::isInScrollView) realY += MusuiGUI::scrollpos;

	if (MusuiGUI::CursorInRect(x, realY, BottomRoundedWidth, BottomRoundedHeight)) {

		MusuiGUI::lerp(sizes[index].x, Constraints::RelativeConstraint(0.198f, "height", true),
			0.15f * MusuiGUI::frameFactor);
		MusuiGUI::lerp(sizes[index].y, Constraints::RelativeConstraint(0.149f, "height", true),
			0.15f * MusuiGUI::frameFactor);

		diffX = (sizes[index].x - Constraints::RelativeConstraint(0.19f, "height", true)) / 2.0f;
		diffY = (sizes[index].y - Constraints::RelativeConstraint(0.141f, "height", true)) / 2.0f;

		MusuiGUI::lerp(shadowSizes[index].x, BottomRoundedWidth, 0.25f * MusuiGUI::frameFactor);
		MusuiGUI::lerp(shadowSizes[index].y, BottomRoundedHeight, 0.25f * MusuiGUI::frameFactor);

	}
	else {

		MusuiGUI::lerp(sizes[index].x, Constraints::RelativeConstraint(0.19f, "height", true),
			0.15f * MusuiGUI::frameFactor);
		MusuiGUI::lerp(sizes[index].y, Constraints::RelativeConstraint(0.141f, "height", true),
			0.15f * MusuiGUI::frameFactor);

		MusuiGUI::lerp(shadowSizes[index].x, 0.01f, 0.01f * MusuiGUI::frameFactor);
		MusuiGUI::lerp(shadowSizes[index].y, 0.01f, 0.01f * MusuiGUI::frameFactor);

		diffX = (sizes[index].x - Constraints::RelativeConstraint(0.19f, "height", true)) / 2.0f;
		diffY = (sizes[index].y - Constraints::RelativeConstraint(0.141f, "height", true)) / 2.0f;

	}



	if (shadowSizes[index].x > Constraints::RelativeConstraint(0.255f, "height")) {


		float diffX2 = (shadowSizes[index].x - BottomRoundedWidth) / 2.0f;
		float diffY2 = (shadowSizes[index].y - BottomRoundedHeight) / 2.0f;

		MusuiGUI::ShadowRect(
			D2D1::RoundedRect(D2D1::RectF(x - diffX2, realY - diffY2, (x - diffX2) + shadowSizes[index].x, (realY - diffY2) + shadowSizes[index].y),
				round.x, round.x));
	}

	x -= diffX;
	y -= diffY;

	D2D1_COLOR_F mod1Col = colors_mod1_rgb ? MusuiGUI::rgbColor : colors_mod1;
	mod1Col.a = o_colors_mod1;

	D2D1_COLOR_F mod2Col = colors_mod2_rgb ? MusuiGUI::rgbColor : colors_mod2;
	mod2Col.a = o_colors_mod2;

	MusuiGUI::RoundedRect(x, y, mod2Col, BottomRoundedWidth, BottomRoundedHeight, round.x, round.x);

	// Top rounded rect

	float TopRoundedHeight = Constraints::SpacingConstraint(sizes[index].y, 0.635f);
	MusuiGUI::RoundedRectOnlyTopCorner(x, y, mod1Col,
		BottomRoundedWidth, TopRoundedHeight, round.x, round.x);

	MusuiGUI::PushSize(x, y, BottomRoundedWidth, BottomRoundedHeight);
	// Mod Name
	float textx = Constraints::PercentageConstraint(0.1405, "left");
	float texty = Constraints::PercentageConstraint(0.415, "top");
	float textWidth = Constraints::RelativeConstraint(1.0);
	float textHeight = Constraints::RelativeConstraint(0.2);

	MusuiGUI::MusuiTextWithFont(textx, texty, MusuiGUI::to_wide(mod->name).c_str(), textWidth, textHeight,
		DWRITE_TEXT_ALIGNMENT_CENTER,
		Constraints::SpacingConstraint(0.8, textWidth),
		DWRITE_FONT_WEIGHT_NORMAL);

	// Mod icon

	D2D1_COLOR_F mod3Col = colors_mod3_rgb ? MusuiGUI::rgbColor : colors_mod3;
	mod3Col.a = o_colors_mod3;

	float modiconx = Constraints::PercentageConstraint(0.40, "left");
	float modicony = Constraints::PercentageConstraint(0.11, "top");

	float paddingSize = Constraints::RelativeConstraint(0.28);

	MusuiGUI::Tooltip("mod_" + std::to_string(index), x, realY, mod->description, BottomRoundedWidth, TopRoundedHeight);

	MusuiGUI::RoundedRect(modiconx, modicony, mod3Col,
		paddingSize, paddingSize, 7.5, 7.5);

	paddingSize = Constraints::RelativeConstraint(0.20);
	modiconx = Constraints::PercentageConstraint(0.43, "left");
	modicony = Constraints::PercentageConstraint(0.15, "top");

	// enabled / disabled button

	std::string text;
	text = mod->settings.getSettingByName<bool>("enabled")->value ? "Enabled" : "Disabled";
	D2D1_COLOR_F enabledColor = colors_enabled_rgb ? MusuiGUI::rgbColor : colors_enabled;
	D2D1_COLOR_F disabledColor = colors_disabled_rgb ? MusuiGUI::rgbColor : colors_disabled;

	enabledColor.a = o_colors_enabled;
	disabledColor.a = o_colors_disabled;

	D2D1_COLOR_F to = text == "Enabled" ? enabledColor : disabledColor;
	if (MusuiGUI::buttonColors.size() >= index)  MusuiGUI::buttonColors[index] = MusuiGUI::LerpColor(MusuiGUI::buttonColors[index], to, 0.15f * MusuiGUI::frameFactor);
	else MusuiGUI::buttonColors.resize(index);

	float buttonWidth = Constraints::RelativeConstraint(0.71, "width");
	float buttonHeight = Constraints::RelativeConstraint(0.27);

	float buttonx = Constraints::PercentageConstraint(0.04, "right");
	float buttony = Constraints::PercentageConstraint(0.05, "bottom");

	round = Constraints::RoundingConstraint(26, 26);

	D2D1_COLOR_F textCol = colors_text_rgb ? MusuiGUI::rgbColor : colors_text;
	textCol.a = o_colors_text;

	if (MusuiGUI::RoundedButton(index, buttonx - buttonWidth, buttony - buttonHeight,
		MusuiGUI::buttonColors[index], textCol,
		MusuiGUI::to_wide(text).c_str(), buttonWidth, buttonHeight, round.x,
		round.x))
		mod->settings.getSettingByName<bool>("enabled")->value = !mod->settings.getSettingByName<bool>("enabled")->value;

	// Settings Button
	float settingswidth = Constraints::RelativeConstraint(0.17);
	float iconwidth = Constraints::RelativeConstraint(0.10);
	float settingsheightspac = Constraints::SpacingConstraint(0.31, settingswidth);

	float paddingwidth = Constraints::RelativeConstraint(0.26);
	float paddingspacing = Constraints::SpacingConstraint(4.84, paddingwidth);
	float paddingheightspac = Constraints::SpacingConstraint(0.05, paddingwidth);

	round = Constraints::RoundingConstraint(20, 20);

	float settingx = Constraints::PercentageConstraint(0.025, "left");
	float settingx2 = Constraints::PercentageConstraint(0.059, "left");

	MusuiGUI::RoundedRect(settingx, (buttony - paddingwidth) - paddingheightspac,
		mod3Col, paddingwidth,
		paddingwidth, round.x, round.x);

	D2D1_COLOR_F mod4Col = colors_mod4_rgb ? MusuiGUI::rgbColor : colors_mod4;
	mod4Col.a = o_colors_mod4;

    MusuiGUI::RoundedRectWithImageAndText(index, settingx2, (buttony - settingswidth) - settingsheightspac,
                                          settingswidth, settingswidth,
                                          mod4Col,
                                          "\\Musui\\assets\\gear.png", iconwidth, iconwidth, L"");

	if (!iconpath.empty() && images[mod->name] == nullptr) {

		std::string among = Utils::getRoamingPath() + "\\" + iconpath;
		MusuiGUI::LoadImageFromFile(MusuiGUI::to_wide(among).c_str(), &images[mod->name]);

	}
	else if (images[mod->name] != nullptr) {

		if (MusuiGUI::isInScrollView) {
			modicony += MusuiGUI::scrollpos;
		}

        D2D::context->DrawBitmap(images[mod->name], D2D1::RectF(modiconx, modicony, modiconx + paddingSize,
                                                                modicony + paddingSize));
	}

	if (MusuiGUI::isInScrollView)
		buttony += MusuiGUI::scrollpos;

	if (MusuiGUI::CursorInRect(buttonx - paddingspacing, (buttony - paddingwidth) - paddingheightspac,
		paddingwidth, paddingwidth) && MC::mousebutton == MouseButton::Left &&
		!MC::held) {
		MusuiGUI::TextBoxes[0].isActive = false;
		MC::mousebutton = MouseButton::None;
		ClickGUIRenderer::page.type = "settings";
		ClickGUIRenderer::page.module = mod->name;
		MusuiGUI::TextBoxes[0].isActive = false;
		MusuiGUI::scrollpos = 0;
		MusuiGUI::barscrollpos = 0;
		GUIMouseListener::accumilatedPos = 0;
		GUIMouseListener::accumilatedBarPos = 0;
	}
	MusuiGUI::PopSize();
}

void ClickGUIElements::convertImageToBitmap(ID2D1Image* pImg, D2D1_SIZE_U size)
{
	ID2D1Image* oldTarget = NULL;
	ID2D1Bitmap1* targetBitmap = NULL;

	//Create a Bitmap with "D2D1_BITMAP_OPTIONS_TARGET"
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
	D2D::context->CreateBitmap(size, 0, 0, bitmapProperties, &targetBitmap);



	//Save current Target, replace by ID2D1Bitmap
	D2D::context->GetTarget(&oldTarget);
	D2D::context->SetTarget(targetBitmap);
	//Draw Image on Target (if currently not drawing also call Begin/EndDraw)
	D2D::context->DrawImage(pImg);

	//Set previous Target
	D2D::context->SetTarget(oldTarget);
}
