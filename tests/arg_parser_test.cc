#include <assert.h>
#include <string.h>
#include "arg_parser.h"

void test_switch_missing()
{
    ArgParser ap;
    assert(ap.get_switch("-s") == "");
    assert(ap.get_switch("--long") == "");
    assert(!ap.has_switch("-s"));
    assert(!ap.has_switch("--long"));
}

void test_switch_is_not_a_flag()
{
    ArgParser ap;
    const char *argv[1] = {"-f"};
    ap.parse(1, argv);
    assert(ap.get_switch("-f") == "");
    assert(!ap.has_switch("-f"));
}

void test_switch_short()
{
    ArgParser ap;
    const char *argv[1] = {"-s=short"};
    ap.parse(1, argv);
    assert(ap.get_switch("-s") == "short");
    assert(ap.get_switch("s") == "short");
    assert(ap.has_switch("-s"));
    assert(ap.has_switch("s"));
}

void test_switch_long()
{
    ArgParser ap;
    const char *argv[1] = {"--long=long"};
    ap.parse(1, argv);
    assert(ap.get_switch("--long") == "long");
    assert(ap.get_switch("-long") == "long");
    assert(ap.get_switch("long") == "long");
    assert(ap.has_switch("--long"));
    assert(ap.has_switch("-long"));
    assert(ap.has_switch("long"));
}

void test_switch_overriding_short()
{
    ArgParser ap;
    const char *argv[2] = {"-s=short1", "-s=short2"};
    ap.parse(2, argv);
    assert(ap.get_switch("-s") == "short2");
}

void test_switch_overriding_long()
{
    ArgParser ap;
    const char *argv[2] = {"--long=long1", "--long=long2"};
    ap.parse(2, argv);
    assert(ap.get_switch("--long") == "long2");
}

void test_switch_with_space()
{
    ArgParser ap;
    const char *argv[1] = {"--switch=long switch"};
    ap.parse(1, argv);
    assert(ap.get_switch("--switch") == "long switch");
}

void test_switch_empty_value()
{
    ArgParser ap;
    const char *argv[1] = {"--switch="};
    ap.parse(1, argv);
    assert(ap.get_switch("--switch") == "");
}

void test_flag_missing()
{
    ArgParser ap;
    assert(!ap.has_flag("nope"));
}

void test_flag()
{
    ArgParser ap;
    const char *argv[1] = {"--flag"};
    ap.parse(1, argv);
    assert(ap.has_flag("flag"));
}

void test_flag_mixed_with_stray()
{
    ArgParser ap;
    const char *argv[2] = {"--flag", "stray"};
    ap.parse(2, argv);
    assert(ap.has_flag("flag"));
    auto stray = ap.get_stray();
    assert(stray.size() == 1);
    assert(stray[0] == "stray");
}

void test_stray_missing()
{
    ArgParser ap;
    auto stray = ap.get_stray();
    assert(stray.size() == 0);
}

void test_stray()
{
    ArgParser ap;
    const char *argv[2] = {"stray1", "stray2"};
    ap.parse(2, argv);
    auto stray = ap.get_stray();
    assert(stray.size() == 2);
    assert(stray[0] == "stray1");
    assert(stray[1] == "stray2");
}

void test_stray_with_space()
{
    ArgParser ap;
    const char *argv[1] = {"long stray"};
    ap.parse(1, argv);
    auto stray = ap.get_stray();
    assert(stray.size() == 1);
    assert(stray[0] == "long stray");
}

void test_mixed_types()
{
    ArgParser ap;
    const char *argv[5] =
    {
        "stray1",
        "--switch=s",
        "--flag1",
        "stray2",
        "--flag2"
    };
    ap.parse(5, argv);

    assert(ap.get_switch("--switch") == "s");
    assert(ap.has_flag("flag1"));
    assert(ap.has_flag("flag2"));

    auto stray = ap.get_stray();
    assert(stray.size() == 2);
    assert(stray[0] == "stray1");
    assert(stray[1] == "stray2");
}

#if 0
#endif

int main(void)
{
    test_switch_missing();
    test_switch_is_not_a_flag();
    test_switch_short();
    test_switch_long();
    // TODO: make this pass
    #if 0
    test_switch_overriding_short();
    test_switch_overriding_long();
    #endif
    test_switch_with_space();
    test_switch_empty_value();
    test_flag_missing();
    test_flag();
    test_flag_mixed_with_stray();
    test_stray_missing();
    test_stray();
    test_stray_with_space();
    test_mixed_types();
    return 0;
}
