
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include "include/raylib.h"
#include "include/mathlib.h"
#include "include/stringlib.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Particle  {
	public:
		float x, y;
		float dx, dy;
		float speed;
		float radius;

		Particle();
		~Particle();
		void toDefault();
		void randomize();
		void step(float delta);
		void wrap_bounds();
		std::string* toString();
};

Particle::Particle() {
	this->toDefault();
}

Particle::~Particle() {

}

void Particle::toDefault() {
	this->x = (float) SCREEN_WIDTH / 2;
	this->y = (float) SCREEN_HEIGHT / 2;
	this->dx = 0;
	this->dy = 0;
	this->speed = 0;
	this->radius = 3;
};

void Particle::randomize() {
	this->x = mathlib::randomInt(50, SCREEN_WIDTH - 50);
	this->y = mathlib::randomInt(50, SCREEN_HEIGHT - 50);
	mathlib::Vector2f* dir = new mathlib::Vector2f(mathlib::randomInt(0, 300) - 150, mathlib::randomInt(0, 300) - 150);
	dir = dir->unit();
	this->dx = mathlib::randomInt(0, 300) - 150;
	this->dy = mathlib::randomInt(0, 300) - 150;
	this->speed = 20 + (rand() % 50);
	this->radius = 2 + rand() % 3;
};

void Particle::step(float delta) {
	float nextX = this->x + (this->dx * delta);
	float nextY = this->y + (this->dy * delta);
	this->x = nextX;
	this->y = nextY;
};

void Particle::wrap_bounds() {
	if (this->x > SCREEN_WIDTH) {
		this->x -= SCREEN_WIDTH;
	} else if (this->x < 0) {
		this->x += SCREEN_WIDTH;
	}
	if (this->y > SCREEN_HEIGHT) {
		this->y -= SCREEN_HEIGHT;
	} else if (this->y < 0) {
		this->y += SCREEN_HEIGHT;
	}
};

std::string* Particle::toString() {
	return string_format("Particle(%d, %d, %f, %f, %f, %f)", this->x, this->y, this->dx, this->dy, this->speed, this->radius);
};

void run_app() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Simulation");
	SetTargetFPS(60);

	// vector of pointers to Particle objects
	std::vector<Particle*> particles = std::vector<Particle*>(50);

	for (unsigned int index = 0; index < particles.size(); index++) {
		// update the randomizer seed
		std::srand( index );
		// create a new particle object and store the pointer
		Particle* particle = new Particle();
		// randomize the particle
		particle->randomize();
		// store the particle in the particle array
		particles[index] = particle;
	}

	// for each active particle
	for (unsigned int index = 0; index < particles.size(); index++) {
		// get the particle pointer
		Particle* p = particles[index];
		// output the toString of it
		std::cout << *p->toString() << std::endl;
	}

	std::clock_t last_lock = std::clock();
	while (!WindowShouldClose()) {
		std::clock_t new_clock = std::clock();
		
		// update particles
		float delta = (new_clock - last_lock) * 1e-3;
		for (unsigned int index = 0; index < particles.size(); index++) {
			// get the pointer
			Particle* p = particles[index];
			// step the particle physics
			p->step(delta);
			// wrap the particle around scene bounds
			p->wrap_bounds();
		}

		last_lock = new_clock;

		BeginDrawing();
			ClearBackground(BLACK);

			// display particles
			for (unsigned int index = 0; index < particles.size(); index++) {
				// get the particle pointer
				Particle* p = particles[index];
				// draw the particle
				DrawCircle( p->x, p->y, p->radius, WHITE );
			}

		EndDrawing();
	}
	CloseWindow();
}

int main() {
	run_app();
	return 0;
}
