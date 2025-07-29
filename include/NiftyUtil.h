#pragma once  

#include "lunasvg.h"  
#include <glad/glad.h> // Ensure OpenGL headers are included  
#include <imgui.h> // Ensure ImGui headers are included  
#include <memory>    // For std::unique_ptr  
#include "NiftyStikTemplates.h"
#include <NiftyCalc.h>

namespace Nifty
{

	struct FretboardSVG
	{
		std::string scallop_data;
		std::string svg_data;

		FretboardSVG(double scale_length, int fret_count, double fret_width, double fret_height, double scallop_depth, bool show_scallop)
		{

			svg_data = fretboard_template;
			size_t pos = svg_data.find("SCALLOP_DATA");
			if (pos != std::string::npos)
				svg_data.replace(pos, std::string("SCALLOP_DATA").length(), calc_scallop_data(scale_length, fret_count, fret_width, scallop_depth));

			pos = svg_data.find("FRET_DATA");
			if (pos != std::string::npos)
				svg_data.replace(pos, std::string("FRET_DATA").length(), calc_fret_data(scale_length, fret_count, fret_width, fret_height));

			pos = svg_data.find("SHOW_SCALLOP\n");
			if (pos != std::string::npos)
			{
				if (show_scallop)
					svg_data.replace(pos, std::string("SHOW_SCALLOP\n").length(), show_scallop_template);
				else
					svg_data.replace(pos, std::string("SHOW_SCALLOP\n").length(), "");
			}
			printf("%s", svg_data.c_str());
		}
	private:
		std::string calc_fret_data(double scale_length, int fret_count, double fret_width, double fret_height)
		{
			std::string fret_data;

			for (int i = 1; i <= fret_count + 1; i++)
			{
				double fret_length = FretCalculator(scale_length, i);
				if (i == 1)
					fret_length -= fret_width / 2;
				else
					fret_length -= FretCalculator(scale_length, i - 1) - fret_width;

				std::ostringstream edit_stream;
				std::string new_fret_data = fret_template;
				//printf("%s\n\n", new_fret_data.c_str());

				if (i == fret_count + 1)
					new_fret_data = fret_template_tail;

				edit_stream << std::fixed << std::setprecision(1) << fret_length * 1000;
				size_t pos = new_fret_data.find("FRET_LENGTH");
				if (pos != std::string::npos)
					new_fret_data.replace(pos, std::string("FRET_LENGTH").length(), edit_stream.str());
				edit_stream.str("");

				if (i != fret_count + 1)
				{
					edit_stream << std::fixed << std::setprecision(1) << (fret_width / 2) * 1000;
					pos = new_fret_data.find("FRET_WIDTH_HALF");
					if (pos != std::string::npos)
						new_fret_data.replace(pos, std::string("FRET_WIDTH_HALF").length(), edit_stream.str());
					edit_stream.str("");

					edit_stream << std::fixed << std::setprecision(1) << fret_height * 1000;
					pos = new_fret_data.find("FRET_HEIGHT");
					if (pos != std::string::npos)
						new_fret_data.replace(pos, std::string("FRET_HEIGHT").length(), edit_stream.str());
					edit_stream.str("");

					edit_stream << std::fixed << std::setprecision(1) << fret_width * 1000;
					pos = new_fret_data.find("FRET_WIDTH");
					if (pos != std::string::npos)
						new_fret_data.replace(pos, std::string("FRET_WIDTH").length(), edit_stream.str());
					edit_stream.str("");
				}

				//printf("%s\n", new_fret_data.c_str());
				fret_data.append(new_fret_data);
			}
			return fret_data;
		}

		std::string calc_scallop_data(double scale_length, int fret_count, double fret_width, double scallop_depth)
		{
			std::string scallop_data;

			for (int i = 1; i <= fret_count; i++)
			{
				double fret_length = FretCalculator(scale_length, i);
				if (i == 1)
					fret_length -= fret_width / 2;
				else
					fret_length -= FretCalculator(scale_length, i - 1) - fret_width;

				std::ostringstream edit_stream;
				std::string new_scallop_data;

				if (i < fret_count)
					new_scallop_data = scallop_template;
				else
					new_scallop_data = scallop_template_tail;
				printf("%s\n\n", new_scallop_data.c_str());

				edit_stream << std::fixed << std::setprecision(1) << (fret_length / 2) * 1000;
				size_t pos = new_scallop_data.find("FRET_LENGTH_HALF");
				if (pos != std::string::npos)
					new_scallop_data.replace(pos, std::string("FRET_LENGTH_HALF").length(), edit_stream.str());
				edit_stream.str("");

				edit_stream << std::fixed << std::setprecision(1) << scallop_depth * 1000;
				pos = new_scallop_data.find("SCALLOP_DEPTH");
				if (pos != std::string::npos)
					new_scallop_data.replace(pos, std::string("SCALLOP_DEPTH").length(), edit_stream.str());
				edit_stream.str("");

				edit_stream << std::fixed << std::setprecision(1) << fret_length * 1000;
				pos = new_scallop_data.find("FRET_LENGTH");
				if (pos != std::string::npos)
					new_scallop_data.replace(pos, std::string("FRET_LENGTH").length(), edit_stream.str());
				edit_stream.str("");

				edit_stream << std::fixed << std::setprecision(1) << fret_width * 1000;
				pos = new_scallop_data.find("FRET_WIDTH");
				if (pos != std::string::npos)
					new_scallop_data.replace(pos, std::string("FRET_WIDTH").length(), edit_stream.str());
				edit_stream.str("");

				printf("%s\n", new_scallop_data.c_str());
				scallop_data.append(new_scallop_data);
			}
			return scallop_data;
		}

		void calc_show_scallop(bool show_scallop)
		{

		}
	};

	class SvgHandler
	{
	public:
		std::unique_ptr<lunasvg::Document> document;
		lunasvg::Bitmap bitmap;
		GLuint texture_id = 0;
		int width, height = 500;

		~SvgHandler()
		{
			// Cleanup GLTexture
			if (texture_id)
			{
				glDeleteTextures(1, &texture_id);
				texture_id = 0;
			}
		}

		// Method to create SVG from template and dimensions  
		void createSvgFromTemplate(const std::string& svgTemplate)
		{
			// Basic example: Replace placeholders for width and height in the template  
			std::string modifiedSvg = svgTemplate;
			// Replace "WIDTH_PLACEHOLDER" and "HEIGHT_PLACEHOLDER" with actual values  
			// For more complex templating, consider a dedicated library or regex.  
			//size_t pos = modifiedSvg.find("WIDTH_PLACEHOLDER");
			//if (pos != std::string::npos)
			//{
			//	modifiedSvg.replace(pos, std::string("WIDTH_PLACEHOLDER").length(), std::to_string(width));
			//}
			//pos = modifiedSvg.find("HEIGHT_PLACEHOLDER");
			//if (pos != std::string::npos)
			//{
			//	modifiedSvg.replace(pos, std::string("HEIGHT_PLACEHOLDER").length(), std::to_string(height));
			//}

			document = lunasvg::Document::loadFromData(modifiedSvg);
			bitmap = document->renderToBitmap();
			bitmap.convertToRGBA();
			width = bitmap.width();
			height = bitmap.height();
			const unsigned char* pixels = bitmap.data(); // Assumes RGBA format, check LunaSVG docs

			glGenTextures(1, &texture_id);
			glBindTexture(GL_TEXTURE_2D, texture_id);

			// Set texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Upload the pixel data to the texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

			// Unbind the texture
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	};
}