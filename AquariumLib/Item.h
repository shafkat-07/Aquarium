/**
 * @file Item.h
 *
 * @author ShafkatKabir
 *
 * Base class for any item in our aquarium.
 */

#pragma once

class Aquarium;

/**
 * Base class for any item in our aquarium.
 */
class Item {
private:
    /// The aquarium this item is contained in
    Aquarium *mAquarium;

    // Item location in the aquarium
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    /// The underlying fish image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mItemBitmap;

    bool mMirror = false;   ///< True mirrors the item image

public:
    /**
    * The X location of the item
    * @return X location in pixels
    */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * The width of the fish
     * @return width of the fish in pixels
     */
    int GetWidth() const { return mItemBitmap->GetWidth(); }

    /**
     * The height of the fish
     * @return height of the fish in pixels
     */
    int GetHeight() const { return mItemBitmap->GetHeight(); }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
     * The pointer to the aquarium the Item is in
     * @return pointer to the aquarium
     */
    Aquarium *GetAquarium(){ return mAquarium; }

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

    /// Destructor
    virtual ~Item();

    /**
     * Draw this item
     * @param dc Device context to draw on
     */
    void Draw(wxDC *dc);

    /**
     * Compute the distance from this item to another item
     * @param item Item we are computing the distance to
     * @return Distance in pixels
     */
    double DistanceTo(std::shared_ptr<Item> item);

    /**
     * Test this item to see if it has been clicked on
     * @param x X location on the aquarium to test in pixels
     * @param y Y location on the aquarium to test in pixels
     * @return true if clicked on
     */
    bool HitTest(int x, int y);

    virtual wxXmlNode* XmlSave(wxXmlNode* node);
    virtual void XmlLoad(wxXmlNode* node);
    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    void SetMirror(bool m);
protected:
    Item(Aquarium *aquarium, const std::wstring &filename);
};
