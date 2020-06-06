#pragma once
#include "raylib.h"
#include "Global.h"
#include "Random.h"
#include "Particle.h"

#include <vector>
#include <memory>

class ParticleGenerator
{
private:
    Texture2D mTexture;

	const unsigned int mMaxNumberOfParticles;
	const float mMaxLife;

	float mElapsedTime = 0.0f; //seconds
	float mNewPartilceTime = 0.05f; //seconds
	std::vector<Particle> mParticles;	

	void addANewParticle(const Vector2& position);

public:
	ParticleGenerator(Texture2D texture, int texureWidth, int textureHeight, unsigned int maxNumberOfParticles, float maxLife);
	~ParticleGenerator();

	void clear() { mParticles.clear(); }
	void update(float deltaTime, Vector2 position);
	void render() const;
};