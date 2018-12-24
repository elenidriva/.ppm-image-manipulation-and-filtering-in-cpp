#include "Image.h"
#include "ppm.h"
#include <iostream>
#include <algorithm>
#include "Array.h"
#include "Vec3.h"
#include <string> 

using namespace std;
using namespace imaging;
using namespace math;

namespace imaging {
	//const unsigned int Image::getWidth() const {};
	//const unsigned int Image::getHeight() const {};
	// data accessors

	/*! Obtains a pointer to the internal data.
	*
	*  This is NOT a copy of the internal image data, but rather a pointer
	*  to the internally allocated space, so DO NOT attempt to delete the pointer.
	*/


	Vec3<float> * Image::getRawDataPtr() {
		// 15.12: Lathos entelws... Tha to xreiastw new project
		Vec3<float> * buffer = new Vec3<float>[getWidth() * getHeight() * sizeof(Vec3<float>)];
		
		return buffer;
	
	}
	Vec3<float> Image::getPixel(unsigned int x, unsigned int y) const {   // Obtains the color of the image at location (x,y).
		Vec3<float> pixelColour; // Returns pixel as Color Obj.
						   // Set to (0,0,0) and return if out of bounds
		if (x < 0 || y < 0 || x > getHeight() || y > getWidth()) {
			pixelColour.r = 0;
			pixelColour.g = 0;
			pixelColour.b = 0;

			return pixelColour;
		}
		else {		// Set to (0,0,0) and return if out of bounds
			pixelColour.r = buffer[unsigned int(getWidth() * x + y)].r;
			pixelColour.g = buffer[unsigned int(getWidth() * x + y)].g;
			pixelColour.b = buffer[unsigned int(getWidth() * x + y)].b;
			return pixelColour;
		}
	}


	void Image::setPixel(unsigned int x, unsigned int y, Vec3<float> & value) {
		if (x < 0 || y < 0 || x > getHeight() || y > getWidth()) return;

		buffer[unsigned int(getWidth() * x + y)].r = value.r; // 15.12: Ligo periergo to "getHeight() * y + x" Chnage to: "getWidth() * x + y" giati mporei na flipparei to image meta.
		buffer[unsigned int(getWidth() * x + y)].g = value.g;
		buffer[unsigned int(getWidth() * x + y)].b = value.b;
		return;
	}

	// Copy from external buffer to the internal buffer.
	void Image::setData(const Vec3<float> * & data_ptr) {
		unsigned int fileSize = getWidth() * getHeight();
		if (getRawDataPtr() == nullptr || width == 0 || height == 0 || buffer == NULL) {
			//cout << "Either buffer, width or height are zero.. Exiting program. \n";
			return;
		}
		else {
			for (unsigned int i = 0; i < fileSize; i++) {
				buffer[i] = data_ptr[i];
				// +3 offset?
			}
			return;
		}
	}

	Image::Image() : Array (0,0){							 // Default Constructor
		this->buffer = nullptr;
	}

	Image::Image(unsigned int width, unsigned int height) {			// Constructor with Coordinates specification
		this->width = width;
		this->height = height;
	}

	Image::Image(unsigned int width, unsigned int height, const Vec3<float> * data_ptr){ // >> + data initialization
		this->width = width;
		this->height = height;
		int bufferSize = width * height * 3;
		this->buffer = new Vec3<float>[bufferSize];
		for (unsigned int i = 0; i < bufferSize; i++) {
			this->buffer[i] = data_ptr[i];
		}
	}

	// src img to replicate
	Image::Image(const Image &src) : Array(src.width, src.height) {
		this->height = src.getHeight();
		this->width = src.getWidth();
		int bufferSize = width * height;										 // 15.12: Esvisa to *3, pleonasmos
		buffer = getRawDataPtr(); // Edw ena lathos
		// Copies #bufferSize bytes from src.buffer to destination buffer
		memcpy(buffer, src.buffer, bufferSize);
	}

	//Decon PETAEI ERROR IF IMPLEMENTED HERE. DECONSTRUCTOR IS CALLED TWICE 1. for IMAGE 2. for ARRAY
	Image::~Image() {
		
	}

	Image & Image:: operator = (const Image & right) { // right is the src image    //15.12: SELF ASSIGNMENT
		if (buffer != nullptr) {
			delete[] buffer;
		}
		if (this != &right) {
			delete[] buffer;
		}
		width = right.width;
		height = right.height;
		int bufferSize = width * height * 3;
		buffer = new Vec3<float>[bufferSize];
		//creates the data pointer given src.buffer and adds data
		memcpy(buffer, right.buffer, bufferSize);

		return *this;
	}

	bool Image::load(const std::string & filename, const std::string & format) {

		// We start by searching if the user added valid arguments/input in the application
		// We tokenize the input to see if the image has the appropriate extension ".ppm"
		string extension = filename.substr(filename.find_first_of(".") + 1);
		transform(extension.begin(), extension.end(), extension.begin(), tolower);
		if ((filename.find_first_of(".") == -1) || (extension.compare(format) != 0)) {
			return false;
		}
		else {
			int loadWidth;
			int loadHeight;
			float * floatdata = ReadPPM(filename.c_str(), &loadWidth, &loadHeight); // ReadPPM accepts char *
			width = loadWidth;									// used in Class Image
			height = loadHeight;
			int dataSize = loadWidth * loadHeight * 3;
			buffer = new Vec3<float>[dataSize];							//new buffer width* height* sizeof(Color)
			int offset = 0;
			for (int i = 0; offset < dataSize; i++) {
				buffer[i].g = floatdata[offset];
				buffer[i].b = floatdata[offset + 1];
				buffer[i].r = floatdata[offset + 2];
				offset += 3;
			}
			delete[] floatdata;
			return true;
		}
	}

	bool Image::save(const std::string & filename, const std::string & format) {
		bool save = true;
		string extension = filename.substr(filename.find_first_of(".") + 1);
		transform(extension.begin(), extension.end(), extension.begin(), tolower);
		if ((filename.find_first_of(".") == -1) || (extension.compare(format) != 0)) {
			return false; // returns immediately as asked
		}

		// If Image Object is not initialized.
		if (buffer == 0) {
			cerr << "Uninitialized Image Object." << endl;
			return false;
		}
		int dataSize = width * height * 3;
		float * datafloat = new float[dataSize];
		int bufferSize = width * height * sizeof(Color);
		// Opposite of load
		int offset = 0;
		for (int i = 0; offset < dataSize && i < bufferSize; i++) {
			datafloat[offset] = buffer[i].r;
			datafloat[offset + 1] = buffer[i].g;
			datafloat[offset + 2] = buffer[i].b;
			offset += 3;
		}
		cout << getRawDataPtr();
		int saveWidth = width, saveHeight = height;
		save = WritePPM(datafloat, saveWidth, saveHeight, filename.c_str());
		delete[] datafloat;
		return save;
	}
}
