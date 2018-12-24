#include "ppm.h"
#include "Array.h"
#include "Image.h"
#include "Filter.h"
#include "FilterGamma.h"
#include "FilterLinear.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <ppm.h>
using namespace imaging;
using namespace std;

int main(int argc,      // Number of strings in array argv
	char *argv[])   // Array of command-line argument string 
{
	bool valid = true;
	string filename;
	string filt = "filter";
	string identifier = "-f";
	vector<string> filters;
	float gamma, a1, a2, a3, c1, c2, c3;

	for (unsigned int i = 1; i < argc; i++) {
		filters.push_back(argv[i]);
	}

	if (argc > 1) {
		filename = argv[argc - 1];
		cout << "Filename:  " << filename << endl;
		
	}
	else  {
		cout << "You have not entered any arguments. \n";
		cout << "Please enter here the filters and the filename you want to edit.\n"<< "For instance:'filter -f gamma 0.5 Image06.ppm' \n";
		cin >> filename;
		
	}

	
	Image img;
	Vec3<float> buffer;
	Vec3<float> pixel;
	//unsigned int width, height;
	if (img.load(filename, "ppm")) {

		cout << "Image dimensions are: " << img.getWidth() << " x " << img.getHeight() << endl;

		/* 1st Assignment -- Negative Image
		//const Color c(1, 1, 1);
		for (int i = 0; i <img.getHeight(); i++) {
			for (int y = 0; y < img.getWidth(); y++) {
				Vec3<float> pixel = img.getPixel(i, y);
				pixel[0] = 1.0f - pixel[0];
				pixel[1] = 1.0f - pixel[1];
				pixel[2] = 1.0f - pixel[2];

				// pixel = (pixel[0].r + pixel[1].g + pixel[2].b )/3;
				img.setPixel(i, y, pixel);
			}
		}
		*/
		string filter;

		valid = false;
		if (filters[0].compare("filter") == 0) {
			valid = true;
		} else {
			valid = false;
		}
		int y = 0;
		for (unsigned int i = 1; i < filters.size(); i++) {
			cout << filters[i];

				if (filters[i].compare("-f") == 0) {
					if (filters[i + 1].compare("gamma") == 0) {

							gamma = stof(filters[i + 2]);
							FilterGamma filter(img, filename, gamma, pixel);
							filter << img;
							cout << "Gamma filter applied.";
							i += 2;
							//Image *image = img;
							img.load("filtered_" + filename, "ppm");
							
					}
					else if (filters[i + 1].compare("linear") == 0) {							
						a1 = stof(filters[i + 2]);
						a2 = stof(filters[i + 3]);
						a3 = stof(filters[i + 4]);
						c1 = stof(filters[i + 5]);
						c2 = stof(filters[i + 6]);
						c3 = stof(filters[i + 7]);
						FilterLinear filter(img, filename, a1, a2, a3, c1, c2, c3, pixel);
						filter << img;
						cout << "Linear filter applied.";
						i += 7;
						img.load("filtered_" + filename, "ppm");
					}

				}
				else {
					valid = false;
					break;
				}

		}

		
		//cout << img;
		/*	for (int i = 0; i < img.getHeight(); i++) {
		Color pixel = img.getPixel(i, img.getWidth());
		pixel[0] = (0, 0, 0) - pixel[0];
		pixel[1] = (1, 1, 1) - pixel[1];
		pixel[2] = (1, 1, 1) - pixel[2];
		img.setPixel(i, img.getWidth(), pixel);
		}*/



		system("pause");
	}
	else {
		cout << "\nAn error has occured. The application supports only .ppm image filtering.\n";
		system("pause");
	}
}