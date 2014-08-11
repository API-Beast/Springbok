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
	r.Data.ReservedBytes = r.Data.Width * r.Data.Height * 4;
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

std::vector< Vec4I > TextureData::findFrames(Vec4F border)
{

}
