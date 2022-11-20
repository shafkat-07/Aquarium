/**
 * @file Fish.cpp
 * @author kabir
 */

#include "pch.h"
#include <random>
#include "Fish.h"
#include "Aquarium.h"

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 20;

/// Maximum speed in the Y direction in
/// in pixels per second
const double MaxSpeedY = 30;

/// Minimum speed in the Y direction in
/// pixels per second
const double MinSpeedY = 10;

/**
* Constructor
* @param aquarium The aquarium we are in
* @param filename Filename for the image we use
*/
Fish::Fish(Aquarium *aquarium, const std::wstring &filename) : Item(aquarium, filename)
{
    std::uniform_real_distribution<> distributionX(MinSpeedX, MaxSpeedX);
    std::uniform_real_distribution<> distributionY(MinSpeedY, MaxSpeedY);
    mSpeedX = distributionX(aquarium->GetRandom());
    mSpeedY = distributionY(aquarium->GetRandom());
}

/**
 * Set Speed of fish
 * @param speedX speed in the X direction
 * @param speedY speed in the Y direction
 */
void Fish::SetSpeed(double speedX, double speedY)
{
    mSpeedX = speedX;
    mSpeedY = speedY;
}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Fish::Update(double elapsed)
{
    SetLocation(GetX() + mSpeedX * elapsed,
            GetY() + mSpeedY * elapsed);


    if (mSpeedX > 0 && GetX() + GetWidth() / 2 >= GetAquarium()->GetWidth() - 10)
    {
        mSpeedX = -mSpeedX;
        SetMirror(true);
    }

    else if (mSpeedX < 0 && GetX() - GetWidth() / 2 < 10){
        mSpeedX = -mSpeedX;
        SetMirror(false);
    }

    else if (mSpeedX < 0)
    {
        SetMirror(true);
    }

    else if (mSpeedX > 0)
    {
        SetMirror(false);
    }

    if (mSpeedY > 0 && GetY() + GetHeight() / 2 >= GetAquarium()->GetHeight() - 10 || mSpeedY < 0 && GetY() - GetHeight() / 2 < 10)
    {
        mSpeedY = -mSpeedY;
    }
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* Fish::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"speedx", wxString::FromDouble(mSpeedX));
    itemNode->AddAttribute(L"speedy", wxString::FromDouble(mSpeedY));
    return itemNode;
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Fish::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
    node->GetAttribute("speedx", "0").ToDouble(&mSpeedX);
    node->GetAttribute("speedy"
            , "0").ToDouble(&mSpeedY);

    if (mSpeedX < 0)
    {
        SetMirror(true);
    }
}