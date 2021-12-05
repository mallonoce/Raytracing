#ifndef _RAY_H_
#define _RAY_H_

#include <iostream>
#include <filesystem>

#include <Eigen/Dense>

using Vec3f = Eigen::Vector3f;

class Ray 
{
public:
	Ray() {};
	Ray(const Vec3f& origin, const Vec3f& direction) : _origin(origin), _direction(direction) {};
	Vec3f origin() const { return _origin; }
	Vec3f direction() const { return _direction; }
	Vec3f point_at_param(const float& t) { return _origin + t * _direction; }
private:
	Vec3f _origin;
	Vec3f _direction;

};

#endif // _RAY_H_