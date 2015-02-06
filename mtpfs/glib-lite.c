
/* Those functions were parts of glib
 * Copyright : COPYING.glib */

#include "glib.h"


#define IS_DIR_SEPARATOR(c) ((c) == '\\' || (c) == '/')

GSList* g_slist_last (GSList *list)
{
  if (list)
    {
      while (list->next)
        list = list->next;
    }

  return list;
}

guint g_slist_length (GSList *list)
{
  guint length;

  length = 0;
  while (list)
    {
      length++;
      list = list->next;
    }

  return length;
}

GSList* g_slist_prepend (GSList *list, void* data)
{
  GSList *new_list;

  new_list = (GSList*)malloc (sizeof(GSList));
  new_list->data = data;
  new_list->next = list;

  return new_list;
}

GSList* g_slist_append (GSList *list, void* data)
{
  GSList *new_list;
  GSList *last;

  new_list = (GSList*)malloc (sizeof(GSList));
  new_list->data = data;
  new_list->next = NULL;

  if (list)
    {
      last = g_slist_last (list);
      /* g_assert (last != NULL); */
      last->next = new_list;

      return list;
    }
  else
    return new_list;
}

GSList* g_slist_find_custom (GSList *list, gconstpointer data, GCompareFunc func)
{
  if (func == NULL){
	  return list;
  }

  while (list)
    {
      if (! func (list->data, data))
        return list;
      list = list->next;
    }

  return NULL;
}

void* g_slist_nth_data (GSList *list, guint n)
{
  while (n-- > 0 && list)
    list = list->next;

  return list ? list->data : NULL;
}

void g_slist_free (GSList *list)
{
  GSList *sl= list;
  for (; sl; sl = sl->next){
	  free(sl->data);
  }
}

GSList* g_slist_remove (GSList *list, gconstpointer data)
{
  GSList *tmp, *prev = NULL;

  tmp = list;
  while (tmp)
    {
      if (tmp->data == data)
        {
          if (prev)
            prev->next = tmp->next;
          else
            list = tmp->next;

          free (tmp);
          break;
        }
      prev = tmp;
      tmp = prev->next;
    }

  return list;
}

//===================================================

void g_strfreev (gchar **str_array)
{
  if (str_array)
    {
      gint i;

      for (i = 0; str_array[i] != NULL; i++)
        free (str_array[i]);

      free (str_array);
    }
}

guint g_strv_length (gchar **str_array)
{
  guint i = 0;

  if (str_array == NULL){
	  return 0;
  }

  while (str_array[i])
    ++i;

  return i;
}

gint g_str_has_prefix (const gchar *str,
                  const gchar *prefix)
{
  if ((str == NULL) || (prefix == NULL)){
	  return 0;
  }

  return strncmp (str, prefix, strlen (prefix)) == 0;
}

gchar * g_strchomp (gchar *string)
{
  size_t len;

  if(string == NULL){
	  return NULL;
  }

  len = strlen (string);
  while (len--)
    {
      if (g_isspace ((guchar) string[len]))
        string[len] = '\0';
      else
        break;
    }

  return string;
}

gchar** g_strsplit (const gchar *string,
            const gchar *delimiter,
            gint         max_tokens)
{
  GSList *string_list = NULL, *GSList;
  gchar **str_array, *s;
  guint n = 0;
  const gchar *remainder;

  if ((string == NULL) || (delimiter == NULL) || (delimiter[0] == '\0')){
	  return NULL;
  }

  if (max_tokens < 1)
    max_tokens = 0x7fffffff;

  remainder = string;
  s = strstr (remainder, delimiter);
  if (s)
    {
      size_t delimiter_len = strlen (delimiter);

      while (--max_tokens && s)
        {
          size_t len;

          len = s - remainder;
          string_list = g_slist_prepend (string_list,
                                         strndup (remainder, len));
          n++;
          remainder = s + delimiter_len;
          s = strstr (remainder, delimiter);
        }
    }
  if (*string)
    {
      n++;
      string_list = g_slist_prepend (string_list, strdup (remainder));
    }

  str_array = (gchar**)malloc (sizeof(gchar*)*(n + 1));

  str_array[n--] = NULL;
  for (GSList = string_list; GSList; GSList = GSList->next)
    str_array[n--] = (gchar*)GSList->data;

  g_slist_free (string_list);

  return str_array;
}

gchar * g_strrstr (const gchar *haystack, const gchar *needle)
{
  size_t i;
  size_t needle_len;
  size_t haystack_len;
  const gchar *p;

  if ((haystack == NULL)||(needle == NULL)){
	  return '\0';
  }

  needle_len = strlen (needle);
  haystack_len = strlen (haystack);

  if (needle_len == 0)
    return (gchar *)haystack;

  if (haystack_len < needle_len)
    return NULL;

  p = haystack + haystack_len - needle_len;

  while (p >= haystack)
    {
      for (i = 0; i < needle_len; i++)
        if (p[i] != needle[i])
          goto next;

      return (gchar *)p;

    next:
      p--;
    }

  return NULL;
}

gchar* g_stpcpy (gchar *dest, const gchar *src)
{
  gchar *d = dest;
  const gchar *s = src;

  if( (dest == NULL)|| (src == NULL) ){
	  return NULL;
  }
  
  do {
    *d++ = *s;
  } while (*s++ != '\0');

  return d - 1;
}

gchar* g_strconcat (const gchar *string1, ...)
{
  size_t   l;
  va_list args;
  gchar   *s;
  gchar   *concat;
  gchar   *ptr;

  if (!string1)
    return NULL;

  l = 1 + strlen (string1);
  va_start (args, string1);
  s = va_arg (args, gchar*);
  while (s)
    {
      l += strlen (s);
      s = va_arg (args, gchar*);
    }
  va_end (args);

  concat = (gchar*)malloc(sizeof(gchar)*l);
  ptr = concat;

  ptr = g_stpcpy (ptr, string1);
  va_start (args, string1);
  s = va_arg (args, gchar*);
  while (s)
    {
      ptr = g_stpcpy (ptr, s);
      s = va_arg (args, gchar*);
    }
  va_end (args);

  return concat;
}


//===================================================

gchar * g_path_get_basename (const gchar *file_name)
{
  long base;
  long last_nonslash;
  size_t len;
  gchar *retval;

  if(file_name == NULL){
	  return NULL;
  }

  if (file_name[0] == '\0')
    return strdup (".");

  last_nonslash = strlen (file_name) - 1;

  while (last_nonslash >= 0 && IS_DIR_SEPARATOR (file_name [last_nonslash]))
    last_nonslash--;

  if (last_nonslash == -1)
    /* string only containing slashes */
    return strdup ("\\");

  base = last_nonslash;

  while (base >=0 && !IS_DIR_SEPARATOR (file_name [base]))
    base--;

  len = last_nonslash - base;
  retval = (gchar*)malloc (len + 1);
  memcpy (retval, file_name + base + 1, len);
  retval [len] = '\0';

  return retval;
}
