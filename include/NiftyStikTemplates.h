#pragma once

namespace Nifty
{
	const std::string fretboard_template = R"SVG(  
       <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 2750 100"  
            width="2750" height="100">
			<g transform="scale(0.1)">
				<defs>
					<clipPath id = "clip-scallop">
						<path
							d="
								M 27500 1000
								H 0
								V 0
								H 500
								V 500
SCALLOP_DATA
								H 27500
								Z
							"
							fill="none"
							stroke="none"
							stroke-width="0"
						/>
					</clipPath>
				</defs>
				<path
					d="
						M 250 750
						v -303
						h 250
						v 53
FRET_DATA
						v 250
						Z
					"
					fill="white"
					stroke="none"
					stroke-width="0"
SHOW_SCALLOP
				/>
			</g>
       </svg>  
   )SVG";

	const std::string fret_template = "\t\t\t\t\t\th FRET_LENGTH\n\t\t\t\t\t\ta FRET_WIDTH_HALF FRET_HEIGHT 0 0 1 FRET_WIDTH 0\n";
	const std::string fret_template_tail = "\t\t\t\t\t\th FRET_LENGTH";
	const std::string scallop_template = "\t\t\t\t\t\t\t\ta FRET_LENGTH_HALF SCALLOP_DEPTH 0 0 0 FRET_LENGTH 0\n\t\t\t\t\t\t\t\tV 0\n\t\t\t\t\t\t\t\th FRET_WIDTH\n\t\t\t\t\t\t\t\tV 500\n";
	const std::string scallop_template_tail = "\t\t\t\t\t\t\t\ta FRET_LENGTH_HALF SCALLOP_DEPTH 0 0 0 FRET_LENGTH 0\n\t\t\t\t\t\t\t\tV 0";
	const std::string show_scallop_template = "\t\t\t\t\tclip-path=\"url(#clip-scallop)\"\n";
}
