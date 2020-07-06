/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @brief Defines various macros.
 *
 * @file centurion_api.hpp
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_API_HEADER
#define CENTURION_API_HEADER

#include <memory>
#include <type_traits>

#include "centurion_cfg.hpp"

/**
 * @brief Used for exporting entities in generated Windows DLL.
 *
 * @def CENTURION_API
 * @headerfile centurion_api.hpp
 * @internal https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
 */
#if defined(_WIN32) && !defined(CENTURION_HEADER_ONLY)
#ifdef WIN_EXPORT
#define CENTURION_API __declspec(dllexport)
#else
#define CENTURION_API __declspec(dllimport)
#endif  // WIN_EXPORT
#else
#define CENTURION_API
#endif  // defined(_WIN32) && !defined(CENTURION_HEADER_ONLY)

/**
 * @brief Used when the pseudo-header-only mode is enabled.
 *
 * @details When header-only mode is enabled, definitions are specified as
 * `inline`.
 *
 * @def CENTURION_DEF
 * @headerfile centurion_api.hpp
 */
#if !defined(CENTURION_DEF) && defined(CENTURION_HEADER_ONLY)
#define CENTURION_DEF inline
#else
#define CENTURION_DEF
#endif

/**
 * @brief Used for methods that return something and aren't inlined.
 *
 * @since 5.0.0
 * @headerfile centurion_api.hpp
 */
#define CENTURION_QUERY [[nodiscard]] CENTURION_API

#endif  // CENTURION_API_HEADER