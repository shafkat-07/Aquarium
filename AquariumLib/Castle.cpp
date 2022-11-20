/**
 * @file Castle.cpp
 * @author kabir
 */

#include "pch.h"
#include <string>
#include "Castle.h"

using namespace std;

/// Castle Filename
const wstring CastleImageName = L"images/castle.png";

Castle::Castle(Aquarium *aquarium) : Item(aquarium, CastleImageName)
{
}

wxXmlNode* Castle::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"castle");
    return itemNode;
}
