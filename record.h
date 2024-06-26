#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

string classicEasyFile = "classic_easy_record.txt";
string classicMedFile = "classic_med_record.txt";
string classicHardFile = "classic_hard_record.txt";

string modernEasyFile = "modern_easy_record.txt";
string modernMedFile = "modern_med_record.txt";
string modernHardFile = "modern_hard_record.txt";

//ifstream classic_easy_fileIn(classicEasyFile);
//ifstream classic_med_fileIn(classicMedFile);
//ifstream classic_hard_fileIn(classicHardFile);
//
//ifstream modern_easy_fileIn(modernEasyFile);
//ifstream modern_med_fileIn(modernEasyFile);
//ifstream modern_hard_fileIn(modernEasyFile);

//ofstream classic_easy_fileOut(classicEasyFile, ios_base::out);
//ofstream classic_med_fileOut(classicMedFile, ios_base::out);
//ofstream classic_hard_fileOut(classicHardFile, ios_base::out);
//
//ofstream modern_easy_fileOut(modernEasyFile, ios_base::out);
//ofstream modern_med_fileOut(modernEasyFile, ios_base::out);
//ofstream modern_hard_fileOut(modernEasyFile, ios_base::out);


//enum MODE { classic = 1, modern = 2 };
//enum DIFF { ez = 1, med = 2, hard = 3 };

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

void readDataFromFile(vector<playerRecord>& container, string filename) {
	ifstream fi(filename);
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
	readDataFromFile(classsicEasyVector, classicEasyFile);
	readDataFromFile(classsicMedVector, classicMedFile);
	readDataFromFile(classsicHardVector, classicHardFile);

	readDataFromFile(classsicEasyVector, modernEasyFile);
	readDataFromFile(classsicMedVector, modernMedFile);
	readDataFromFile(classsicHardVector, modernHardFile);
}