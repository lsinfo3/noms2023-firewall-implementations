/* picoc external interface. This should be the only header you need to use if
 * you're using picoc as a library. Internal details are in interpreter.h */
#ifndef PICOC_H
#define PICOC_H

#include <stdio.h>

/* picoc version number */
#ifdef VER
#define PICOC_VERSION "v2.2 beta r" VER         /* VER is the subversion version number, obtained via the Makefile */
#else
#define PICOC_VERSION "v2.2"
#endif

/* handy definitions */
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

struct Picoc_Struct;
typedef struct Picoc_Struct Picoc;

/* parse.c */
void PicocParse(Picoc *pc, const char *FileName, const char *Source, int SourceLen, int RunIt, int CleanupNow, int CleanupSource, int EnableDebugger);
void PicocParseInteractive(Picoc *pc);

/* platform.c */
int PicocEntry(FILE *istream, FILE *ostream, const char *filename, const char *plugin_dir);
void PicocCallMain(Picoc *pc, int argc, char **argv);
void PicocInitialise(Picoc *pc, int StackSize, FILE *istream, FILE *ostream, const char *plugin_dir);
void PicocCleanup(Picoc *pc);
void PicocPlatformScanFile(Picoc *pc, const char *FileName, int is_include, int allow_failure);

/* include.c */
void PicocIncludeAllSystemHeaders(Picoc *pc);

#endif /* PICOC_H */
