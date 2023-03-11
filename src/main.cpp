
#include <iostream>
#include "include/mathlib.h"
#include "include/stringlib.h"

int main() {
	mathlib::Vector2f v1 = mathlib::Vector2f(5.0f, 3.0f);
	mathlib::Vector2f v2 = mathlib::Vector2f(3.0f, 5.0f);

	mathlib::Vector2f vf = v2.add(&v1);

	std::cout << vf.magnitude() << std::endl;
	std::cout << vf.toString() << std::endl;

	mathlib::Vector3f origin = mathlib::Vector3f();
	mathlib::Vector3f goal = mathlib::Vector3f(2, 2, 2);

	mathlib::CFrame cf = mathlib::CFrame( &origin, &goal );
	mathlib::Vector3f offset = cf.LookVector.mult(5);

	mathlib::CFrame ncf = cf.add( &offset );

	std::cout << origin.toString() << std::endl;
	std::cout << goal.toString() << std::endl;
	std::cout << ncf.Position.toString() << std::endl;

	return 0;
}
