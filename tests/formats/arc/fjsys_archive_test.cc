#include "formats/arc/fjsys_archive.h"
#include "test_support/archive_support.h"

void test_fjsys_archive()
{
    std::vector<VirtualFile*> expected_files;
    std::unique_ptr<VirtualFile> file1(new VirtualFile);
    std::unique_ptr<VirtualFile> file2(new VirtualFile);
    file1->name = "abc.txt";
    file2->name = "another.txt";
    file1->io.write("123", 3);
    file2->io.write("abcdefghij", 10);
    expected_files.push_back(file1.get());
    expected_files.push_back(file2.get());

    std::string path = "tests/test_files/arc/fjsys/test.fjsys";
    std::unique_ptr<Archive> archive(new FjsysArchive);
    auto output_files = unpack_to_memory(path, *archive, 0, nullptr);
    auto actual_files = output_files->get_saved();

    compare_files(expected_files, actual_files);
}

int main(void)
{
    test_fjsys_archive();
    return 0;
}
