#ifndef __TEXTURE__
#define __TEXTURE__
#include "GameHeader.h"
#include "Ref.h"

class Texture: public Ref, nocopy{
	friend class TextureCache;
public:
	Texture();
	~Texture();
	CREATE_FUNC(Texture);
	static Texture* create(const char* path);
	bool init();
	bool init(const char* path);
	
	bool createTexture(const char* path, 
		size_t width, size_t height, 
		DWORD usage, 
		D3DPOOL pool = D3DPOOL_DEFAULT);

	bool loadTexture(const char* path, D3DPOOL pool = D3DPOOL_DEFAULT, bool pow2 = false);

	DWORD getUsage() const;
	D3DPOOL getPool() const;

	void reset();
	const Size& getSize() const;
	size_t getWidth() const;
	size_t getHeight() const;
	IDirect3DTexture9* getTexture() const;
	IDirect3DTexture9* getSafeTexture() const;
	const std::string& getName() const;

	void setupTexture(DWORD index);
	void setupTexture_Safe(DWORD index);
private:
	IDirect3DTexture9*		m_pTexture;
	Size					m_sSize;
	std::string				m_sName;
};
#endif