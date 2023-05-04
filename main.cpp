/*
 * main.cpp
 *
 *  Created on: Apr 10, 2023
 *      Author: Sourabh B
 */
#include <iostream>
//#include <fstream>
#include "color.h"
#include "ray.h"
#include "vec3.h"

using namespace std;

color ray_color(const ray& r){
	vec3 unit_direction = unit_vector(r.direction());

	auto t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0,1.0,1.0) + t * color(0.5,0.7,1.0);
}

int main(){

	// Image
	const auto aspect_ratio = 16.0 /9.0;
	const int image_width = 400;
	const int image_height = static_cast<int> (image_width/aspect_ratio); // 225

	// Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;// 1.125
	auto focal_length = 1.0;

	auto origin = point3(0,0,0);
	auto horizontal = vec3(viewport_width,0,0); //(2,0,0)
	auto vertical =   vec3(0,viewport_height,0); // (0,1.125,0)
	auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length); //(0,0,0) - (1,0,0) - (0,0.5625,0) - (0,0,1) = (-1,-0.5625,-1)

	//Render
	cout << "P3\n" << image_width << ' ' << image_height << "\n255\n"; // This line is added to comply PPM file header format


	for(int j = image_height-1;j>=0;--j){
		cerr << "\rScanlines remaining: " << j << ' ' << flush;

		for(int i = 0;i<image_width; ++i){
			/*
			auto r = double(i)/(image_width-1);
			auto g = double(j)/(image_height-1);
			auto b = 0.25;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);
			*/
			auto u = double(i) /(image_width - 1);
			auto v = double(j) /(image_height - 1);

			ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);

			//color pixel_color(double(i)/(image_width-1),double(j)/(image_height-1),0.25);
			color pixel_color = ray_color(r);
			write_color(cout,pixel_color);

			// std::cout << ir << ' ' << ig << ' ' << ib << '\n';

		}
			//std::cout << '\n';
	}
	cerr << "\nDone.\n";
}



