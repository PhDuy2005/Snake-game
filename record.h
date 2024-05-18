#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

string classicEasyFile = "classic_easy_record.txt";
string classicMedFile = "classic_med_record.txt";
string classicHardFile = "classic_hard_record.txt";

string modernEasyFile = "modern_easy_record.txt";
string modernMedFile = "modern_med_record.txt";
string modernHardFile = "modern_hard_record.txt";

ifstream classic_easy_fileIn(classicEasyFile, ios_base::in);
ifstream classic_med_fileIn(classicMedFile, ios_base::in);
ifstream classic_hard_fileIn(classicHardFile, ios_base::in);

ifstream modern_easy_fileIn(modernEasyFile, ios_base::in);
ifstream modern_med_fileIn(modernEasyFile, ios_base::in);
ifstream modern_hard_fileIn(modernEasyFile, ios_base::in);

ofstream classic_easy_fileOut(classicEasyFile, ios_base::out);
ofstream classic_med_fileOut(classicMedFile, ios_base::out);
ofstream classic_hard_fileOut(classicHardFile, ios_base::out);

ofstream modern_easy_fileOut(modernEasyFile, ios_base::out);
ofstream modern_med_fileOut(modernEasyFile, ios_base::out);
ofstream modern_hard_fileOut(modernEasyFile, ios_base::out);

enum MODE {classic = 2, modern = 1};
enum DIFF {ez = 1, med = 2, hard = 3};

struct playerRecord {
	int score;
	string name;
};

vector<playerRecord> classsicEasyVector;
vector<playerRecord> classsicMedVector;
vector<playerRecord> classsicHardVector;

vector<playerRecord> modernEasyVector;
vector<playerRecord> modernMedVector;
vector<playerRecord> modernHardVector;

void readDataFromFile(vector<playerRecord>& container, ifstream& fi) {
	if (!fi) {
		cerr << "Unable to open\n";
		return;
	}

	string line;
	while (getline(fi, line)) {
		istringstream ss(line);
		int player_score;
		string player_name;

		ss >> player_score;
		ss.ignore(1, '|');
		getline(ss, player_name, '\n');

		playerRecord player = { player_score, player_name };
		container.push_back(player);
	}

	while (container.size() > 5)
		container.erase(container.begin() + 5);
}

void readDataFromAllFiles() {
	readDataFromFile(classsicEasyVector, classic_easy_fileIn);
	readDataFromFile(classsicMedVector, classic_med_fileIn);
	readDataFromFile(classsicHardVector, classic_hard_fileIn);

	readDataFromFile(classsicEasyVector, modern_easy_fileIn);
	readDataFromFile(classsicMedVector, modern_med_fileIn);
	readDataFromFile(classsicHardVector, modern_hard_fileIn);
}