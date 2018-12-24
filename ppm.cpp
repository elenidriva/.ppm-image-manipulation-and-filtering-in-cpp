#include <iostream>
#include <fstream>
#include "ppm.h"

#include <iomanip>
#include <string>

using namespace std;
// Implementing ppm.h functions.
namespace imaging
{
	// Similar to the Streams that were done in Lab03.
	float * ReadPPM(const char * filename, int * w, int * h) {
		ifstream iFile(filename, ios::binary);
		int headerSize = 0;
		int position = 0;
		int dataSize;
		int fileSize;
		if (iFile.is_open()) {
			/*
			fileSize = iFile.tellg(); // This is done to retrieve the size of the file
			unsigned char *datachar = new unsigned char[fileSize]; // For the size retrieved we read the stream and store it to datachar
			iFile.seekg(0, ios::beg);
			iFile.read((char*)datachar, fileSize); // extract #fileSize chars, pointer to array
			iFile.seekg(0, ios::beg); // We return back to the beginning of the file.
			*/
			// We will start by getting the first line.
			string line;
			string p6format;
			//int colour;
			int space = 0;
			int part = 1;
			getline(iFile, line);
			bool valid = true;
			// We need check if there are all 4 'parts' in the header of the file (and if they are correct)
			while ((valid) && (line.length() >= 1) && (part <= 4)) {
				space = line.find_first_of(' ');
				if (space != -1) {						// The substring until the first space is the format type we are searching for.
					p6format = line.substr(0, space); // If there is a space then we tokenize the first line.
					line = line.substr(space + 1);
					// Rest of the line.
					position = p6format.capacity();

				}
				else {									// No space found, thus the first line only contains the format type.
					p6format = line;
					getline(iFile, line);
				}

				switch (part) {
				case 1:                             // P6 Part
					if (p6format == "P6") {
						//cout << "Valid header!!: " << p6format << endl;
					}
					else {
						valid = false;
						cout << "Invalid header...: " << p6format << "Only P6 is supported" << endl;
					}
					break;
				case 2:                            // Width
					*w = stoi(p6format);
					//cout << "Width...: " << *w << endl;
					break;
				case 3:							   // Height
					if (p6format.length() <= 4) {
						*h = stoi(p6format);
						//cout << "Height...: " << *h << endl;
						// At this stage we store the size of the header by using tellg();
						headerSize = iFile.tellg();
					}
					else {
						cout << "Width and Height are missing.";
						valid = false;
					}
					break;
				case 4:
					if (p6format == "255") {
						//colour = stoi(p6format);
						// cout << "Colour..: " << colour;
					}
					else if (p6format != "255" && p6format.length() <= 4) {
						cout << "Only max colour value of 255 is supported for now";
						cout << p6format;
						valid = false;
					}
					else {
						cout << "Width or height is missing.";
						valid = false; // not needed probs
					}
					break;
				}
				part++;
			}
			if (valid) {

				int dataSize = *w * *h * 3;
				//We find where the header of the .ppm ends and we set our iterator there
				if (headerSize > 20) {
					iFile.seekg(position - 1);
				}
				else {
					iFile.seekg(headerSize + (char)1);
				}

				unsigned char *datachar = new unsigned char[dataSize];
				iFile.read((char *)datachar, dataSize);
				float * datafloat = new float[dataSize];

				for (int i = 0; i < dataSize; i++) {
					datafloat[i] = ((float)(unsigned char)datachar[i]) / 255.f;
				}
				iFile.close();
				delete[]datachar;
				return datafloat;
			}
			else {
				cout << "Returning nullptr";
				return nullptr;
			}
		}
		else {
			cout << "Error opening the file..";
			return nullptr;
		}
	}

	bool WritePPM(const float * data, int w, int h, const char * filename) {
		//Returns false immediately as asked.
		if (data == nullptr) {
			return false;
		}
		//Creating output stream.
		ofstream oFile(filename, ios_base::binary);
		if (oFile.fail()) {
			cerr << "Failure opening file.\n";
			return false;
		}
		// Writing the header of the file.
		oFile << "P6" << ' ' << w << ' ' << h << ' ' << "255\n";
		// Transfering data from src.buffer to the new one
		int fileSize = 3 * w * h;
		char *datachar = new char[fileSize];
		for (int i = 0; i < fileSize; i++) {
			datachar[i] = (data[i] * 255.0f);
		}
		oFile.write((char *)datachar, fileSize);
		oFile.close();
		delete[] datachar;

		return true;
	}
}