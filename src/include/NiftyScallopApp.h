#pragma once

#include <NiftyApp.h>
#include <NiftyScallop.h>
#include <NiftyCalc.h>
#include <NiftyNum.h>

namespace Nifty
{
class NiftyScallop : public App
{
public:
	NiftyScallop();
	~NiftyScallop();

private:
	virtual void Update() override;
	SVG::Fretboard fretboard_svg;
	ScallopOffsetTable router_offsets;
};
}