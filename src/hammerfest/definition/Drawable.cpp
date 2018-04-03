#include "Drawable.h"

Drawable::Drawable()
{
}

Drawable::~Drawable()
{
}

void Drawable::drawHimself(SDL_Surface *dest)
{
}

void Drawable::copySurfaceToBackRenderer(SDL_Surface *src, SDL_Surface *dest, int x, int y, int lengthX, int lengthY)
{
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	if (lengthX == -1)
	{
		dstRect.w = src->w;
	}
	else
	{
		dstRect.w = lengthX;
	}
	if (lengthY == -1)
	{
		dstRect.h = src->h;
	}
	else
	{
		dstRect.h = lengthY;
	}
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	if (lengthX == -1)
	{
		srcRect.w = src->w;
	}
	else
	{
		srcRect.w = lengthX;
	}
	if (lengthY == -1)
	{
		srcRect.h = src->h;
	}
	else
	{
		srcRect.h = lengthY;
	}
	SDL_BlitSurface(src, &srcRect, dest, &dstRect);
}

void Drawable::copySurfaceToBackRendererWithStartOffset(SDL_Surface *src, SDL_Surface *dest, int x, int y, int lengthX, int lengthY, int offsetX, int offsetY)
{
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	if (lengthX == -1)
	{
		dstRect.w = src->w;
	}
	else
	{
		dstRect.w = lengthX;
	}
	if (lengthY == -1)
	{
		dstRect.h = src->h;
	}
	else
	{
		dstRect.h = lengthY;
	}
	SDL_Rect srcRect;
	srcRect.x = offsetX;
	srcRect.y = offsetY;
	if (lengthX == -1)
	{
		srcRect.w = src->w;
	}
	else
	{
		srcRect.w = lengthX;
	}
	if (lengthY == -1)
	{
		srcRect.h = src->h;
	}
	else
	{
		srcRect.h = lengthY;
	}
	SDL_BlitSurface(src, &srcRect, dest, &dstRect);
}

void Drawable::copySurfaceToBackRenderer(SDL_Surface *src, SDL_Surface *dest, int x, int y)
{
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = src->w;
	dstRect.h = src->h;
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = src->w;
	srcRect.h = src->h;
	SDL_BlitSurface(src, &srcRect, dest, &dstRect);
}

void Drawable::fillScreenBufferWithSurface(std::string name, int index, SDL_Surface *destination)
{
	SDL_Surface *temp2 = Sprite::Instance().getAnimation(name, index);
	int x = 0;
	int y = 0;
	while (y < 500)
	{
		while (x < 420)
		{
			copySurfaceToBackRenderer(temp2, destination, x, y);
			x += temp2->w;
		}
		x = 0;
		y += temp2->h;
	}
}