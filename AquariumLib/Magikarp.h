/**
 * @file Magikarp.h
 * @author kabir
 *
 * Class for a Magikarp fish
 */

#pragma once

#include "Fish.h"

/**
 * Class for an Magikarp fish
 */
class Magikarp : public Fish{
private:

public:
    /// Default constructor (disabled)
    Magikarp() = delete;

    /// Copy constructor (disabled)
    Magikarp(const Magikarp &) = delete;

    /// Assignment operator
    void operator=(const Magikarp &) = delete;

    Magikarp(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;

    void Accelerate(double elapsed);

    void Update(double elapsed) override;
};
