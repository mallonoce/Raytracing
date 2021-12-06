#ifndef _RAY_H_
#define _RAY_H_

#include "header.h"

class Ray 
{
public:
	Ray() {};
	Ray(const vec3& origin, const vec3& direction) : _origin(origin), _direction(direction.normalized()) {};
	vec3 origin() const { return _origin; }
	vec3 direction() const { return _direction; }
	vec3 point_at_param(const double& t) const { return _origin + t * _direction; }
	vec3 at(const double& t) const { return point_at_param(t); }
private:
	vec3 _origin;
	vec3 _direction;
};

#endif // _RAY_H_