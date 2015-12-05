#include "Texture.h"
#include "DXUtils.h"
#include "TextureCache.h"

#pragma warning(disable:4244)

Texture::Texture()
	:m_pTexture(nullptr), m_sSize(0, 0)
{

}

Texture::~Texture()
{
	SAFE_RELEASE_COM(m_pTexture);
}

Texture* Texture::create(const char* path)
{
	Texture* ret = _textureCache->getSafeTexture(path);
	if (ret)
	{
		ret->retain();
		return ret;
	}
	ret = new Texture();
	if (ret && ret->init(path))
	{
		ret->autorelease();
		_textureCache->push(path, ret);
		return ret;
	}

	delete ret;
	return nullptr;
}

bool Texture::init()
{
	return true;
}

bool Texture::init(const char* path)
{
	return loadTexture(path);
}

bool Texture::createTexture(
	const char* path, 
	size_t width, size_t height,
	DWORD usage, 
	D3DPOOL pool /*= D3DPOOL_DEFAULT*/)
{
	reset();
	HRESULT result = D3DERR_INVALIDCALL;

	result = D3DXCreateTexture(
		dxGetDevice(),
		width, height,
		0,
		usage,
		D3DFMT_A8R8G8B8,
		pool,
		&m_pTexture
		);

	return SUCCEEDED(result);
}

bool Texture::loadTexture(const char* path, D3DPOOL pool /*= D3DPOOL_DEFAULT*/, bool pow2 /*= false*/)
{
	reset();
	D3DXIMAGE_INFO info = { 0 };
	HRESULT result = D3DERR_INVALIDCALL;
	if (pow2)
		result = D3DXCreateTextureFromFileExA(
			dxGetDevice(),
			path,
			D3DX_DEFAULT, D3DX_DEFAULT,
			0,
			0,
			D3DFMT_A8R8G8B8,
			pool,
			D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(0, 0, 0, 0),
			&info,
			nullptr,
			&m_pTexture
			);
	else
		result = D3DXCreateTextureFromFileExA(
			dxGetDevice(),
			path,
			D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
			0,
			0,
			D3DFMT_A8R8G8B8,
			pool,
			D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(0, 0, 0, 0),
			&info,
			nullptr,
			&m_pTexture
			);
	m_sSize.width = info.Width;
	m_sSize.height = info.Height;
	if (SUCCEEDED(result))
		m_sName = path;

	return SUCCEEDED(result);
}

DWORD Texture::getUsage() const
{
	D3DSURFACE_DESC desc;
	m_pTexture->GetLevelDesc(0, &desc);
	return desc.Usage;
}

D3DPOOL Texture::getPool() const
{
	D3DSURFACE_DESC desc;
	m_pTexture->GetLevelDesc(0, &desc);
	return desc.Pool;
}

void Texture::reset()
{
	SAFE_RELEASE_COM(m_pTexture);
	m_sSize.width = m_sSize.height = 0;
}

const Size& Texture::getSize() const
{
	return m_sSize;
}

size_t Texture::getWidth() const
{
	return m_sSize.width;
}

size_t Texture::getHeight() const
{
	return m_sSize.height;
}

IDirect3DTexture9* Texture::getTexture() const
{
	return m_pTexture;
}

IDirect3DTexture9* Texture::getSafeTexture() const
{
	if (this == nullptr)
		return nullptr;
	return m_pTexture;
}

const std::string& Texture::getName() const
{
	return m_sName;
}

void Texture::setupTexture(DWORD index)
{
	dxSetTexture(index, m_pTexture);
}

void Texture::setupTexture_Safe(DWORD index)
{
	if (this == nullptr)
	{
		dxSetTexture(index, nullptr);
		return;
	}
	dxSetTexture(index, m_pTexture);
}

#pragma warning(default:4244)