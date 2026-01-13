/*
 * Minimal BSD sys/cdefs.h compatibility shim
 * Provides macros needed by queue.h on non-BSD systems
 * Based on FreeBSD sys/cdefs.h (BSD-3-Clause)
 */
#ifndef _SYS_CDEFS_H_
#define _SYS_CDEFS_H_

#include <stddef.h>
#include <stdint.h>

/* C++ compatibility */
#if defined(__cplusplus)
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS   }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif

/* Branch prediction hints */
#ifndef __predict_true
#if defined(__GNUC__) || defined(__clang__)
#define __predict_true(exp)  __builtin_expect((exp), 1)
#define __predict_false(exp) __builtin_expect((exp), 0)
#else
#define __predict_true(exp)  (exp)
#define __predict_false(exp) (exp)
#endif
#endif

/* offsetof - use builtin if available */
#ifndef __offsetof
#if defined(__GNUC__) || defined(__clang__)
#define __offsetof(type, field) __builtin_offsetof(type, field)
#else
#define __offsetof(type, field) offsetof(type, field)
#endif
#endif

/* Type dequalification (remove const/volatile) */
#ifndef __DEQUALIFY
#define __DEQUALIFY(type, var) ((type)(uintptr_t)(const volatile void *)(var))
#endif

/* Container of - get struct pointer from member pointer */
#ifndef __containerof
#define __containerof(x, s, m) ({                                       \
    const volatile __typeof(((s *)0)->m) *__x = (x);                    \
    __DEQUALIFY(s *, (const volatile char *)__x - __offsetof(s, m));    \
})
#endif

/* NOTE: We intentionally do NOT define __unused here because
 * musl libc uses __unused as a field name in struct stat.
 * The __unused attribute is not needed by queue.h anyway. */

#endif /* _SYS_CDEFS_H_ */
