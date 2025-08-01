#pragma once
#include "Statemachine/GameObject.h"
#include "CollisionManager.h"
class Bullet :
    public GameObject
{
public:
    Bullet();
    ~Bullet();
    
    void Update(float aDeltaTime) override;
    void SetDir(const Tga2D::Vector2f& aDir) { myDir = aDir; }
    void SetTarget(eTag::Enum aTag) { myTarget = aTag; }

    static std::vector<Bullet*> GetBullets() { return ourBullets; }
private:
    inline static std::vector<Bullet*> ourBullets;
    const float mySpeed = .2f;
    Tga2D::Vector2f myDir;
    eTag::Enum myTarget = eTag::Obstacle;
};

