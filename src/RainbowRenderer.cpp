#include "RainbowRenderer.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdio>

void HSVtoRGB(double& fR, double& fG, double& fB, double& fH, double& fS, double& fV);

RainbowRenderer::RainbowRenderer(const Config & config)
	: MultiBridgeRenderer(config)
{
	for (int i = 0; i < N; ++i) {
		hue_[i] = i*(2.0*360.0/static_cast<double>(N));
	}
}

void HSVtoRGB(double& fR, double& fG, double& fB, double& fH, double& fS, double& fV);

void RainbowRenderer::prepareFrame()
{
	for (int i = 0; i < N; ++i)
	{
		hue_[i] = fmod(hue_[i] + hueDelta, 360.0);
		huestream::Color & c = colors_[i];
		double r, g, b;
		HSVtoRGB(r, g, b, hue_[i], sat_, brightness_);
		c.SetR(r);
		c.SetG(g);
		c.SetB(b);
		//printf("id %d <= (%f, %f, %f)\n", i, c.GetR(), c.GetG(), c.GetB());
    }
}

void HSVtoRGB(double& fR, double& fG, double& fB, double& fH, double& fS, double& fV) {
	double fC = fV * fS; // Chroma
	double fHPrime = fmod(fH / 60.0, 6);
	double fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
	double fM = fV - fC;

	if(0 <= fHPrime && fHPrime < 1) {
		fR = fC;
		fG = fX;
		fB = 0;
	} else if(1 <= fHPrime && fHPrime < 2) {
		fR = fX;
		fG = fC;
		fB = 0;
	} else if(2 <= fHPrime && fHPrime < 3) {
		fR = 0;
		fG = fC;
		fB = fX;
	} else if(3 <= fHPrime && fHPrime < 4) {
		fR = 0;
		fG = fX;
		fB = fC;
	} else if(4 <= fHPrime && fHPrime < 5) {
		fR = fX;
		fG = 0;
		fB = fC;
	} else if(5 <= fHPrime && fHPrime < 6) {
		fR = fC;
		fG = 0;
		fB = fX;
	} else {
		fR = 0;
		fG = 0;
		fB = 0;
	}

	fR += fM;
	fG += fM;
	fB += fM;
}
