#ifndef AU_FMT_BGI_CBG_CONVERTER_H
#define AU_FMT_BGI_CBG_CONVERTER_H
#include "fmt/converter.h"

namespace au {
namespace fmt {
namespace bgi {

    class CbgConverter final : public Converter
    {
    protected:
        bool is_recognized_internal(File &) const override;
        std::unique_ptr<File> decode_internal(File &) const override;
    };

} } }

#endif