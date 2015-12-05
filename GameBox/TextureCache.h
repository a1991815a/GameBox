#ifndef __TEXTURECACHE__
#define __TEXTURECACHE__
#include "GameHeader.h"
#include "Texture.h"

#define _textureCache TextureCache::getInstance()

class TextureCache{
public:
	static TextureCache* getInstance();
	static void destroyInstance();
private:
	static TextureCache* m_instance;
public:
	
	void push(const char* name, Texture* texture);
	void pop(Texture* texture);
	Texture* getTexture(const char* name) const;
	Texture* getSafeTexture(const char* name) const;
private:
	Map<std::string, Texture*> m_mTextureMap;
};
#endif