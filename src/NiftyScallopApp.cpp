#include "NiftyScallopApp.h"

namespace Nifty
{
NiftyScallop::NiftyScallop() : App("Nifty Scallop")
{
}

NiftyScallop::~NiftyScallop()
{
}

void NiftyScallop::Update()
{
	ImGui::Text("Scaloop");

	static bool init = true;
	static double scale_length = 25.5;
	static int fret_count = 24;
	static double fret_width = 0.115;
	static double fret_height = 0.053;
	static double scallop_depth = 0.0625;
	static double router_base_width = 6.75;
	static bool display_fractions = true;
	static bool show_scallop = false;

	if (init)
	{
		fretboard_svg.Update(scale_length, fret_count, fret_width, fret_height, scallop_depth, show_scallop);
		init = false;
	}

	// Scale Length Input
	ImGui::SetNextItemWidth(100);
	ImGui::InputDouble("Scale Length", &scale_length, 0.001, 0.01, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit() || (ImGui::IsItemDeactivated() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
		fretboard_svg.Update(scale_length, fret_count, fret_width, fret_height, scallop_depth, show_scallop);

	// Number of Frets Input
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("Number of Frets", &fret_count);
	if (ImGui::IsItemDeactivatedAfterEdit() || (ImGui::IsItemDeactivated() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
		fretboard_svg.Update(scale_length, fret_count, fret_width, fret_height, scallop_depth, show_scallop);

	// Fret Width Input
	ImGui::SetNextItemWidth(100);
	ImGui::InputDouble("Fret Width", &fret_width, 0.001, 0.01, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit() || (ImGui::IsItemDeactivated() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
		fretboard_svg.Update(scale_length, fret_count, fret_width, fret_height, scallop_depth, show_scallop);

	// Fret Height Input
	ImGui::SetNextItemWidth(100);
	ImGui::InputDouble("Fret Height", &fret_height, 0.001, 0.01, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit() || (ImGui::IsItemDeactivated() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
		fretboard_svg.Update(scale_length, fret_count, fret_width, fret_height, scallop_depth, show_scallop);

	// Scallop Depth Input
	ImGui::SetNextItemWidth(100);
	ImGui::InputDouble("Scallop Depth", &scallop_depth, 0.0001, 0.001, "%.4f");
	if (ImGui::IsItemDeactivatedAfterEdit() || (ImGui::IsItemDeactivated() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
		fretboard_svg.Update(scale_length, fret_count, fret_width, fret_height, scallop_depth, show_scallop);

	// Router Base Width Input
	ImGui::SetNextItemWidth(100);
	ImGui::InputDouble("Router Base Width", &router_base_width, 0.001, 0.01, "%.3f");

	ImGui::Checkbox("Show Fractions", &display_fractions);

	static int selected_precision_idx = 5; // Here we store our selection data as an index.
	if (display_fractions)
	{
	// Precision Input
		ImGui::SetNextItemWidth(100);
		const char * items[] = {
			"1/2",
			"1/4",
			"1/8",
			"1/16",
			"1/32",
			"1/64",
			"1/128"
		};


		// Pass in the preview value visible before opening the combo (it could technically be different contents or not pulled from items[])
		const char * combo_preview_value = items[selected_precision_idx];
		if (ImGui::BeginCombo("Precision", combo_preview_value))
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				const bool is_selected = (selected_precision_idx == n);
				if (ImGui::Selectable(items[n], is_selected))
					selected_precision_idx = n;

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
	}

	router_offsets = Nifty::ScallopCalculator(scale_length, fret_count, fret_width, router_base_width);

	if (ImGui::BeginTable("Scallop Offsets", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
	{
		ImGui::TableSetupColumn("Fret Number");
		ImGui::TableSetupColumn("1/4 Offset");
		ImGui::TableSetupColumn("1/2 Offset");
		ImGui::TableSetupColumn("3/4 Offset");
		ImGui::TableHeadersRow();
		for (int row = 1; row < fret_count + 1; row++)
		{
			ImGui::TableNextRow();
			for (int col = 0; col < 4; col++)
			{
				ImGui::TableSetColumnIndex(col);

				double offset_quarter = router_offsets[row][Nifty::ScallopOffsetType::Quarter];
				double offset_half = router_offsets[row][Nifty::ScallopOffsetType::Half];
				double offset_three_quarter = router_offsets[row][Nifty::ScallopOffsetType::ThreeQuarter];

				std::ostringstream offset_quarter_str;
				std::ostringstream offset_half_str;
				std::ostringstream offset_three_quarter_str;

				offset_quarter_str << std::setprecision(4) << std::showpoint << offset_quarter;
				offset_half_str << std::setprecision(4) << std::showpoint << offset_half;
				offset_three_quarter_str << std::setprecision(4) << std::showpoint << offset_three_quarter;

				if (display_fractions)
				{
					offset_quarter_str << " : " << Num::MixedNumber(static_cast<double>(offset_quarter), static_cast<Num::Precision>(selected_precision_idx + 1));
					offset_half_str << " : " << Num::MixedNumber(static_cast<double>(offset_half), static_cast<Num::Precision>(selected_precision_idx + 1));
					offset_three_quarter_str << " : " << Num::MixedNumber(static_cast<double>(offset_three_quarter), static_cast<Num::Precision>(selected_precision_idx + 1));
				}

				switch (col)
				{
				case 0:
					ImGui::Text("%d", row);
					break;
				case 1:
					ImGui::Text("%s", offset_quarter_str.str().c_str());
					break;
				case 2:
					ImGui::Text("%s", offset_half_str.str().c_str());
					break;
				case 3:
					ImGui::Text("%s", offset_three_quarter_str.str().c_str());
					break;
				}
			}
		}
		ImGui::EndTable();
	}
	//Nifty::FretImage fret;
	//fret.Display({ 512, 512 });
	//Nifty::FretSVG();

	if (ImGui::Checkbox("Show Scallop", &show_scallop))
		fretboard_svg.Update(scale_length, fret_count, fret_width, fret_height, scallop_depth, show_scallop);

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
	ImGui::BeginChild("Fretboard", ImVec2(ImGui::GetContentRegionAvail().x, fretboard_svg.GetHeight()), ImGuiChildFlags_None, window_flags);
	ImGui::Image((void*)(intptr_t)fretboard_svg.GetTextureID(), ImVec2((float)fretboard_svg.GetWidth(), (float)fretboard_svg.GetHeight()));
	ImGui::EndChild();
}
}
