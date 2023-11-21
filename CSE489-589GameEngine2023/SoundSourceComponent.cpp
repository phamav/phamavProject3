#include "SoundSourceComponent.h"

#define VERBOSE false


SoundSourceComponent::SoundSourceComponent( std::string soundFileName, float refDistance,
	float rollOffFactor, float maxDistance, int updateOrder)
	: SoundBaseComponent( updateOrder )
{
	// Load the sound file into a buffer.
	buffer = alutCreateBufferFromFile(soundFileName.c_str());
	SoundEngine::check_alut_errors();

	// Create a source
	alGenSources((ALuint)1, &source);
	SoundEngine::check_al_errors();

	// Associate the buffer with the source
	alSourcei(source, AL_BUFFER, buffer);
	SoundEngine::check_al_errors();

	// Set the sound reference distance roll off factor and max distance properties.
	alSourcef(source, AL_REFERENCE_DISTANCE, refDistance);
	alSourcef(source, AL_ROLLOFF_FACTOR, rollOffFactor);
	alSourcef(source, AL_MAX_DISTANCE, maxDistance);

	SoundEngine::check_al_errors();

} // SoundSource constructor


SoundSourceComponent::~SoundSourceComponent( )
{
	// Stop playing the sound
	stop();

	if (VERBOSE) cout << "~SoundSourceComponent" << endl;

	// Delete the source and the buffer
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);

} // end SoundSource destructor


void SoundSourceComponent::update(const float& deltaTime)
{
	// Call SoundBaseComponent update method
	SoundBaseComponent::update(deltaTime);
	

	// Set the position, direction, and velocity of the sound source using
	// data members inherited from SoundBaseComponent.
	alSource3f(source, AL_POSITION, soundPosition.x, soundPosition.y, soundPosition.z);
	alSource3f(source, AL_VELOCITY, soundVelocity.x, soundVelocity.y, soundVelocity.z);
	alSource3f(source, AL_DIRECTION, soundForward.x, soundForward.y, soundForward.z);

	// check for errors
	SoundEngine::check_al_errors();

} // end update

 // Start playing the sound
void SoundSourceComponent::play()
{
	// Play the source
	alSourcePlay(source);

	SoundEngine::check_al_errors();

} // end play

// Stop the sound. 
void SoundSourceComponent::stop()
{
	// Stop playing the source
	alSourceStop(source);

	SoundEngine::check_al_errors();

} // end stop

  // Pause the sound. When played again, it will start from the point 
  // where is was paused.
void SoundSourceComponent::pause()
{
	// Pause the source
	alSourcePause(source);

	SoundEngine::check_al_errors();

} // end pause

void SoundSourceComponent::continuePlaying()
{
	// Continue playing the source
	alSourcePlay(source);
	
	SoundEngine::check_al_errors();

} // end continuePlaying

void SoundSourceComponent::setLooping(bool loopingOn)
{
	// Set the source to loop
	alSourcei(source, AL_LOOPING, loopingOn ? AL_TRUE : AL_FALSE);

	SoundEngine::check_al_errors();

} // end setLooping

// Check to see if a sound it actively playing
bool SoundSourceComponent::isPlaying()
{
	ALint state;
	
	// Query for the state of the sound source
	alGetSourcei(source, AL_SOURCE_STATE, &state);

	SoundEngine::check_al_errors();

	// Return turn if the state is AL_PLAYING
	return state == AL_PLAYING;

} // end isPlaying

bool SoundSourceComponent::isPaused()
{
	ALint state;
	// Query for the state of the sound source
	alGetSourcei(source, AL_SOURCE_STATE, &state);

	SoundEngine::check_al_errors();

	// Return turn if the state is AL_PAUSED
	return state == AL_PAUSED;
	
} // end isPlaying

void SoundSourceComponent::setGain(float volume)
{
	// Set the gain "volume" of the sound source.
	alSourcef(source, AL_GAIN, volume);

	SoundEngine::check_al_errors();

} // end setGain

float SoundSourceComponent::getGain()
{
	float gain;
	
	// Query for the current gain.
	alGetSourcef(source, AL_GAIN, &gain);

	SoundEngine::check_al_errors();

	// return the gain
	return gain;

} // end getGain

void SoundSourceComponent::setReferenceDistance(float refDistance)
{
	// Set the reference distance
	alSourcef(source, AL_REFERENCE_DISTANCE, refDistance);

	SoundEngine::check_al_errors();

} // end setReferenceDistance

void SoundSourceComponent::setRollOffFactor(float rollOffFactor)
{
	// Set the roll off factor
	alSourcef(source, AL_ROLLOFF_FACTOR, rollOffFactor);

	SoundEngine::check_al_errors();

} // end setRollOffFactor

void SoundSourceComponent::setMaxDistance(float maxDistance)
{
	// Set the max distance
	alSourcef(source, AL_MAX_DISTANCE, maxDistance);

	SoundEngine::check_al_errors();

} // end setMaxDistance

