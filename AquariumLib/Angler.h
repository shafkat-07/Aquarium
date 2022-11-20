/**
 * @file Angler.h
 * @author kabir
 *
 * Class for an Angler fish
 */

#pragma once

#include "Fish.h"

/**
 * Class for an Angler fish
 */
class Angler : public Fish{
private:

public:
    /// Default constructor (disabled)
    Angler() = delete;

    /// Copy constructor (disabled)
    Angler(const Angler &) = delete;

    /// Assignment operator
    void operator=(const Angler &) = delete;

    Angler(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;
};
