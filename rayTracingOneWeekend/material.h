#pragma once

#include "vec3.h"
#include "rngs.h"
#include "mathUtilities.h"

#include "ray.h"
#include "hitable.h"
#include "texture.h"

static vec3 reflect(const vec3 &v, const vec3 &n) {
	return v - 2 * dot(v, n)*n;
}

bool refract(const vec3 &inputRay, const vec3 &normal, float nOverNPrime, vec3 &refracted) {
	vec3 uv = unit_vector(inputRay);
	float dt = dot(uv, normal);
	float discriminant = 1.0 - nOverNPrime * nOverNPrime*(1 - dt * dt);

	if (discriminant > 0) {
		refracted = nOverNPrime * (uv - normal * dt) - normal * sqrt(discriminant);
		return true;
	}
	else
		return false;
}

float schlick(float cosine, float refIndex) {
	float r0 = (1 - refIndex) / (1 + refIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}

class Material {
public:
	virtual bool scatter(const ray &inputRay, const HitRecord &hitRecord, vec3 &attenuation, ray &scatteredRay) const = 0;

	virtual vec3 emitted(float u, float v, const vec3 &p) const {
		return vec3(0, 0, 0);
	}
};

class Lambertian : public Material {
public:
	Lambertian(Texture *a) : albedo(a) {}

	virtual bool scatter(const ray &inputRay, const HitRecord &hitRecord, vec3 &attenuation, ray &scattered) const {						
		////produce a "reflection" ray that originates at the point where a hit was detected and is cast in some random direction away from the impact surface.
		vec3 target = hitRecord.point + hitRecord.normal + randomInUnitSphere();
		scattered = ray(hitRecord.point, target - hitRecord.point, inputRay.time());
		attenuation = albedo->value(hitRecord.u, hitRecord.v, hitRecord.point);
		return true;
	}

	Texture *albedo;
};

class Metal : public Material {
public:
	Metal(const vec3 &a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }

	virtual bool scatter(const ray &inputRay, const HitRecord &hitRecord, vec3 &attenuation, ray &scattered) const {
		vec3 reflected = reflect(unit_vector(inputRay.direction()), hitRecord.normal);
		scattered = ray(hitRecord.point, reflected + fuzz*randomInUnitSphere());
		attenuation = albedo;
		return (dot(scattered.direction(), hitRecord.normal) > 0);
	}

	vec3 albedo;
	float fuzz;
};

class Dielectric : public Material {
public:
	Dielectric(float ri) : refIndex(ri) {}

	virtual bool scatter(const ray &inputRay, const HitRecord &hitRecord, vec3 &attenuation, ray &scattered) const {
		vec3 outwardNormal;
		vec3 reflected = reflect(inputRay.direction(), hitRecord.normal);

		float nOverNPrime;
		
		attenuation = vec3(1.0, 1.0, 1.0);

		vec3 refracted;

		float reflectProbability;
		float cosine;

		if (dot(inputRay.direction(), hitRecord.normal) > 0) {
			outwardNormal = -hitRecord.normal;
			nOverNPrime = refIndex;
			cosine = refIndex * dot(inputRay.direction(), hitRecord.normal) / inputRay.direction().length();
		}
		else {
			outwardNormal = hitRecord.normal;
			nOverNPrime = 1.0 / refIndex;
			cosine = -dot(inputRay.direction(), hitRecord.normal) / inputRay.direction().length();
		}

		if (refract(inputRay.direction(), outwardNormal, nOverNPrime, refracted)) {
			reflectProbability = schlick(cosine, refIndex);
		}
		else {
			scattered = ray(hitRecord.point, reflected);
			reflectProbability = 1.0;
		}

		if (unifRand(randomNumberGenerator) < reflectProbability) {
			scattered = ray(hitRecord.point, reflected);
		}
		else {
			scattered = ray(hitRecord.point, refracted);
		}

		return true;
	}

	float refIndex;
};

class DiffuseLight : public Material {
public:
	DiffuseLight(Texture *a) : emit(a) {}

	virtual bool scatter(const ray &inputRay, const HitRecord &record, vec3 &attenuation, ray &scattered) const { 
		return false; 
	}
	virtual vec3 emitted(float u, float v, const vec3 &p) const { 
		return emit->value(u, v, p); 
	}

	Texture *emit;
};

class Isotropic : public Material {
public:
	Isotropic(Texture *texture) : _albedo(texture) {}

	virtual bool scatter(const ray &inputRay, const HitRecord &hitRecord, vec3 &attenuation, ray &scatteredRay) const {
		scatteredRay = ray(hitRecord.point, randomInUnitSphere());
		attenuation = _albedo->value(hitRecord.u, hitRecord.v, hitRecord.point);
		return true;
	}

	Texture *_albedo;
};

