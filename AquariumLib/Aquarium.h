/**
 * @file Aquarium.h
 *
 * @author ShafkatKabir
 *
 * Class that describes our aquarium
 *
 */

#pragma once

#include <random>

class Item;
/**
 * Class aquarium describes our aquarium
 */
class Aquarium {
private:
    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<Item>> mItems;
    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use

    /// Random number generator
    std::mt19937 mRandom;
public:
    void OnDraw(wxDC *dc);
    Aquarium();

    void Add(std::shared_ptr<Item> item);

    std::shared_ptr<Item> HitTest(int x, int y);

    void MoveToFront(std::shared_ptr<Item> item);

    void Save(const wxString& filename);

    void Load(const wxString& filename);

    void Clear();

    void XmlItem(wxXmlNode* node);

    void Update(double elapsed);

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() {return mRandom;}

    /**
     * Get the width of the aquarium
     * @return Aquarium width in pixels
     */
    int GetWidth() const { return mBackground->GetWidth(); }

    /**
     * Get the height of the aquarium
     * @return Aquarium height in pixels
     */
    int GetHeight() const { return mBackground->GetHeight(); }
};
