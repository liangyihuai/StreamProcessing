#pragma once

#include <string>

/**
 * The maximum len allowed for a string attribute.
 * It is better to keep this value as low as minimum to enhance the GPU engine's
 * performance
 */
#define STRING_VAL_LEN 15


 /**
  * Kinds of types for the values of attributes and contraints
  */
enum class ValType { INT = 0, FLOAT = 1, BOOL = 2, STRING = 3 };

namespace Consts {
	const static char* LOG_DIR = "C:\\Users\\LIANG\\Desktop\\temp\\streamprocessingLog\\log";
}

