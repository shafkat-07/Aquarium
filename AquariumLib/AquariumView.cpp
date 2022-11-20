/**

 * @file AquariumView.cpp
 * @author ShafkatKabir
 *
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include <algorithm>
#include "AquariumView.h"
#include "ids.h"
#include "FishBeta.h"
#include "Magikarp.h"
#include "Angler.h"
#include "Castle.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void AquariumView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishMagikarp, this, IDM_ADDFISHMAGIKARP);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishAngler, this, IDM_ADDFISHANGLER);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddCastle, this, IDM_ADDCASTLE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileSaveAs, this, wxID_SAVEAS);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileOpen, this, wxID_OPEN);
    Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);
    Bind(wxEVT_TIMER, &AquariumView::OnTimer, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void AquariumView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mAquarium.OnDraw(&dc);

    mAquarium.Update(elapsed);
}

/**
 * Menu hander for Add Fish>Angler
 * @param event Mouse event
 */
void AquariumView::OnAddFishAngler(wxCommandEvent& event)
{
    auto fish = make_shared<Angler>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu hander for Add Fish>Magikarp
 * @param event Mouse event
 */
void AquariumView::OnAddFishMagikarp(wxCommandEvent& event)
{
    auto fish = make_shared<Magikarp>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu hander for Add Fish>Beta Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishBeta>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu hander for Add Fish>Beta Fish
 * @param event Mouse event
 */
void AquariumView::OnAddCastle(wxCommandEvent& event)
{
    auto castle = make_shared<Castle>(&mAquarium);
    mAquarium.Add(castle);
    Refresh();
}

/**
 * Menu handler for File>Save As menu option
 * @param event The menu event
 */
void AquariumView::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, ("Save Aquarium file"), "", "",
            "Aquarium Files (*.aqua)|*.aqua", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();
    mAquarium.Save(filename);
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void AquariumView::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, ("Load Aquarium file"), "", "",
            "Aquarium Files (*.aqua)|*.aqua", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    mAquarium.Load(filename);
    Refresh();
}

/**
 * Event handler for the timer
 * @param event Timer event
 */
void AquariumView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}

/**
 * Handle the left mouse button down event
 * @param event Mouse event
 */
void AquariumView::OnLeftDown(wxMouseEvent &event)
{
    mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());
    if (mGrabbedItem != nullptr)
    {
        mAquarium.MoveToFront(mGrabbedItem);
        Refresh();
    }
}

/**
* Handle the left mouse button down event
* @param event Mouse event
*/
void AquariumView::OnLeftUp(wxMouseEvent &event)
{

}

/**
* Handle the left mouse button down event
* @param event Mouse event
*/
void AquariumView::OnMouseMove(wxMouseEvent &event)
{
// See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
        }
        else
        {
            // When the left button is released, we release the
            // item.
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }
}
