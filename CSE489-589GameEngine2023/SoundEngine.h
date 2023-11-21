#pragma once

#include "MathLibsConstsFuncs.h"

// Includes for the OpenAL Sound Engine
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

// Depending on the OpenAL install you will need to modify the 
// include statements in alut.h to read as follows
//#include <AL/alc.h>
//#include <AL/al.h>

// For OpenAL information see
// See https://www.openal.org/documentation/openal-1.1-specification.pdf

// For free sounds 
// See https://www.soundjay.com/

// IMPORTANT: To play 3D sounds with OpenAL sound files must be single channel 
// i.e. mono. To convert to single channel
// use Audacity https://www.audacityteam.org/download/windows/
// follow instructions at 
// https://www.laptopmag.com/how-to/convert-stereo-audio-file-to-mono-using-audacity

using namespace constants_and_types;

class SoundEngine 
{
public:

	/**
	 * @fn	static bool SoundEngine::Init(ALint distanceModel = AL_INVERSE_DISTANCE, ALfloat dopplerFactor = 1.0f);
	 *
	 * @brief	Initialize the sound engine.
	 *
	 * @param 	distanceModel	(Optional) The distance model.
	 * @param 	dopplerFactor	(Optional) The doppler factor.
	 *
	 * @returns	True if it succeeds, false if it fails.
	 */
	static bool Init(ALint distanceModel = AL_INVERSE_DISTANCE, ALfloat dopplerFactor = 1.0f);

	/**
	 * @fn	static void SoundEngine::Update(const float & deltaTime = 0.0f);
	 *
	 * @brief	Update the sound engine. Call this once each frame.
	 *
	 * @param	deltaTime	(Optional) The delta time.
	 */
	static void Update(const float & deltaTime = 0.0f);

	/**
	 * @fn	static void SoundEngine::Stop();
	 *
	 * @brief	Stop the sound engine. Call when closing down
	 */
	static void Stop();

	/**
	 * @fn	static bool SoundEngine::check_al_errors();
	 *
	 * @brief	Checks for OpenAL error and prints error messages.
	 *
	 * @returns	True if there are no errors.
	 */
	static bool check_al_errors();

	/**
	 * @fn	static bool SoundEngine::check_alut_errors();
	 *
	 * @brief	Checks for errors that occurr when ALUT functions
	 * 			are called
	 *
	 * @returns	True if there are no errors.
	 */
	static bool check_alut_errors();

	friend class SoundBaseComponent;
	friend class SoundListenerComponent;
	friend class SoundSourceComponent;

protected:

	//static ALCdevice* device;
	//static ALCcontext* context;

}; // end SoundEngine class

