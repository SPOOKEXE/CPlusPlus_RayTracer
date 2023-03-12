
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <thread>
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
	mathlib::Vector2f* unit_dir = dir->unit();
	delete(dir);
	this->dx = unit_dir->x;
	this->dy = unit_dir->y;
	delete(unit_dir);

	this->speed = mathlib::randomInt(5, 25);
	this->radius = mathlib::randomInt(2, 5);
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

void update_particles(std::vector<Particle*>* particles, float delta) {
	for (unsigned int index = 0; index < particles->size(); index++) {	
		// get the pointer
		Particle* p = particles->data()[index];
		// step the particle physics
		p->step(delta);
		// wrap the particle around scene bounds
		p->wrap_bounds();
	}
}

void _update_particle(Particle* particle, float delta) {
	// step the particle physics
	particle->step(delta);
	// wrap the particle around scene bounds
	particle->wrap_bounds();
}

void update_particles_parallel(std::vector<Particle*>* particles, float delta) {
	std::vector<std::thread*>* threads = new std::vector<std::thread*>( particles->size() );

	for (unsigned int i = 0; i < particles->size(); i++) {
		std::thread* thread = new std::thread(_update_particle, particles->data()[i], delta);
		threads->data()[i] = thread;
	}

	for (std::thread* threadd : *threads) {
		threadd->join();
	}
}

void draw_particles(std::vector<Particle*>* particles) {
	for (unsigned int index = 0; index < particles->size(); index++) {
		// get the particle pointer
		Particle* p = particles->data()[index];
		// draw the particle
		DrawCircle( p->x, p->y, p->radius, WHITE );
	}
}

void run_app() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Simulation");
	SetTargetFPS(60);

	// vector of pointers to Particle objects
	std::vector<Particle*>* particles = new std::vector<Particle*>(5000);

	for (unsigned int index = 0; index < particles->size(); index++) {
		// update the randomizer seed
		std::srand( index );
		// create a new particle object and store the pointer
		Particle* particle = new Particle();
		// randomize the particle
		particle->randomize();
		// store the particle in the particle array
		particles->data()[index] = particle;
	}

	// for each active particle
	// for (unsigned int index = 0; index < particles->size(); index++) {
	// 	// get the particle pointer
	// 	Particle* p = particles->data()[index];
	// 	// output the toString of it
	// 	std::cout << *p->toString() << std::endl;
	// }

	std::clock_t last_lock = std::clock();
	while (!WindowShouldClose()) {
		std::clock_t new_clock = std::clock();
		
		float delta = (new_clock - last_lock) * 1e-3;
		// update_particles(particles, delta);
		update_particles_parallel(particles, delta);
		last_lock = new_clock;

		BeginDrawing();
			ClearBackground(BLACK);
			draw_particles(particles);
		EndDrawing();
	}
	CloseWindow();

}

int main() {
	run_app();
	return 0;
}
