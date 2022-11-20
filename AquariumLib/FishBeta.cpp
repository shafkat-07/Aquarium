/**
 *
 * @file FishBeta.cpp
 * @author ShafkatKabir
 *
 */

#include "pch.h"
#include <string>
#include "FishBeta.h"
#include "Aquarium.h"
using namespace std;

/// Fish filename
const wstring FishBetaImageName = L"images/beta.png";

/// Maximum acceleration in the X direction in
/// in pixels per second per second
const double MaxAccelerationX = 5;

/// Minimum acceleration in the X direction in
/// pixels per second per second
const double MinAccelerationX = 2;

/// Maximum acceleration in the Y direction in
/// in pixels per second per second
const double MaxAccelerationY = 4;

/// Minimum acceleration in the Y direction in
/// pixels per second per second
const double MinAccelerationY = 1;

/// Maximum speed in the Y direction in
/// pixels per second
const double MaxSpeedY = 40;

/// Maximum speed in the X direction in
/// pixels per second
const double MaxSpeedX = 70;

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishBeta::FishBeta(Aquarium *aquarium) : Fish(aquarium, FishBetaImageName)
{
    std::uniform_real_distribution<> distributionX(MinAccelerationX, MaxAccelerationX);
    std::uniform_real_distribution<> distributionY(MinAccelerationY, MaxAccelerationY);

    mAccelerationX = distributionX(aquarium->GetRandom());
    mAccelerationY = distributionY(aquarium->GetRandom());
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishBeta::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);
    itemNode->AddAttribute(L"type", L"beta");
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
void FishBeta::Update(double elapsed)
{
    Accelerate(elapsed);
    Fish::Update(elapsed);
}

/**
 * Accelerates the fish
 * @param elapsed Time elapsed since the class call
 */
void FishBeta::Accelerate(double elapsed)
{
    auto speedX = GetSpeedX();
    auto speedY = GetSpeedY();

    if (speedX + elapsed * mAccelerationX < MaxSpeedX)
    {
        speedX = speedX + elapsed * mAccelerationX;
    }

    if (speedY + elapsed * mAccelerationY < MaxSpeedY)
    {
        speedY = speedY + elapsed * mAccelerationY;
    }

    SetSpeed(speedX, speedY);
}