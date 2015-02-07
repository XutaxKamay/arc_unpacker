#include <cassert>
#include <cstring>
#include <memory>
#include "formats/image.h"
#include "file_io.h"
#include "logger.h"
#include "test_support/converter_support.h"
#include "virtual_file.h"

namespace
{
    void compare_images(
        const Image *expected_image,
        const Image *actual_image)
    {
        if (expected_image == nullptr || actual_image == nullptr)
        {
            assert(expected_image == nullptr);
            assert(actual_image == nullptr);
            return;
        }

        assert(image_width(expected_image) == image_width(actual_image));
        assert(image_height(expected_image) == image_height(actual_image));

        size_t x, y;
        for (y = 0; y < image_height(expected_image); y ++)
        {
            for (x = 0; x < image_width(expected_image); x ++)
            {
                uint32_t expected_rgba = image_color_at(expected_image, x, y);
                uint32_t actual_rgba = image_color_at(actual_image, x, y);
                if (expected_rgba != actual_rgba)
                {
                    log_error(
                        "Image pixels differ at %d, %d (%08x != %08x)",
                        x,
                        y,
                        expected_rgba,
                        actual_rgba);
                    assert(0);
                }
            }
        }
    }

    Image *get_actual_image(const std::string path, Converter *converter)
    {
        FileIO io(path, "rb");
        std::unique_ptr<VirtualFile> file(new VirtualFile);
        file->io.write_from_io(io, io.size());
        converter->decode(*file);
        return image_create_from_boxed(file->io);
    }

    Image *get_expected_image(const std::string path)
    {
        FileIO io(path, "rb");
        Image *image = image_create_from_boxed(io);
        assert(image != nullptr);
        return image;
    }
}

void assert_decoded_image(
    Converter *converter,
    const char *path_to_input,
    const char *path_to_expected)
{
    assert(converter != nullptr);
    assert(path_to_input != nullptr);
    assert(path_to_expected != nullptr);

    Image *actual_image = get_actual_image(path_to_input, converter);
    Image *expected_image = get_expected_image(path_to_expected);

    compare_images(expected_image, actual_image);

    image_destroy(actual_image);
    image_destroy(expected_image);
}
