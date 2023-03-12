
#include <iostream>
#include <vector>
#include "include/raylib.h"
#include "include/mathlib.h"
#include "include/stringlib.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

class ImageDisplayBuffer {
	public:
		Texture2D* activeTexture;
		Image* buffer1;
		Image* buffer2;
		int bufferState;

		ImageDisplayBuffer();
		~ImageDisplayBuffer();

		void toDefault();

		void SetPixel(int x, int y, Color* color);
		void SetActive(Image* image);
		void SetInactive(Image* image);
		Image* GetActive();
		Image* GetInactive();
		
		void Flip();
};

ImageDisplayBuffer::ImageDisplayBuffer() { this->toDefault(); }
ImageDisplayBuffer::~ImageDisplayBuffer() { }

void ImageDisplayBuffer::toDefault() {
	Image blank1 = GenImageWhiteNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 0.5);
	Image blank2 = GenImageCellular(SCREEN_WIDTH, SCREEN_HEIGHT, 2);
	Texture2D textured = LoadTextureFromImage(blank1);

	this->buffer1 = &blank1;
	this->buffer2 = &blank2;
	this->activeTexture = new Texture(textured);
	this->bufferState = 1;
}

void ImageDisplayBuffer::SetPixel(int x, int y, Color* color) {
	ImageDrawPixel(this->GetInactive(), x, y, *color);
}

void ImageDisplayBuffer::SetActive(Image* image) { 
	this->bufferState == 1 ? this->buffer1 = image : this->buffer2 = image;
};

void ImageDisplayBuffer::SetInactive(Image* image) { 
	this->bufferState == 2 ? this->buffer1 = image : this->buffer2 = image;
};

Image* ImageDisplayBuffer::GetActive() { 
	return (this->bufferState == 1) ? this->buffer1 : this->buffer2;
};

Image* ImageDisplayBuffer::GetInactive() { 
	return (this->bufferState == 2) ? this->buffer1 : this->buffer2;
};

void ImageDisplayBuffer::Flip() {
	this->bufferState = (this->bufferState == 1) ? 2 : 1;

	// TODO: fix
	// Texture2D textured = LoadTextureFromImage( *new Image(*this->GetActive()) );
	// this->activeTexture = new Texture(textured);
}

void run_app() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Simulation");
	SetTargetFPS(60);

	ImageDisplayBuffer* imgDisplayBuffer = new ImageDisplayBuffer();

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
			DrawTexture(*imgDisplayBuffer->activeTexture, 0, 0, WHITE);
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
