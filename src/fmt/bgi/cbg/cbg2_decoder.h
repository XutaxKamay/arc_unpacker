#pragma once

#include "io/io.h"
#include "pix/grid.h"

namespace au {
namespace fmt {
namespace bgi {
namespace cbg {

    class Cbg2Decoder final
    {
    public:
        std::unique_ptr<pix::Grid> decode(io::IO &io) const;
    };

} } } }