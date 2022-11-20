/**
 * @file FishBeta.h
 *
 * @author ShafkatKabir
 *
 * Class to describe our fish
 */

#pragma once

#include "Fish.h"


/**
 * Class for an Beta fish
 */
class FishBeta : public Fish {
private:
    /// The acceleration of FishBeta in the X direction
    double mAccelerationX;

    /// The acceleration of FishBeta in the Y direction
    double mAccelerationY;
public:
    /// Default constructor (disabled)
    FishBeta() = delete;

    /// Copy constructor (disabled)
    FishBeta(const FishBeta &) = delete;

    /// Assignment operator
    void operator=(const FishBeta &) = delete;
    FishBeta(Aquarium* aquarium);
    wxXmlNode* XmlSave(wxXmlNode* node) override;

    void Update(double elapsed) override;

    void Accelerate(double elapsed);
};
