#pragma once

#define GenErrorCase(error) case error: return #error;

namespace Tocs {
namespace Parallel {

bool CheckError (int error);

}}
