
#include "raylib.h"

namespace bufferNamespace {
	
	class ImageDisplayBuffer {
		public:
			Texture2D activeTexture;
			Image buffer1;
			Image buffer2;
			int bufferState;
			bool finished;

			ImageDisplayBuffer();
			~ImageDisplayBuffer();

			void toDefault();

			void SetImage(Image* ref);
			void SetPixel(int x, int y, Color* color);
			void SetActive(Image* image);
			void SetInactive(Image* image);
			Image* GetActive();
			Image* GetInactive();
			
			void Flip();
			void SetState(bool finished);
	};

	ImageDisplayBuffer::ImageDisplayBuffer() { this->toDefault(); }
	ImageDisplayBuffer::~ImageDisplayBuffer() { }

	void ImageDisplayBuffer::toDefault() {
		// Image* p = NULL;
		// Texture2D* t = NULL;
		// this->buffer1 = *p;
		// this->buffer2 = *p;
		// this->activeTexture = *t;
		this->bufferState = 1;
	};

	void ImageDisplayBuffer::SetPixel(int x, int y, Color* color) {
		ImageDrawPixel(this->GetInactive(), x, y, *color);
	};

	void ImageDisplayBuffer::SetActive(Image* image) { 
		this->bufferState == 1 ? this->buffer1 = *image : this->buffer2 = *image;
	};

	void ImageDisplayBuffer::SetInactive(Image* image) { 
		this->bufferState == 2 ? this->buffer1 = *image : this->buffer2 = *image;
	};

	Image* ImageDisplayBuffer::GetActive() { 
		return (this->bufferState == 1) ? &this->buffer1 : &this->buffer2;
	};

	Image* ImageDisplayBuffer::GetInactive() { 
		return (this->bufferState == 2) ? &this->buffer1 : &this->buffer2;
	};

	void ImageDisplayBuffer::Flip() {
		this->bufferState = (this->bufferState == 1) ? 2 : 1;
		this->finished = false;

		Texture2D textured = LoadTextureFromImage( *new Image(*this->GetActive()) );
		this->activeTexture = textured;
	};

	void ImageDisplayBuffer::SetState(bool finished) {
		this->finished = finished;
	};
}
