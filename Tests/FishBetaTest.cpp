/**
 * @file FishBetaTest.cpp
 * @author kabir
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <FishBeta.h>
#include <Aquarium.h>

using namespace std;

TEST(FishBeta, Construct){
    Aquarium aquarium;
    FishBeta fishBeta(&aquarium);
}
