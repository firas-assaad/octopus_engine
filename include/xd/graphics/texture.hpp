#ifndef H_XD_GRAPHICS_TEXTURE
#define H_XD_GRAPHICS_TEXTURE

#include "../vendor/glew/glew.h"
#include "../asset_serializer.hpp"
#include "image.hpp"
#include <memory>
#include <string>

namespace xd
{
    class texture
    {
    public:
        texture(const texture&) = delete;
        texture& operator=(const texture&) = delete;
        texture(int width, int height, const void *data = 0, vec4 ck = vec4(0),
            GLint wrap_s = GL_REPEAT, GLint wrap_t = GL_REPEAT,
            GLint mag_filter = GL_LINEAR, GLint min_filter = GL_LINEAR);
        texture(const std::string& filename, vec4 ck = vec4(0),
            GLint wrap_s = GL_REPEAT, GLint wrap_t = GL_REPEAT,
            GLint mag_filter = GL_LINEAR, GLint min_filter = GL_LINEAR);
        texture(const xd::image& image,
            GLint wrap_s = GL_REPEAT, GLint wrap_t = GL_REPEAT,
            GLint mag_filter = GL_LINEAR, GLint min_filter = GL_LINEAR);
        virtual ~texture();

        void bind() const noexcept;
        void bind(int unit) const noexcept;

        void load(const std::string& filename, vec4 color_key = vec4(0));
        void load(const xd::image& image);
        void load(int width, int height, const void *data, vec4 color_key = vec4(0));
        void load(const void *data);
        void copy_read_buffer(int x, int y, int width, int height);

        GLuint texture_id() const noexcept { return m_texture_id; }
        int width() const noexcept { return m_width; }
        int height() const noexcept { return m_height; }
        vec4 color_key() const noexcept { return m_color_key; }

        void set_wrap(GLint wrap_s, GLint wrap_t);
        void set_filter(GLint mag_filter, GLint min_filter);

    private:
        GLuint m_texture_id;
        int m_width;
        int m_height;
        vec4 m_color_key;
        mutable int m_unit;

        void init();
    };

    template <>
    struct asset_serializer<xd::texture>
    {
        typedef std::string key_type;
        key_type operator()(const std::string& filename, xd::vec4,
            GLint = GL_REPEAT, GLint = GL_REPEAT,
            GLint = GL_LINEAR, GLint = GL_LINEAR) const
        {
            return filename;
        }
        key_type operator()(const xd::image& image,
            GLint = GL_REPEAT, GLint = GL_REPEAT,
            GLint = GL_LINEAR, GLint = GL_LINEAR) const
        {
            return image.filename();
        }
    };
}

#endif
