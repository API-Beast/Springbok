//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "TextureData.h"
#include "../../Dependencies/lodepng.h"
#include <Springbok/Utils/Debug.h>
#include <cassert>

TextureData TextureData::FromFile(const std::string& path)
{
	TextureData r;
  unsigned error;
	unsigned w, h;
  error = lodepng_decode32_file(&(r.Data.DataPtr), &w, &h, path.c_str());
	r.Data.Width         = w;
	r.Data.Height        = h;
	r.Data.Autonomous    = true;
	r.Data.ReservedBytes = r.Data.Width * r.Data.Height * sizeof(u_int32_t);
	r.Data.UsedBytes     = r.Data.ReservedBytes;
	
	if(error)
		Debug::Write("Can't decode $ as PNG: $", path, lodepng_error_text(error));
	return r;
}

bool TextureData::exportToPNG(const std::string& path)
{
	if(Data.isDense())
		lodepng_encode32_file(path.c_str(), Data.DataPtr, Data.Width, Data.Height);
	else
		assert(false); // TODO
}

std::vector< Vec4I > TextureData::findFrames(Vec4F border, bool findBaseline)
{
	std::vector<Vec4I> frames;
	u_int32_t borderClr = Color2Int(border);
	frames.reserve(24);
	
	for(int y = 0; y < Data.Height; ++y)
	for(int x = 0; x < Data.Width ; ++x)
	if(Data.at(x, y) != borderClr)
	{
		bool found = false;
		for(Vec4I& frame : frames)
		{
			bool isExtensionX = false;
			bool isExtensionY = false;
			auto extend = [&]()
			{ 
				frame.XY.lowerBound(Vec2I(x, y));
				frame.ZW.upperBound(Vec2I(x, y));
				found = true;
			};
			
			if(y >= frame.X && y <= frame.ZW.Y) // Is it inside on the Y-Axis?
			{
				     if(x+1 == frame.XY.X){ extend(); break; } // Extend if it is a extension on the X-Axis
				else if(x-1 == frame.ZW.X){ extend(); break; }
			}
			else if(x >= frame.X && x <= frame.ZW.X) // Same, on X-Axis
			{
				     if(y+1 == frame.XY.Y){ extend(); break; } // Extend on Y-Axis
				else if(y-1 == frame.ZW.Y){ extend(); break; }
			}
		}
		if(!found) frames.push_back(Vec4I(x, y, x, y));
	}
	
	if(findBaseline)
	{
		Vec4I* firstFrame    = nullptr;
		int    minY = +999999;
		int    maxY = -999999;
		for(Vec4I& frame : frames)
		{
			if(firstFrame == nullptr)
			{
				firstFrame = &frame;
				continue;
			}
			
			auto overlaps = [](Vec4I& frame, Vec4I& other, int i)
			{
				return (frame.XY[i] > other.XY[i] && frame.XY[i] < other.ZW[i])
				    || (frame.ZW[i] > other.XY[i] && frame.ZW[i] < other.ZW[i]);
			};
			
			if(overlaps(frame, *firstFrame, 1))
			{
				bool resized = false;
				
				if(frame.XY.Y < minY){ minY = frame.XY.Y; resized = true; }
				if(frame.ZW.Y > maxY){ maxY = frame.ZW.Y; resized = true; }
				
				bool isPossible = true;
				
				// Go through all frames in with this baseline and check if they would collide with any other frame if they were extended
				for(Vec4I* it = firstFrame; it++; it <= &frame)
				{
					Vec4I extended = *it;
					extended.XY.Y = minY;
					extended.ZW.Y = maxY;
					
					for(Vec4I& other : frames)
					if(it != &other)
					if(overlaps(extended, other, 0) && overlaps(extended, other, 1))
					{
						isPossible = false;
						break;
					}
				}
				
					
				if(isPossible)
				{
					// If this extents the baselines, apply the new lines to all previous ones
					if(resized)
					for(Vec4I* it = firstFrame; it++; it <= &frame)
					{
						(*it).XY.Y = minY;
						(*it).ZW.Y = maxY;
					}
					// Else only change this one
					else
					{
						frame.XY.Y = minY;
						frame.ZW.Y = maxY;
					}
				}
				else
				{
					// Can't extent the frames, this group of frames is finished.
					firstFrame = nullptr;
				}
			}
			else
			{
				// This frame doesn't overlap with any previous frames, thus this group of frames is finished.
				firstFrame = nullptr;
			}
		}
	}

	// For the return value convert the end positions to Width/Height
	for(Vec4I& frame : frames)
		frame.ZW -= frame.XY;
	
	return frames;
}
