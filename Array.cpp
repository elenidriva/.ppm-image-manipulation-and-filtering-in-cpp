using namespace std;
using namespace math;
namespace math {

	template <typename T>
	class Array {
	protected:
		Vec3<T> * buffer; // Change T *buffer to std::vector <T> buffer;
		unsigned int width, height;

	public:
		unsigned int getWidth() const { return width; }
		const unsigned int getHeight() const { return height; }
		<T> getPixel(unsigned int x, unsigned int y) const;
		void setPixel(unsigned int x, unsigned int y, <T> & value);
		void setData(const <T> * & data_ptr);
		Array<T>();
		Array<T>(unsigned int width, unsigned int height);
		Array<T>(unsigned int width, unsigned int height, const <T> * data_ptr);
		Array<T>(const Array<T> &src);
		~Array<T>();
		Array<T> & operator = (const Array<T> & right);




		<T> getPixel(unsigned int x, unsigned int y) const {   // Obtains the color of the image at location (x,y).
			<T> pixelColour; // Returns pixel as Color Obj.
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

		void setPixel(unsigned int x, unsigned int y, <T> & value) {
			if (x < 0 || y < 0 || x > getHeight() || y > getWidth()) return;

			buffer[unsigned int(getWidth() * x + y)].r = value.r; // 15.12: Ligo periergo to "getHeight() * y + x" Chnage to: "getWidth() * x + y" giati mporei na flipparei to image meta.
			buffer[unsigned int(getWidth() * x + y)].g = value.g;
			buffer[unsigned int(getWidth() * x + y)].b = value.b;
			return;
		}

		void setData(const <T> * & data_ptr) {
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


		Array<T>() :width(0), height(0) {							 // Default Constructor
			this->buffer = nullptr;
		}

		Array<T>(unsigned int width, unsigned int height) {			// Constructor with Coordinates specification
			this->width = width;
			this->height = height;
		}

		Array<T>(unsigned int width, unsigned int height, const <T> * data_ptr) { // >> + data initialization
			this->width = width;
			this->height = height;
			int bufferSize = width * height * 3;
			this->buffer = new Color[bufferSize];
			for (unsigned int i = 0; i < bufferSize; i++) {
				this->buffer[i] = data_ptr[i];
			}
		}

		// src img to replicate
		Array<T>(const Array<T> &src) {
			this->height = src.getHeight();
			this->width = src.getWidth();
			int bufferSize = width * height;										 // 15.12: Esvisa to *3, pleonasmos
			buffer = getRawDataPtr(); // Edw ena lathos
									  // Copies #bufferSize bytes from src.buffer to destination buffer
			memcpy(buffer, src.buffer, bufferSize);
		}

		//Decon
		~Array<T>() {
			delete[]buffer;
		}

		Array<T> &  operator = (const Array<T> & right) { // right is the src image    //15.12: SELF ASSIGNMENT
			if (buffer != nullptr) {
				delete[] buffer;
			}
			if (this != &right) {
				delete[] buffer;
			}
			width = right.width;
			height = right.height;
			int bufferSize = width * height * 3;
			buffer = new <T> [bufferSize];
			//creates the data pointer given src.buffer and adds data
			const <T> * data_ptr = right.buffer;
			setData(data_ptr);

			return *this;
		}

	};




