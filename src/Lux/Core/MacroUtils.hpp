#pragma once

#define LUX_PRIVATE_CONCAT(a, b) a##b
#define LUX_CONCAT(a, b) LUX_PRIVATE_CONCAT(a, b)
