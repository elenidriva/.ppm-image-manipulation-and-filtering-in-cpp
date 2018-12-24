#include "Image.h"

#ifndef _FILTER_
#define _FILTER_

namespace imaging {
	class Filter {

	public:
		// Declaring the pure virtual method, the default constructors(default, copy) and decon ? mallon de thelei
		virtual Image operator << (const Image & image)=0; // NEEDS to be implemented by derived class if not declared as abstract
		//Filter();
	//	Filter(const Filter &src);
		virtual ~Filter();





	};


	//Filter::Filter() {}
	//Filter::Filter(const Filter &src) {}
	Filter::~Filter() {}
	








}

#endif