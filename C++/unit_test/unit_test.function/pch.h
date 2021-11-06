#pragma once

#include "gtest/gtest.h"

// configure) 
#define _CGDK_NO_ASSERT_ON_BOUND_CHECK

#include <array>
#include <unordered_map>
#include <vector>
#if defined(__cpp_lib_format)
	#include <format>
#endif
#include <cgdk/shared_buffer>

#include "test_data.h"

