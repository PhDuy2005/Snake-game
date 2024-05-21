#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;


struct playerRecord {
	int score = 0;
	string name = "NULL";
};


void readDataFromFile(vector<playerRecord>& container, string filename);
void readDataFromAllFiles();
playerRecord getInformation();
void checkHighScore();
void sortRecord(vector<playerRecord>& container);
void writeDataToFile(vector<playerRecord> container ,string filename);
void writeDataToAllFiles();



string classicEasyFile = "record/classic_easy_record.txt";
string classicMedFile = "record/classic_med_record.txt";
string classicHardFile = "record/classic_hard_record.txt";

string modernEasyFile = "record/modern_easy_record.txt";
string modernMedFile = "record/modern_med_record.txt";
string modernHardFile = "record/modern_hard_record.txt";

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



vector<playerRecord> classicEasyVector;
vector<playerRecord> classicMedVector;
vector<playerRecord> classicHardVector;

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
	readDataFromFile(classicEasyVector, classicEasyFile);
	readDataFromFile(classicMedVector, classicMedFile);
	readDataFromFile(classicHardVector, classicHardFile);

	readDataFromFile(classicEasyVector, modernEasyFile);
	readDataFromFile(classicMedVector, modernMedFile);
	readDataFromFile(classicHardVector, modernHardFile);
}

playerRecord getInformation(){
	playerRecord info;

	vector<char> name_inCharArray;

	gotoXY(50, 10);
	cout << "Score: ";
	gotoXY(50, 12);
	cout << "Enter your name: ";

	while(1){
		if (_kbhit()){
			char c = getch();
			if (c >= 32 && c <= 122){
				name_inCharArray.push_back(c);
				cout << c;
			}
			if (c == '\n'){
				break;
			}
		}
	}


	info.score = Score;
	string temp(name_inCharArray.begin(), name_inCharArray.end());
	info.name = temp;
	return info;
}

void checkHighScore() {
	switch (Mode) {
	case MODE::classic:
		switch (Level) {
		case DIFF::ez:
			if (Score > classicEasyVector[4].score){
				playerRecord info = getInformation();
				classicEasyVector.erase(classicEasyVector.begin() + 4);
				classicEasyVector.push_back(info);
			}
			break;
		case DIFF::med:
			if (Score > classicMedVector[4].score){
				playerRecord info = getInformation();
				classicMedVector.erase(classicMedVector.begin() + 4);
				classicMedVector.push_back(info);
			}
			break;
		case DIFF::hard:
			if (Score > classicHardVector[4].score){
				playerRecord info = getInformation();
				classicHardVector.erase(classicHardVector.begin() + 4);
				classicHardVector.push_back(info);
			}
			break;
		}
		break;
	case MODE::modern:
		switch (Level) {
		case DIFF::ez:
			if (Score > modernEasyVector[4].score){
				playerRecord info = getInformation();
				modernEasyVector.erase(modernEasyVector.begin() + 4);
				modernEasyVector.push_back(info);
			}
			break;
		case DIFF::med:
			if (Score > modernMedVector[4].score){
				playerRecord info = getInformation();
				modernMedVector.erase(modernMedVector.begin() + 4);
				modernMedVector.push_back(info);
			}
			break;
		case DIFF::hard:
			if (Score > modernHardVector[4].score){
				playerRecord info = getInformation();
				modernHardVector.erase(modernHardVector.begin() + 4);
				modernHardVector.push_back(info);
			}
			break;
		}
		break;
	}
}

void sortRecord(vector<playerRecord>& container){
	int highestScoreIndex = 0;
	for (int i = 1; i <= 4; i++){
		if (container[i].score > container[highestScoreIndex].score){
			string tempName = container[highestScoreIndex].name;
			int tempScore = container[highestScoreIndex].score;
			container[highestScoreIndex].name = container[i].name;
			container[highestScoreIndex].score = container[i].score;
			container[i].name = tempName;
			container[i].score = tempScore;
			highestScoreIndex = i;
		}
	}
}

void sortAllRecords(){
	sortRecord(classicEasyVector);
	sortRecord(classicMedVector);
	sortRecord(classicHardVector);

	sortRecord(modernEasyVector);
	sortRecord(modernMedVector);
	sortRecord(modernEasyVector);
}

void writeDataToFile(vector<playerRecord> container, string filename) {
    ofstream fo(filename, ios::out | ios::trunc);
    if (!fo) {
        cerr << "Unable to open file for writing\n";
        return;
    }

    for (int i = 0; i <= 4; i++) {
        fo << container[i].score << " | " << container[i].name << "\n";
    }

    fo.close();
}

void writeDataToAllFiles(){
	writeDataToFile(classicEasyVector, classicEasyFile);
	writeDataToFile(classicMedVector, classicMedFile);
	writeDataToFile(classicHardVector, classicHardFile);

	writeDataToFile(classicEasyVector, modernEasyFile);
	writeDataToFile(classicMedVector, modernMedFile);
	writeDataToFile(classicHardVector, modernHardFile);
}

