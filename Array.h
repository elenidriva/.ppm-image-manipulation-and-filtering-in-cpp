#include <iostream>
#include "Vec3.h"
#include <vector>
#ifndef _ARRAY_
#define _ARRAY_
using namespace std;
namespace math {

	template <typename T>
	class Array {						//declaration
	protected:
		T * buffer;						// Change T *buffer to std::vector <T> buffer;
		unsigned int width, height;

	public:
		unsigned int getWidth() const { return width; }
		const unsigned int getHeight() const { return height; }
		// Change the elements using the component "Pixel" into something more abstract.
		T * getRawDataPtr();
		T getPixel(unsigned int x, unsigned int y) const;
		void setPixel(unsigned int x, unsigned int y, T & value);
		void setData(const T * & data_ptr);

		// Constructors and Deconstructor 
		Array();
		Array(unsigned int width, unsigned int height);
		Array(unsigned int width, unsigned int height, const T * data_ptr);
		Array(const Array<T> &src);
		 ~Array(); //virtual? ** Be careful of double deletion **

		Array & operator = (const Array<T> & right);

		// New operator () returns a reference to T of the line y and column x (where x=i, y=j)
		T & operator () (int x, int y);        // Or Const?
		const T & operator() (int x, int y) const;          
	};


	/* ********************************************* *
	 *      Implementation of the generic class.     *
	 * ********************************************* */

	template <typename T> T * Array<T>::getRawDataPtr() {
		return buffer;
	}

	template <typename T>
	T Array<T>::getPixel(unsigned int x, unsigned int y) const { // Vec3<float> stin Image
		T pixelColour; // Returns pixel as Color Obj.
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
	template<typename T>
	void Array<T>::setPixel(unsigned int x, unsigned int y, T & value) {
		if (x < 0 || y < 0 || x > getHeight() || y > getWidth()) return;

		buffer[unsigned int(getWidth() * x + y)].r = value.r; // 15.12: Ligo periergo to "getHeight() * y + x" Chnage to: "getWidth() * x + y" giati mporei na flipparei to image meta.
		buffer[unsigned int(getWidth() * x + y)].g = value.g;
		buffer[unsigned int(getWidth() * x + y)].b = value.b;
		return;
	}

	template<typename T>
	void Array<T>::setData(const T * & data_ptr) {
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

	template<typename T>
	Array<T>::Array() {
		this->buffer = nullptr;
	}

	template <typename T> Array<T>::Array(unsigned int w, unsigned int h) {
		this->width = width;
		this->height = height;
	}

	template<typename T>
	Array<T>::Array(unsigned int width, unsigned int height, const T * data_ptr)
	{
		this->width = width;
		this->height = height;
		int bufferSize = width * height * 3;
		this->buffer = new T[bufferSize];
		for (unsigned int i = 0; i < bufferSize; i++) {
			this->buffer[i] = data_ptr[i];
		}
	}


	template <typename T> Array<T>::Array(const Array<T> & source) {
		this->height = src.getHeight();
		this->width = src.getWidth();
		int bufferSize = width * height;										 // 15.12: Esvisa to *3, pleonasmos
		buffer = getRawDataPtr(); // Edw ena lathos
								  // Copies #bufferSize bytes from src.buffer to destination buffer
		memcpy(buffer, src.buffer, bufferSize);
	}


	template <typename T> Array<T>::~Array() {
		delete[] buffer;
	}

	template <typename T>
	Array<T> & Array<T>::operator = (const Array<T> & right) {
		if (buffer != nullptr) {
			delete[] buffer;
		}
		if (this != &right) {
			delete[] buffer;
		}
		width = right.width;
		height = right.height;
		int bufferSize = width * height * 3;
		buffer = new T[bufferSize];
		//creates the data pointer given src.buffer and adds data
		const T * data_ptr = right.buffer;
		setData(data_ptr);

		return *this;
	}

	template <typename T> T & Array<T>::operator () (int x, int y) {
		return buffer[x*y];
	}

	template <typename T> const T & Array<T>::operator () (int x, int y) const {
		return buffer[x*y];
	}

}
#endif


/*
template <typename T> bool Array<T>::operator == (const Array<T> & source) const {
if (getWidth() * getHeight() != source->getWidth() * source->getHeight()) {
return false;
}
else {
for (int i = 0; i < getWidth() * getHeight(); i++) {
if (buffer[i] != source->getRawDataPtr()[i]) {
return false;
}
}
}
return true;
}

*/