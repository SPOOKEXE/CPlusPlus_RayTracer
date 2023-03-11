#pragma once

#include <ios>
#include "stringlib.h"

namespace Color {

	class Color3 {
		public:
			float R, G, B;
			Color3();
			Color3(int r, int g, int b);
			Color3(float r, float g, float b);
			~Color3();

			void setDefault();

			float getR();
			float getG();
			float getB();

			Color3 copy();
			std::string toString();

			static Color3 getShade(Color3 color, float shade);
			static Color3 mixAll(Color3 colors[]);
			static Color3 mix(Color3 color);

			static Color3 fromRGB(int R, int G, int B);
			static Color3 fromHSV(int H, int S, int V);
			static Color3 fromHex(int hex_value);
	};

	Color3::Color3() {

	};

	Color3::Color3(int r, int g, int b) {
		this->R = (float) r / 255.0f;
		this->G = (float) g / 255.0f;
		this->B = (float) b / 255.0f;
	};

	Color3::Color3(float r, float g, float b) {
		this->R = r;
		this->G = g;
		this->B = b;
	};

	Color3::~Color3() {

	};

	void Color3::setDefault() {
		this->R = 0;
		this->G = 0;
		this->B = 0;
	}

	float Color3::getR() {
		return this->R;
	};

	float Color3::getG() {
		return this->G;
	};

	float Color3::getB() {
		return this->B;
	};

	Color3 Color3::copy() {
		return Color3(this->R, this->G, this->B);
	};

	std::string Color3::toString() {
		return string_format("Color3(%f, %f, %f)", this->R, this->G, this->B);
	}

	Color3 getShade(Color3 color, float shade) {
		double redLinear = pow(color.getR(), 2.4) * shade;
		double greenLinear = pow(color.getG(), 2.4) * shade;
		double blueLinear = pow(color.getB(), 2.4) * shade;

		float red = pow(redLinear, 1/2.4);
		float green = pow(greenLinear, 1/2.4);
		float blue = pow(blueLinear, 1/2.4);

		return Color3(red, green, blue);
	};

	Color3 mixAll(Color3 colors[]) {
		if ( sizeof(colors) == 0){
			return Color3();
		};

		float concentration = (float) (1.0 / (1.0 + sizeof(colors)));

		float A_r = 1 * concentration;
		float A_g = 1 * concentration;
		float A_b = 1 * concentration;

		for (unsigned int i = 0; i < sizeof(colors); i += 1 ) {
			A_r += colors[i].getR() * concentration;
			A_g += colors[i].getG() * concentration;
			A_b += colors[i].getB() * concentration;
		};

		return Color3(A_r, A_g, A_b);
	};

	Color3 mix(Color3 a, Color3 b) {
		return Color3(
			a.getR() + b.getR() / 2,
			a.getG() + b.getG() / 2,
			a.getB() + b.getB() / 2
		);
	};

	Color3 fromRGB(int R, int G, int B) {
		return Color3(
			(float) R / 255.0f,
			(float) G / 255.0f,
			(float) B / 255.0f
		);
	};

	Color3 fromHSV(int h, int s, int v) {
		double hh, p, q, t, ff;
		long i;
		Color3 out = Color3();

		if(s <= 0.0) {
			out.R = v;
			out.G = v;
			out.B = v;
			return out;
		};

		hh = h;
		if(hh >= 360.0)
			hh = 0.0;
		hh /= 60.0;

		i = (long)hh;
		ff = hh - i;
		p = v * (1.0 - s);
		q = v * (1.0 - (s * ff));
		t = v * (1.0 - (s * (1.0 - ff)));

		switch(i) {
			case 0:
				out.R = v;
				out.G = t;
				out.B = p;
				break;
			case 1:
				out.R = q;
				out.G = v;
				out.B = p;
				break;
			case 2:
				out.R = p;
				out.G = v;
				out.B = t;
				break;
			case 3:
				out.R = p;
				out.G = q;
				out.B = v;
				break;
			case 4:
				out.R = t;
				out.G = p;
				out.B = v;
				break;
			default:
				out.R = v;
				out.G = p;
				out.B = q;
				break;
		}

		return out;
	};

	Color3 fromHex(int hex_value) {
		return Color3(
			((hex_value >> 16) & 0xFF), // Extract the RR byte
			((hex_value >> 8) & 0xFF), // Extract the GG byte
			((hex_value) & 0xFF) // Extract the BB byte
		);
	};

}

