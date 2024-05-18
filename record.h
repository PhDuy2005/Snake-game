#pragma once
#include <fstream>

string classicEasy = "classic_easy_record.txt";
string classicMed = "classic_med_record.txt";
string classicHard = "classic_hard_record.txt";

string modernEasy = "modern_easy_record.txt";
string modernMed = "modern_med_record.txt";
string modernHard = "modern_hard_record.txt";

ifstream classic_easy_fileIn(classicEasy);
ifstream classic_med_fileIn(classicMed);
ifstream classic_hard_fileIn(classicHard);

ifstream modern_easy_fileIn(modernEasy);
ifstream modern_med_fileIn(modernEasy);
ifstream modern_hard_fileIn(modernEasy);

