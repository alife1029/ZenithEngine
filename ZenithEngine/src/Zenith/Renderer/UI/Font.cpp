#include "zenithpch.h"
#include "Font.h"
#include "Zenith/Utils/ZenithException.h"

namespace Zenith
{
	static FT_Library ft;
	static bool ftInitialized = false;
	static unsigned int fontInstanceCount = 0;

	Font::Font(const std::string& path, unsigned int fontSize, Texture2D::Filter filterMode)
	{
		if (!ftInitialized)
		{
			if (FT_Init_FreeType(&ft))
			{
				throw InitializationError(__LINE__, __FILE__, "Failed to initialize FreeType library!");
			}

			ftInitialized = true;
		}

		FT_Face fontFace;
		if (FT_New_Face(ft, path.c_str(), 0, &fontFace))
			throw ResourceNotFoundException(__LINE__, __FILE__, path);

		FT_Set_Pixel_Sizes(fontFace, 0, fontSize);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		m_FontSize = 0u;

		for (unsigned char c = 0; c < 255; c++)
		{
			if (FT_Load_Char(fontFace, c, FT_LOAD_RENDER))
				continue;

			// Generate texture
			uint32_t texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, fontFace->glyph->bitmap.buffer);

			// Set texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			switch (filterMode)
			{
			case Zenith::Texture2D::Filter::Point:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;

			case Zenith::Texture2D::Filter::Trilinear:
			case Zenith::Texture2D::Filter::Bilinear:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			}

			// Store character
			Character _c = {
				texture,
				{ fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows },
				{ fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top },
				static_cast<uint32_t>(fontFace->glyph->advance.x)
			};

			m_Characters.insert(std::pair<char, Character>(c, _c));
			if (static_cast<unsigned int>(_c.GlyphSize.y) > m_FontSize)
				m_FontSize = _c.GlyphSize.y;
		}

		glBindTexture(GL_TEXTURE_2D, NULL);

		// Cleanup
		FT_Done_Face(fontFace);

		++fontInstanceCount;
	}

	Font::~Font()
	{
		// Delete character textures
		for (unsigned char i = 0; i < 255; i++)
		{
			if (m_Characters.count(i))
			{
				Character c = m_Characters[i];
				glDeleteTextures(1, &c.TextureID);
			}
		}

		--fontInstanceCount;
		if (fontInstanceCount == 0)
		{
			FT_Done_FreeType(ft);
			ftInitialized = false;
		}
	}
}
