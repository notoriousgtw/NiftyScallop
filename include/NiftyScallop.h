#pragma once

#include <NiftySVG.h>
#include <NiftyStik.h>
#include <NiftyStikSVGTemplates.h>

using namespace Nifty::Stik;

namespace Nifty::SVG
{
class Fretboard
{
public:
	Fretboard();
	void Update(double scale_length, int fret_count, double fret_width, double fret_height, double scallop_depth, bool show_scallop);
	int GetTextureID() { return svg_handler.texture_id; };
	int GetWidth() { return svg_handler.width; };
	int GetHeight() { return svg_handler.height; };

private:
	double scale_length = 25.5;
	int fret_count = 24;
	double fret_width = 0.115;
	double fret_height = 0.053;
	double scallop_depth = 0.0625;
	bool show_scallop = false;
	std::string svg_data;
	Handler svg_handler;

	std::string CalcFretData();
	std::string CalcClipData();
	std::string CalcScallopClipHead();
	std::string CalcScallopClipBody();
	std::string CalcScallopClipTail();
	std::string CalcShowClips();
};
}