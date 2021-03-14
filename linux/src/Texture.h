#ifndef _TEXTURE_INCLUDE
#define _TEXTURE_INCLUDE

//Theirs

#include <string>

#include <GL/glew.h>


enum PixelFormat {TEXTURE_PIXEL_FORMAT_RGB, TEXTURE_PIXEL_FORMAT_RGBA};


class Texture
{

	public:

	Texture();

	bool loadFromFile(const std::string &filename, PixelFormat format);
	void loadFromGlyphBuffer(unsigned char *buffer, int width, int height);

	void createEmptyTexture(int width, int height);
	void loadSubtextureFromGlyphBuffer(unsigned char *buffer, int x, int y, int width, int height);
	void generateMipmap();
	
	void setWrapS(GLint value);
	void setWrapT(GLint value);
	void setMinFilter(GLint value);
	void setMagFilter(GLint value);
	
	void use() const;
	
	int width() const { return widthTex; }
	int height() const { return heightTex; }

	private:

	int widthTex, heightTex;
	GLuint texId;
	GLint wrapS, wrapT, minFilter, magFilter;

};

#endif // _TEXTURE_INCLUDE

