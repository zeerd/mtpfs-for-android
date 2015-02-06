/* Those functions were parts of glib
 * Copyright : COPYING.glib */
 
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#pragma once

#define G_STATIC_MUTEX_INIT { NULL }

#ifndef TRUE
#define TRUE (~0)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#define GStaticMutex pthread_mutex_t
#define g_static_mutex_lock pthread_mutex_lock
#define g_static_mutex_unlock pthread_mutex_unlock
#define g_ascii_strcasecmp strcasecmp
#define g_ascii_strncasecmp strncasecmp
#define g_free free
#define g_malloc malloc
#define g_strndup strndup
#define g_strdup strdup


typedef char   gchar;
typedef int    gint;
typedef int   gboolean;

typedef unsigned char   guchar;
typedef unsigned long   gulong;
typedef unsigned int    guint;

typedef void* gpointer;
typedef const void *gconstpointer;

#define GUINT_TO_POINTER(u) ((gpointer) (gulong) (u))
#define GPOINTER_TO_UINT(p) ((guint) (gulong) (p))

static const unsigned short ascii_table_data[256] = {
  0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
  0x004, 0x104, 0x104, 0x004, 0x104, 0x104, 0x004, 0x004,
  0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
  0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
  0x140, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x459, 0x459, 0x459, 0x459, 0x459, 0x459, 0x459, 0x459,
  0x459, 0x459, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x0d0, 0x653, 0x653, 0x653, 0x653, 0x653, 0x653, 0x253,
  0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253,
  0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253,
  0x253, 0x253, 0x253, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
  0x0d0, 0x473, 0x473, 0x473, 0x473, 0x473, 0x473, 0x073,
  0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073,
  0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073,
  0x073, 0x073, 0x073, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x004
  /* the upper 128 are all zeroes */
};

typedef struct _GSList GSList;
struct _GSList
{
  gpointer data;
  GSList *next;
};

typedef gint            (*GCompareFunc)         (gconstpointer  a,
                                                 gconstpointer  b);

#define G_ASCII_SPACE   (1 << 8)

#define g_isspace(c) ((ascii_table_data[(guchar) (c)] & G_ASCII_SPACE) != 0)
extern gint g_str_has_prefix (const gchar *str, const gchar *prefix);
extern gchar * g_strchomp (gchar *string);
extern gchar** g_strsplit (const gchar *string, const gchar *delimiter, gint max_tokens);
extern gchar * g_strrstr (const gchar *haystack, const gchar *needle);
extern void g_strfreev (gchar **str_array);
extern guint g_strv_length (gchar **str_array);
extern gchar* g_strconcat (const gchar *string1, ...);

#define g_slist_next(sl) ((sl) ? (((GSList *)(sl))->next) : NULL)
extern guint g_slist_length (GSList *list);
extern GSList* g_slist_append (GSList *list, void* data);
extern GSList* g_slist_prepend (GSList *list, void* data);
extern GSList* g_slist_find_custom (GSList *list, gconstpointer data, GCompareFunc func);
extern void* g_slist_nth_data (GSList *list, guint n);
extern GSList* g_slist_remove (GSList *list, gconstpointer data);
extern void g_slist_free (GSList *list);

extern gchar * g_path_get_basename (const gchar *file_name);
