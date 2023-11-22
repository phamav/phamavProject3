#pragma once

// Shader program building
#include "BuildShaderProgram.h"
#include "Texture.h"

// Shared Uniform Blocks
#include "SharedMaterials.h"
#include "SharedTransformations.h"
#include "SharedLighting.h"

// Component container
#include "GameObject.h"

// Custom GameObjects
#include "Game.h"

// Camera
#include "CameraComponent.h"

// GameObject Management


// Lights
#include "LightComponent.h"
#include "PositionalLightComponent.h"
#include "DirectionalLightComponent.h"
#include "SpotLightComponent.h"


// Meshes
#include "SphereMeshComponent.h"
#include "BoxMeshComponent.h"

// Movement
#include "ArrowRotateComponent.h"

// Physics
#include "SpinComponent.h"
#include "PhysicsEngine.h"
#include "SteeringComponent.h"
#include "WaypointComponent.h"
#include "JourneyComponent.h"
#include "CollisionComponent.h"
#include "RigidBodyComponent.h"

// Sound
#include "SoundEngine.h"
#include "SoundBaseComponent.h"
#include "SoundListenerComponent.h"
#include "SoundSourceComponent.h"

// Model
#include "ModelMeshComponent.h"

// Fog
#include "SharedFog.h"