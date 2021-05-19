#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <utility>
#include <algorithm>
#include "user.h"
#include "pet.h"
#include "location.h"
#include "petowner.h"

float getScore(User user, Pet pet);
std::vector<std::pair<Pet, float>> sortByMatch(std::vector<Pet> pets);
double distance(double lat1, double long1, double lat2, double long2);
double distanceToUser(const Location& start, User user);

#endif
