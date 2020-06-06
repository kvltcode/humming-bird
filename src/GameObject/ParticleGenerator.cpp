#include "ParticleGenerator.h"
#include <algorithm>

ParticleGenerator::ParticleGenerator(Texture2D texture, int texureWidth, int textureHeight, unsigned int maxNumberOfParticles, float maxLife):
mTexture(texture),
mMaxNumberOfParticles(maxNumberOfParticles),
mMaxLife(maxLife)
{
    mTexture.width = texureWidth;
    mTexture.height = textureHeight;
}

ParticleGenerator::~ParticleGenerator()
{
    UnloadTexture(mTexture);
}

void ParticleGenerator::addANewParticle(const Vector2& position)
{
    Particle temp;
    temp.position.x = position.x;
    temp.position.y = position.y + Random::GetInstance().drawNumber(0.0f, 30.0f);

    //flows slightly behind the position
    //then random speed falling done the screen
    temp.velocity = Vector2{
        -2.0f,
        Random::GetInstance().drawNumber(0.1f, 3.0f) };    

    temp.colour = Color{
        static_cast<unsigned char>(Random::GetInstance().drawNumber(100, 255)),
        static_cast<unsigned char>(Random::GetInstance().drawNumber(100, 255)),
        static_cast<unsigned char>(Random::GetInstance().drawNumber(100, 255)),
        255};
    
    temp.life     = Random::GetInstance().drawNumber(0.5f, mMaxLife); 
    temp.scale    = Random::GetInstance().drawNumber(0.3f, 1.0f);
    temp.rotation = Random::GetInstance().drawNumber(0.0f, 360.0f);        

    mParticles.push_back(temp);
}

void ParticleGenerator::update(float deltaTime, Vector2 position)
{
    mElapsedTime += deltaTime;
    if (mElapsedTime >= mNewPartilceTime)
    {   
        addANewParticle(position);

        mElapsedTime = 0.0f;
    }   

    for (auto& particle : mParticles)
    {  
        particle.life -= deltaTime;     
        float ratio = static_cast<unsigned char>(255 / mMaxLife); //255 because that's the max colour value
        particle.colour.a =  static_cast<unsigned char>(particle.life * ratio);   //Note - this gets cut
        particle.position.x += particle.velocity.x;
        particle.position.y += particle.velocity.y;

        particle.rotation -= 1.0f;
        if (particle.rotation >= 360) { particle.rotation = 0.0f; }
    }

    auto iterator = std::remove_if(mParticles.begin(), mParticles.end(), [&](Particle particle) -> bool
    {
        return particle.life <= 0.0f;
    });

    mParticles.erase(iterator, mParticles.end());
}

void ParticleGenerator::render() const
{
    BeginBlendMode(BLEND_ALPHA);
    for (auto& particle : mParticles)
    {
        if (particle.life > 0.0f)
        {
            DrawTextureEx(mTexture, particle.position, particle.rotation, particle.scale, particle.colour);
        }
    }
    EndBlendMode();
}