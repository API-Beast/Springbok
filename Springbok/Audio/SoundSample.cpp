// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "SoundSample.h"
#include "../Dependencies/stb_vorbis.h"
#include "SoundManager.h"
#include <Springbok/Utils/Debug.h>
#include <AL/al.h>
#include <cassert>

SoundSample::SoundSample(const std::string& filename)
{
	// Initialize OpenAL if not done already.
	SoundManager::GetInstance();
	alGenBuffers(1, &BufferIndex);
	Location = filename;

	int error = 0;
	stb_vorbis* file = stb_vorbis_open_filename(const_cast<char*>(filename.c_str()), &error, NULL);
	if(error)
		Debug::Write("stb_vorbis error while loading $: $", filename, error);
	else
	{
		stb_vorbis_info info = stb_vorbis_get_info(file);
		int length = stb_vorbis_stream_length_in_samples(file) * info.channels;
		short* buffer = new short[length];
		stb_vorbis_get_samples_short_interleaved(file, info.channels, buffer, length);
		assert(info.channels > 0 && info.channels < 3);
		if(info.channels == 1)
			alBufferData(BufferIndex, AL_FORMAT_MONO16  , buffer, length * sizeof(short), 44100);
		else if(info.channels == 2)
			alBufferData(BufferIndex, AL_FORMAT_STEREO16, buffer, length * sizeof(short), 44100);
		delete[] buffer;
		
		Channels = info.channels;
		int alError = alGetError();
		if(alError)
			Debug::Write("OpenAL error after loading $: $", filename, alError);
	}
	//free(buffer);
}

SoundSample::~SoundSample()
{
	alDeleteBuffers(1, &BufferIndex);
}
