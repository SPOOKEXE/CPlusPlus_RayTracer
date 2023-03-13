
#include <iostream>
#include <vector>
#include "include/raylib.h"
#include "include/mathlib.h"
#include "include/stringlib.h"
#include "include/image_buffer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

void run_app() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Simulation");
	SetTargetFPS(60);

	bufferNamespace::ImageDisplayBuffer* imgDisplayBuffer = new bufferNamespace::ImageDisplayBuffer();

	Image blank1 = GenImageWhiteNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 0.5);
	imgDisplayBuffer->buffer1 = blank1;
	Image blank2 = GenImageCellular(SCREEN_WIDTH, SCREEN_HEIGHT, 2);
	imgDisplayBuffer->buffer2 = blank2;

	imgDisplayBuffer->Flip(); // force flip to load texture for below

	std::clock_t last_lock = std::clock();
	while (!WindowShouldClose()) {
		std::clock_t new_clock = std::clock();
		float delta = (new_clock - last_lock) * 1e-3;
		if (delta > 1) {
			std::cout << "flip - " << imgDisplayBuffer->bufferState << std::endl;
			imgDisplayBuffer->Flip();
			last_lock = new_clock;;
		}
		
		// check update status (if not updating, start updating)
		BeginDrawing();
			ClearBackground(BLACK);
			DrawTexture(imgDisplayBuffer->activeTexture, 0, 0, WHITE);
			// display active buffer image
		EndDrawing();
	}
	CloseWindow();

	delete(imgDisplayBuffer);

}

int main() {
	run_app();
	return 0;
}
