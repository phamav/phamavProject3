#include "SoundListenerComponent.h"

SoundListenerComponent::SoundListenerComponent(int updateOrder)
    : SoundBaseComponent(updateOrder) {}

void SoundListenerComponent::update(const float& deltaTime) {
    // Call SoundBaseComponent update method
    SoundBaseComponent::update(deltaTime);

    // Updates the position, velocity, and orientation of the listener
    alListener3f(AL_POSITION, soundPosition.x, soundPosition.y, soundPosition.z);
    alListener3f(AL_VELOCITY, soundVelocity.x, soundVelocity.y, soundVelocity.z);

    ALfloat orientation[] = { soundForward.x, soundForward.y, soundForward.z,
                              soundUp.x, soundUp.y, soundUp.z };
    alListenerfv(AL_ORIENTATION, orientation);

    // check for errors
    SoundEngine::check_al_errors();
}
