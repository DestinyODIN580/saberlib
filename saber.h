#ifndef SABER_H
#define SABER_H 1

#define True 1
#define False 0

/* type conversion */
extern char *dtob (int);
extern char *dtoh (int);
extern int stoi (char *);

/* string manipulation */
extern char *strstdin (const int);
extern char *strsost (char *, char *, char *);
extern char *revstr (char *);
extern struct info *strinfo (char *);
extern char *strupper (char *);
extern char *strlower (char *);
extern char *strtrim (char *);
extern char **strmatdiv (char *);
#endif

#ifndef STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#endif

#ifndef STRING_H
#include <string.h>
#endif

#ifndef STDARG_H
#include <stdarg.h>
#endif

#ifndef CTYPE_H
#include <ctype.h>
#endif
