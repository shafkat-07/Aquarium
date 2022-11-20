/**
 * @file Angler.cpp
 * @author kabir
 */

#include "pch.h"
#include <string>
#include "Angler.h"

using namespace std;

/// Angler filename
const wstring AnglerImageName = L"images/angler.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
Angler::Angler(Aquarium *aquarium) : Fish(aquarium, AnglerImageName)
{
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* Angler::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);
    itemNode->AddAttribute(L"type", L"angler");
    return itemNode;
}

