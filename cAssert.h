/****************************************************************/
/** @file:    cAssert.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		12/7
 *  @version:	1.1
 *  @brief:   define assert method
 *
 *  @note:
 *
 ****************************************************************/
#ifndef _cAssert_h
#define _cAssert_h

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define LOG_ERROR 0
#define LOG_DEBUG 1
#define LOG_INFO  2
#define LOG_TEST  3

#define ASSERT_ON_COMPILE(ex) \
	{ uint8_t cassert_type[(ex) ? 1 : -1]; \
	(void)cassert_type;}

#if  ASSERTLV == 0
#define REQUIRE(test_)
#define ENSURE(test_)
#define INVARIANT(test_)
#define ERROR(test_)
#define ALLEGE(test_)
#elif ASSERTLV == 1
#define REQUIRE(test_)         my_assert_param(test_)         // PRECONDITION#define ENSURE(test_)          my_assert_param(test_)                 // CONDITIONS MAY MEET, BUT NEED TO ENSURE#define INVARIANT(test_)
#define ERROR(test_)
#define ALLEGE(test_)
#elif ASSERTLV == 2
#define REQUIRE(test_)         my_assert_param(test_)         // PRECONDITION#define ENSURE(test_)          my_assert_param(test_)                 // CONDITIONS MAY MEET, BUT NEED TO ENSURE#define INVARIANT(test_)       my_assert_param(test_)         // MUST BE ALWAYS TRUE#define ERROR(test_)           my_assert_param(test_)                 // IF IT HAS ANY ERROR#define ALLEGE(test_)          my_assert_param(test_)                 // THIS CASE NOT ALLOW TO HAPPEN PRACTICALLY#endif /* USE_FULL_ASSERT */

#ifdef  USE_MY_ASSERT
#define my_assert_param(expr)  ((expr) ? (void)0 : my_assert_failed((uint8_t *)__FILE__, __LINE__, 0, (int8_t *)#expr))
void my_assert_failed(uint8_t * file, uint32_t line, uint32_t fileIndex,
		int8_t * expression);
///@ref:http://www.barrgroup.com/Embedded-Systems/How-To/Use-Assert-Macro
#define compile_time_assert(cond)  \
    extern int8_t assertion[(cond) ? 1 : -1]
#else
#define my_assert_param(expr)        ((void)0)
#endif

#ifdef DEBUGON
#define DEBUG(level, fmt, ...) \
    if (DEBUGLV >= level) { \
        DebugLogHandle((char*)"DB:%d:", level); \
        DebugLogHandle((char*)fmt, __VA_ARGS__); \
    }
void DebugLogHandle(char * msg, ...);
#else
#define DEBUG(level, fmt, ...) ((void)0)
#endif

#ifdef __cplusplus
}
#endif
#endif /* ifndef _cAssert_h */
