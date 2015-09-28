#include "fmt/nitroplus/pak_archive_decoder.h"
#include "test_support/archive_support.h"
#include "test_support/file_support.h"
#include "test_support/catch.hh"

using namespace au;
using namespace au::fmt::nitroplus;

static void test_pak_archive(const std::string &path)
{
    std::vector<std::shared_ptr<File>> expected_files
    {
        tests::stub_file("123.txt", "1234567890"_b),
        tests::stub_file("abc.txt", "abcdefghijklmnopqrstuvwxyz"_b),
    };

    PakArchiveDecoder decoder;
    auto actual_files = au::tests::unpack_to_memory(path, decoder);

    tests::compare_files(expected_files, actual_files, true);
}

TEST_CASE("Nitroplus PAK uncompressed archives", "[fmt]")
{
    test_pak_archive("tests/fmt/nitroplus/files/pak/uncompressed.pak");
}

TEST_CASE("Nitroplus PAK compressed archives", "[fmt]")
{
    test_pak_archive("tests/fmt/nitroplus/files/pak/compressed.pak");
}