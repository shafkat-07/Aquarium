/**
 * @file Castle.h
 * @author kabir
 *
 * Class for castle item
 */

#include "Item.h"

#pragma once

/**
 * Class for castle item
 */
class Castle : public Item {
private:

public:
    /// Default constructor (disabled)
    Castle() = delete;

    /// Copy constructor (disabled)
    Castle(const Castle &) = delete;

    /// Assignment operator
    void operator=(const Castle &) = delete;

    /**
     * Constructor
     * @param aquarium Aquarium this castle is a part of
     */
    Castle(Aquarium *aquarium);

    /**
     * Save this fish to an XML node
     * @param node The parent node we are going to be a child of
     * @return
     */
    wxXmlNode* XmlSave(wxXmlNode* node) override;
};
