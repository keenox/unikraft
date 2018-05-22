/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Simon Kuenzer <simon.kuenzer@neclab.eu>
 *
 *
 * Copyright (c) 2017, NEC Europe Ltd., NEC Corporation. All rights reserved.
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * THIS HEADER MAY NOT BE EXTRACTED OR MODIFIED IN ANY WAY.
 */

#ifndef __UK_ESSENTIALS_H__
#define __UK_ESSENTIALS_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__
#ifndef __packed
#define __packed               __attribute__((packed))
#endif
#ifndef __noreturn
#define __noreturn             __attribute__((noreturn))
#endif
#ifndef __weak
#define __weak                 __attribute__((weak))
#endif
#ifndef __used
#define __used                 __attribute__((used))
#endif
#ifndef __unused
#define __unused               __attribute__((unused))
#endif
#ifndef __section
#define __section(s)           __attribute__((section(s)))
#endif
#ifndef __nonnull
#define __nonnull              __attribute__((nonnull))
#endif
#ifndef __printf
#define __printf(fmt, args)    __attribute__((format(printf, (fmt), (args))))
#endif
#ifndef __scanf
#define __scanf(fmt, args)     __attribute__((format(scanf, (fmt), (args))))
#endif
#ifndef __align
#define __align(bytes)         __attribute__((aligned(bytes)))
#endif

/**
  * Mark a function as constructor
  * The compiler/linker will populate a function pointer
  * to the init_array section
  */
#ifndef __constructor
#define __constructor __attribute__ ((constructor))
#endif

/**
  * Mark a function as constructor with priority
  * The compiler/linker will populate a function pointer
  * (sorted by priority) to the init_array section
  * Prioritized constructors are called before
  * non-prioritized ones
  *
  * @param lvl
  *   Priority level (101 (earliest)...onwards (latest))
  */
#ifndef __constructor_prio
#define __constructor_prio(lvl) __attribute__ ((constructor (lvl)))
#endif

#else
/* TO BE DEFINED */
#endif /* __GNUC__ */

#define __align4       __align(0x04)
#define __align8       __align(0x08)
#define __align16      __align(0x010)
#define __align32      __align(0x020)
#define __align64      __align(0x040)
#define __align4k      __align(0x1000)
#define __align32b     __align4
#define __align64b     __align8
#define __align128b    __align16
#define __align256b    __align32
#define __align512b    __align64

#ifndef STRINGIFY
#ifndef __STRINGIFY
#define __STRINGIFY(x) #x
#endif
#define STRINGIFY(x) __STRINGIFY(x)
#endif

#ifndef MIN
#define MIN(a, b)                                                              \
	({                                                                     \
		__typeof__(a) __a = (a);                                       \
		__typeof__(b) __b = (b);                                       \
		__a < __b ? __a : __b;                                         \
	})
#endif
#ifndef MIN3
#define MIN3(a, b, c) MIN(MIN((a), (b)), (c))
#endif
#ifndef MIN4
#define MIN4(a, b, c, d) MIN(MIN((a), (b)), MIN((c), (d)))
#endif

#ifndef MAX
#define MAX(a, b)                                                              \
	({                                                                     \
		__typeof__(a) __a = (a);                                       \
		__typeof__(b) __b = (b);                                       \
		__a > __b ? __a : __b;                                         \
	})
#endif
#ifndef MAX3
#define MAX3(a, b, c) MAX(MAX((a), (b)), (c))
#endif
#ifndef MAX4
#define MAX4(a, b, c, d) MAX(MAX((a), (b)), MAX((c), (d)))
#endif

#ifndef POWER_OF_2
#define POWER_OF_2(v) ((0 != v) && (0 == (v & (v - 1))))
#endif

#ifndef DIV_ROUND_UP
#define DIV_ROUND_UP(v, d) (((v) + (d)-1) / (d))
#endif

/* Note: a has to be a power of 2 */
#ifndef ALIGN_UP
#define ALIGN_UP(v, a) (((v) + (a)-1) & ~((a)-1))
#endif

/* Note: a has to be a power of 2 */
#ifndef ALIGN_DOWN
#define ALIGN_DOWN(v, a) ((v) & ~((a)-1))
#endif

#ifndef DECONST
#include <uk/arch/types.h>
#define DECONST(t, a) ((t)((__uptr)((const void *)(a))))
#endif

#ifndef DEQUALIFY
#include <uk/arch/types.h>
#define DEQUALIFY(t, a) ((t)(__uptr)(const volatile void *)(a))
#endif


/* The following code was taken from FreeBSD: sys/sys/cdefs.h */
/*
 * Macro to test if we're using a specific version of gcc or later.
 */
#ifndef __GNUC_PREREQ__
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
#define	__GNUC_PREREQ__(ma, mi)	\
	(__GNUC__ > (ma) || __GNUC__ == (ma) && __GNUC_MINOR__ >= (mi))
#else
#define __GNUC_PREREQ__(ma, mi) 0
#endif
#endif /* !__GNUC_PREREQ__ */

#ifndef __offsetof
#if __GNUC_PREREQ__(4, 1)
#define __offsetof(t, field)       __builtin_offsetof(t, field)
#else
#define __offsetof(t, field) \
	((__sz)(__uptr)((const volatile void *)&((t *)0)->field))
#endif
#endif /* !__offsetof */

/*
 * Given the pointer x to the member m of the struct s, return
 * a pointer to the containing structure.  When using GCC, we first
 * assign pointer x to a local variable, to check that its type is
 * compatible with member m.
 */
#ifndef __containerof
#if __GNUC_PREREQ__(3, 1)
#define __containerof(x, s, m) ({ \
	const volatile __typeof(((s *)0)->m) *__x = (x); \
	DEQUALIFY(s *, (const volatile char *)__x - __offsetof(s, m)); \
})
#else
#define __containerof(x, s, m) \
	DEQUALIFY(s *, (const volatile char *)(x) - __offsetof(s, m))
#endif
#endif /* !__containerof */

#ifdef __cplusplus
}
#endif

#endif /* __UK_ESSENTIALS_H__ */
