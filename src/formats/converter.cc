#include <cassert>
#include <stdexcept>
#include "formats/converter.h"
#include "logger.h"

void Converter::add_cli_help(__attribute__((unused)) ArgParser &arg_parser)
{
}

void Converter::parse_cli_options(__attribute__((unused)) ArgParser &arg_parser)
{
}

bool Converter::decode_internal(__attribute__((unused)) VirtualFile &)
{
    throw std::runtime_error("Decoding is not supported");
}

bool Converter::decode(VirtualFile &target_file)
{
    target_file.io.seek(0);
    return decode_internal(target_file);
}

bool Converter::try_decode(VirtualFile &target_file)
{
    try
    {
        return decode(target_file);
    }
    catch (...)
    {
        return false;
    }
}

Converter::~Converter()
{
}
