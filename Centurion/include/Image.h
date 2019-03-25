#pragma once
#include <SDL.h>
#include <string>
#include "centurion.h"

class centurion::visuals::Image {

private:
	int width;
	int height;
	SDL_Texture* texture = nullptr;

	SDL_Texture* CreateTexture(SDL_Surface* surface, SDL_Renderer* renderer);

	Image(const std::string& path, centurion::visuals::Graphics& graphics);
	
public:
	~Image();

	int GetWidth();

	int GetHeight();

	SDL_Texture* GetTexture();

	static centurion::visuals::Image* Create(const std::string& path, centurion::visuals::Graphics& graphics);

	static void Destroy(centurion::visuals::Image* img);
};