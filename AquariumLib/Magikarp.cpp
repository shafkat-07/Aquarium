/**
 * @file Magikarp.cpp
 * @author kabir
 */

#include "pch.h"
#include <string>
#include <random>
#include "Magikarp.h"
#include "Aquarium.h"

using namespace std;

/// Maximum acceleration in the X direction in
/// in pixels per second per second
const double MaxAccelerationX = 4;

/// Minimum acceleration in the X direction in
/// pixels per second per second
const double MinAccelerationX = -5;

/// Maximum acceleration in the Y direction in
/// in pixels per second per second
const double MaxAccelerationY = 3;

/// Minimum acceleration in the Y direction in
/// pixels per second per second
const double MinAccelerationY = -7;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 40;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 5;

/// Maximum speed in the Y direction in
/// in pixels per second
const double MaxSpeedY = 20;

/// Minimum speed in the Y direction in
/// pixels per second
const double MinSpeedY = 10;

/// Magikarp filename
const wstring MagikarpImageName = L"images/magikarp.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
Magikarp::Magikarp(Aquarium *aquarium) : Fish(aquarium, MagikarpImageName)
{
    std::uniform_real_distribution<> distributionX(MinSpeedX, MaxSpeedX);
    std::uniform_real_distribution<> distributionY(MinSpeedY, MaxSpeedY);

    auto speedX = distributionX(aquarium->GetRandom());
    auto speedY = distributionY(aquarium->GetRandom());

    SetSpeed(speedX, speedY);
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* Magikarp::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);
    itemNode->AddAttribute(L"type", L"magikarp");
    return itemNode;
}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Magikarp::Update(double elapsed)
{
    Accelerate(elapsed);
    Fish::Update(elapsed);
}

/**
 * Accelerates the fish
 * @param elapsed Time elapsed since the class call
 */
void Magikarp::Accelerate(double elapsed)
{
    std::uniform_real_distribution<> distributionX(MinAccelerationX, MaxAccelerationX);
    std::uniform_real_distribution<> distributionY(MinAccelerationY, MaxAccelerationY);

    auto accelerationX = distributionX(GetAquarium()->GetRandom());
    auto accelerationY = distributionY(GetAquarium()->GetRandom());
    auto speedx = GetSpeedX();
    auto speedy = GetSpeedY();

    if (speedx + elapsed * accelerationX < MaxSpeedX)
    {
        speedx = speedx + elapsed * accelerationX;
    }

    if (speedy + elapsed * accelerationY < MaxSpeedY)
    {
        speedy = speedy + elapsed * accelerationY;
    }

    SetSpeed(speedx, speedy);
}