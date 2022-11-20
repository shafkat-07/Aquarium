/**
 * @file Fish.h
 * @author kabir
 *
 * Base Class for all the fish items
 */

#pragma once

#include "Item.h"

/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class Fish : public Item{
private:
    /// Fish speed in the X direction
    /// in pixels per second
    double mSpeedX;

    /// Fish speed in the Y direction
    /// in pixels per second
    double mSpeedY;
public:
    /// Default constructor (disabled)
    Fish() = delete;

    /// Copy constructor (disabled)
    Fish(const Fish &) = delete;

    /// Assignment operator
    void operator=(const Fish &) = delete;

    /**
     * Gets the speed in the X direction
     * @return speed in the X direction
     */
    double GetSpeedX(){ return mSpeedX; }

    /**
     * Gets the speed in the Y direction
     * @return speed in the Y direction
     */
    double GetSpeedY(){ return mSpeedY; }

    void SetSpeed(double speedX, double speedY);

    virtual void Update(double elapsed);
    wxXmlNode* XmlSave(wxXmlNode* node) override;

protected:
    Fish(Aquarium* aquarium, const std::wstring& filename);

    void XmlLoad(wxXmlNode* node);
};
