#ifndef TEXTUREHANDLE_H
#define TEXTUREHANDLE_H

#include <memory>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "../../Core/Debug.h"
#include <glew.h>

struct Texture {
	GLuint textureID = 0;
	float width = 0.0f;
	float height = 0.0f;
	std::string textureName = "";
};
class TextureHandle
{
public:
	TextureHandle(const TextureHandle&) = delete;
	TextureHandle(TextureHandle&&) = delete;
	TextureHandle& operator=(const TextureHandle&) = delete;
	TextureHandle& operator=(TextureHandle&&) = delete;
	static TextureHandle* GetInstance();

	void OnDestroy();

	void CreateTexture(const std::string& textureName_,
		const std::string& textureFilePath_);
	const GLuint GetTexture(const std::string& textureName_);
	const Texture* GetTextureData(const std::string textureName_);

private:
	TextureHandle();
	~TextureHandle();

	static std::unique_ptr<TextureHandle> textureInstance;
	friend std::default_delete<TextureHandle>;
	static std::vector<Texture*> textures;
};
#endif // !TEXTUREHANDLE_H
