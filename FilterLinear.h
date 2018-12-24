#include "Filter.h"
#include "Image.h"
#include <math.h>  
using namespace imaging;
using namespace math;
namespace imaging {
	class FilterLinear : public Filter // class Image: public math::Array::Vec3<float>
	{
	private:
		float a1,a2,a3, c1, c2, c3;
		Image image;
		string filename;
		Vec3<float> pixel;
	public:

		Image operator << (const Image & image) {
			Image img = image;
			
			if (a1 >= 1.0) a1 = 1.0;
			if (a2 >= 1.0) a2 = 1.0;
			if (a3 >= 1.0) a3 = 1.0;
			if (c1 >= 1.0) c1 = 1.0;
			if (c2 >= 1.0) c2 = 1.0;
			if (c3 >= 1.0) c3 = 1.0;

			for (int i = 0; i <image.getHeight(); i++) {
				for (int y = 0; y < image.getWidth(); y++) {
					Vec3<float> pixel = image.getPixel(i, y);
					pixel[0] = (pixel[0] * a1) + c1;
					pixel[1] = (pixel[1] * a2) + c2;
					pixel[2] = (pixel[2] * a3) + c3;
					//pixel = (pixel[0].r + pixel[1].g + pixel[2].b )/3;
					if (pixel[0] > 1.0) pixel[0] = 1.0f;
					if (pixel[1] > 1.0) pixel[1] = 1.0f;
					if (pixel[2] > 1.0) pixel[2] = 1.0f;

					//pixel[0] = pixel[.clampToUpperBound(1.0);
					img.setPixel(i, y, pixel);
				}

			}


			string newimage = "filtered_" + filename;
			if (img.save(newimage, "ppm")) {

				cout << "Check the working directory for the new image. \n";
			}

			return img;

		}

		FilterLinear();

		FilterLinear(Image &image, string filename, float a1, float a2, float a3, float c1, float c2, float c3, Vec3<float> pixel);

	};


	/*
	for (int i = 0; i < image.getHeight(); i++) {
	for (int y = 0; y < image.getWidth(); y++) {
	Vec3<float> pixel = image.getPixel(i, y);
	pixel[0] = 1.0f - pixel[0];
	pixel[1] = 1.0f - pixel[1];
	pixel[2] = 1.0f - pixel[2];



	// pixel = (pixel[0].r + pixel[1].g + pixel[2].b )/3;
	image.setPixel(i, y, pixel);
	}
	}
	*/



	FilterLinear::FilterLinear() {							 // Default Constructor
	}



	FilterLinear::FilterLinear(Image &image, string filename, float a1, float a2, float a3, float c1, float c2, float c3, Vec3<float> pixel) {
		this->a1 = a1;
		this->a2 = a2;
		this->a3 = a3;
		this->c1 = c1;
		this->c2 = c2;
		this->c3 = c3;
		this->image = image;
		this->filename = filename;
		this->pixel = pixel;

	}












}