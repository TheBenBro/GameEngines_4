#include "TextureHandle.h"

std::unique_ptr<TextureHandle> TextureHandle::textureInstance = nullptr;

std::vector<Texture*> TextureHandle::textures = std::vector<Texture*>();
TextureHandle* TextureHandle::GetInstance()
{
	if (textureInstance.get() == nullptr) {
		textureInstance.reset(new TextureHandle);
	}
	return textureInstance.get();
}

void TextureHandle::OnDestroy()
{
	if (textures.size() > 0) {
		for (auto t : textures) {
			glDeleteTextures(1, &t->textureID);
			delete t;
			t = nullptr;
		}
		textures.clear();
	}
}

void TextureHandle::CreateTexture(const std::string& textureName_, const std::string& textureFilePath_)
{
	if (GetTextureData(textureName_)) {
		return;
	}
	Texture* t = new Texture();
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(textureFilePath_.c_str());
	if (surface == nullptr) {
		Debug::Error("Surface for texture " + textureName_ + "failed to be created",
			"TextureHandler.cpp", __LINE__);
		delete t;
		t = nullptr;
		return;
	}
	glGenTextures(1, &t ->textureID);
	glBindTexture(GL_TEXTURE_2D, t->textureID);
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0,
		mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	t->width = static_cast<float>(surface->w);
	t->height = static_cast<float>(surface->h);
	t->textureName = textureName_;

	textures.push_back(t);

	SDL_FreeSurface(surface);
	surface = nullptr;
}

const GLuint TextureHandle::GetTexture(const std::string& textureName_)
{
	for (auto t : textures) {
		if (t->textureName == textureName_) {
			return t->textureID;
		}
	}
	return 0;
}

const Texture* TextureHandle::GetTextureData(const std::string textureName_)
{
	for (auto t : textures) {
		if (t->textureName == textureName_) {
			return t;
		}
	}
	return nullptr;
}

TextureHandle::TextureHandle()
{
	textures.reserve(10);
}

TextureHandle::~TextureHandle()
{
	OnDestroy();
}
