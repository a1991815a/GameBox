#include "TextureCache.h"

TextureCache* TextureCache::m_instance = nullptr;

TextureCache* TextureCache::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new TextureCache();
	return m_instance;
}

void TextureCache::destroyInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

void TextureCache::push(const char* name, Texture* texture)
{
	if (m_mTextureMap.find(name) == m_mTextureMap.end())
		m_mTextureMap.insert(name, texture);
}

void TextureCache::pop(Texture* texture)
{
	if(!texture->getName().empty())
		m_mTextureMap.erase(texture->getName());
}

Texture* TextureCache::getTexture(const char* name) const
{
	return m_mTextureMap.at(name);
}

Texture* TextureCache::getSafeTexture(const char* name) const
{
	auto itor = m_mTextureMap.end();
	if ((itor = m_mTextureMap.find(name)) == m_mTextureMap.end())
		return nullptr;
	return itor->second;
}
