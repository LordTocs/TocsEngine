#include "IndexFormat.h"

namespace Tocs {
namespace Graphics {

const IndexFormat IndexFormat::SixteenBit(sixteenbit);
const IndexFormat IndexFormat::ThirtyTwoBit(thirtytwobit);

int IndexFormat::GetGLEnum() const { return Internal; }

}}