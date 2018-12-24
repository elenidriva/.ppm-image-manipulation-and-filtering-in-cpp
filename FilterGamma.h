#include "Filter.h"
#include "Image.h"
#include <math.h>  
using namespace imaging;
using namespace math;
namespace imaging {
	class FilterGamma : public Filter // class Image: public math::Array::Vec3<float>
	{
	private: 
		float gamma;
		Image image;
		string filename;
		Vec3<float> pixel;
	public: 
		
		 Image operator << (const Image & image) {
			 Image img = image;
			 for (int i = 0; i <image.getHeight(); i++) {
				 for (int y = 0; y < image.getWidth(); y++) {
					 Vec3<float> pixel = image.getPixel(i, y);
					 pixel[0] = pow(pixel[0], gamma);
					 pixel[1] = pow(pixel[1], gamma);
					 pixel[2] = pow(pixel[2], gamma);

					 //pixel = (pixel[0].r + pixel[1].g + pixel[2].b )/3;
					img.setPixel(i, y, pixel);
				 }

			 }


			string newimage = "filtered_"+ filename;
			if (img.save(newimage, "ppm")) {
			
				cout << "Check the working directory for the new image. \n";
			}
			 
			return img;

		}

		FilterGamma();

		FilterGamma(Image &image, string filename, float gamma, Vec3<float> pixel);

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
	


	FilterGamma::FilterGamma() {							 // Default Constructor
	}



	FilterGamma::FilterGamma(Image &image, string filename, float gamma, Vec3<float> pixel) {
		this->gamma = gamma;// Default Constructor
		this->image = image;
		this->filename = filename;
		this->pixel = pixel;

	}











	
}