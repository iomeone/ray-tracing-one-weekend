#pragma once

#include <stdlib.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

//Color is called recursively!
//drowan 20190127: replaced with version that uses std::shared_ptr
//vec3 color(const ray &rayCast, Hitable *world, int depth) {	
//	//provide a way to store the hit vector to act on it outside the hit check
//	HitRecord hitRecord;
//
//	//hits a point on the sphere or hittable.
//	if (world->hit(rayCast, 0.001, std::numeric_limits<float>::max(), hitRecord)) {
//		ray scattered;
//		vec3 attenuation;
//
//		//depth refers to number of recursive calls to bounce the ray around???
//		if (depth < 50 && hitRecord.materialPointer->scatter(rayCast, hitRecord, attenuation, scattered)) {
//			return attenuation * color(scattered, world, depth + 1);
//		}
//		else {
//			//what does it mean when this returns?
//			return vec3(0, 0, 0);
//		}
//	}
//	//does not hit anything, so "background" gradient
//	else {
//		vec3 unit_direction = unit_vector(rayCast.direction());
//
//		float tempPointAtParameterT = 0.5*(unit_direction.y() + 1.0);
//
//		return (1.0 - tempPointAtParameterT)*vec3(1.0, 1.0, 1.0) + tempPointAtParameterT * vec3(0.5, 0.7, 1.0);
//	}
//}

vec3 color(const ray &rayCast, std::shared_ptr<Hitable> &worldHitableList, int depth) {
	//provide a way to store the hit vector to act on it outside the hit check
	HitRecord hitRecord;

	//hits a point on the sphere or hittable.
	if (worldHitableList->hit(rayCast, 0.001, std::numeric_limits<float>::max(), hitRecord)) {
		ray scattered;
		vec3 attenuation;

		//depth refers to number of recursive calls to bounce the ray around???
		if (depth < 50 && hitRecord.materialPointer->scatter(rayCast, hitRecord, attenuation, scattered)) {
			return attenuation * color(scattered, worldHitableList, depth + 1);
		}
		else {
			//what does it mean when this returns?
			return vec3(0, 0, 0);
		}
	}
	//does not hit anything, so "background" gradient
	else {
		vec3 unit_direction = unit_vector(rayCast.direction());

		float tempPointAtParameterT = 0.5*(unit_direction.y() + 1.0);

		return (1.0 - tempPointAtParameterT)*vec3(1.0, 1.0, 1.0) + tempPointAtParameterT * vec3(0.5, 0.7, 1.0);
	}
}