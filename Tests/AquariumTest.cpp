//
// Created by kabir on 9/14/2022.
//

/**
 *
 * @file AquariumTest.cpp
 * @author ShafkatKabir
 *
 */

#include <pch.h>
#include <wx/filename.h>
#include "gtest/gtest.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <Aquarium.h>
#include <FishBeta.h>
#include <Castle.h>
#include <Angler.h>
#include <Magikarp.h>

using namespace std;

const unsigned int RandomSeed = 1238197374;

class AquariumTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/aquarium";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

        return str;
    }

    /**
 * Test to ensure an aquarium .aqua file is empty
 */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));
    }

    /**
     *  Populate an aquarium with three Beta fish
     */
    void PopulateThreeBetas(Aquarium *aquarium)
    {
        aquarium->GetRandom().seed(RandomSeed);
        auto fish1 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(100, 200);

        auto fish2 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(400, 400);

        auto fish3 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(600, 100);
    }

    /**
     * Populate the aquarium with all types
     */
    void PopulateAllTypes(Aquarium *aquarium)
    {
        aquarium->GetRandom().seed(RandomSeed);

        auto fish1 = make_shared<Angler>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(100, 200);

        auto fish2 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(400, 400);

        auto fish3 = make_shared<Magikarp>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(600, 100);

        auto castle1 = make_shared<Castle>(aquarium);
        aquarium->Add(castle1);
        castle1->SetLocation(600, 600);

        auto fish4 = make_shared<Angler>(aquarium);
        aquarium->Add(fish4);
        fish4->SetLocation(535, 132);

        auto fish5 = make_shared<Magikarp>(aquarium);
        aquarium->Add(fish5);
        fish5->SetLocation(300, 400);

        auto castle2 = make_shared<Castle>(aquarium);
        aquarium->Add(castle2);
        castle2->SetLocation(600, 300);
    }

    void TestThreeBetas(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

        // Ensure the positions and speeds are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedx=\"34\\.6892.*\" speedy=\"23\\.7355.*\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedx=\"48\\.756.*\" speedy=\"29\\.7539.*\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\" speedx=\"21\\.8432.*\" speedy=\"17\\.0998.*\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
    }


    void TestAllTypes(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

        // Ensure the positions and speeds are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedx=\"34\\.6892.*\" speedy=\"23\\.7355.*\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedx=\"40\\.6797.*\" speedy=\"24\\.7838.*\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\" speedx=\"7\\.15038.*\" speedy=\"13\\.5499.*\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"600\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"535\" y=\"132\" speedx=\"20\\.0011.*\" speedy=\"28\\.1488.*\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"300\" y=\"400\" speedx=\"5\\.82512.*\" speedy=\"12\\.5423.*\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"300\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"angler\"/><item.* type=\"beta\"/><item.* type=\"magikarp\"/><item.* type=\"castle\"/><item.* type=\"angler\"/><item.* type=\"magikarp\"/><item.* type=\"castle\"/></aqua>")));
    }
};

TEST_F(AquariumTest, Save) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    //
    // Now populate the aquarium
    //

    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);
    //TestAllTypesSpeed(file3);

}

TEST_F(AquariumTest, Load) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;
    Aquarium aquarium2;

    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test4.aqua";
    aquarium.Save(file2);
    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test5.aqua";
    aquarium3.Save(file3);
    TestAllTypes(file3);

    aquarium2.Load(file2);
    aquarium2.Save(file2);
    TestThreeBetas(file2);

    aquarium3.Load(file3);
    aquarium3.Save(file3);
    TestAllTypes(file3);
}

TEST_F(AquariumTest, Clear)
{
    Aquarium aquarium;
    PopulateAllTypes(&aquarium);

    aquarium.Clear();

    auto path = TempPath();
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    auto file2 = path + L"/test2.aqua";

    Aquarium aquarium2;
    PopulateThreeBetas(&aquarium2);
    aquarium2.Clear();

    aquarium2.Save(file2);

    TestEmpty(file2);
}

TEST_F(AquariumTest, Construct){
    Aquarium aquarium;
}

TEST_F(AquariumTest, HitTest) {
    Aquarium aquarium;

    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) <<
                                                   L"Testing empty aquarium";

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) <<
                                                     L"Testing fish at 100, 200";
    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish2);
    fish2->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish2) <<
    L"Testing second fish at (100, 200)";

    shared_ptr<FishBeta> fish3 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish3);
    fish3->SetLocation(100, 200);

    ASSERT_EQ(aquarium.HitTest(100,200), fish3) <<
                                                L"Testing second fish at (100, 200)";


    ASSERT_EQ(nullptr, aquarium.HitTest(500,500)) <<
    L"Testing when there is no image at (500, 500)";

    ASSERT_EQ(nullptr, aquarium.HitTest(0,500)) <<
                                                L"Testing when there is no image at (0, 500)";
}

//TEST(AquariumTest, NonoverlappingAdd1) {
//    Aquarium aquarium;
//
//    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
//    aquarium.Add(fish1);
//
//    ASSERT_NEAR(200, fish1->GetX(), 0.1);
//    ASSERT_NEAR(200, fish1->GetY(), 0.1);
//
//    // First fish moved to 210, 210
//    fish1->SetLocation(210, 210);
//
//    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
//    aquarium.Add(fish2);
//
//    // Second fish should be created at 200, 200, since there
//    // is not a fish there.
//    ASSERT_NEAR(200, fish2->GetX(), 0.1);
//    ASSERT_NEAR(200, fish2->GetY(), 0.1);
//
//    shared_ptr<FishBeta> fish3 = make_shared<FishBeta>(&aquarium);
//    aquarium.Add(fish3);
//
//    // Since there are fish at (200, 200) and (210, 210),
//    // this fish should have been created at (220, 220)
//    ASSERT_NEAR(220, fish3->GetX(), 0.1);
//    ASSERT_NEAR(220, fish3->GetY(), 0.1);
//}
//
//TEST(AquariumTest, NonoverlappingAdd2) {
//    Aquarium aquarium;
//
//    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
//    aquarium.Add(fish1);
//
//    ASSERT_NEAR(200, fish1->GetX(), 0.1);
//    ASSERT_NEAR(200, fish1->GetY(), 0.1);
//
//    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
//    aquarium.Add(fish2);
//
//    ASSERT_NEAR(210, fish2->GetX(), 0.1);
//    ASSERT_NEAR(210, fish2->GetY(), 0.1);
//
//    fish1->SetLocation(220, 220);
//    // Fish are now at (220, 220), (210, 210)
//
//    shared_ptr<FishBeta> fish3 = make_shared<FishBeta>(&aquarium);
//    aquarium.Add(fish3);
//
//    // Since nothing is at (200, 200), the fish should be created there
//    ASSERT_NEAR(200, fish3->GetX(), 0.1);
//    ASSERT_NEAR(200, fish3->GetY(), 0.1);
//
//    fish2->SetLocation(230, 230);
//    // Fish are now at (220, 220), (230, 230), (200, 200)
//
//    shared_ptr<FishBeta> fish4 = make_shared<FishBeta>(&aquarium);
//    aquarium.Add(fish4);
//
//    // No fish at 210, 210, so should be created there.
//    ASSERT_NEAR(210, fish4->GetX(), 0.1);
//    ASSERT_NEAR(210, fish4->GetY(), 0.1);
//}