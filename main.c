/****************************************************/
/* File: main.c                                     */
/* Main program for TINY compiler                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
/* 将NO_PARSE设置为TRUE可获得仅扫描程序的编译器 */
#define NO_PARSE true
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
/* 将NO_ANALYZE设置为TRUE可获得仅解析器的编译器 */
#define NO_ANALYZE true

/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 * 将NO_CODE设置为TRUE可获得不生成代码的编译器
 */
#define NO_CODE false

#include "util.c"
#include "scan.c"

/* allocate global variables */
/* 分配全局变量 */
int lineno = 0;
int CommentLine = 0;
int StringLine = 0;
FILE *source;
FILE *listing;
FILE *code;

/* allocate and set tracing flags */
/* 分配和设置跟踪标志 */
bool EchoSource = true;
bool TraceScan = true;
bool TraceParse = true;
bool TraceAnalyze = false;
bool TraceCode = false;

bool Error = false;

/*分配和设置string和comment的标志*/
bool StringOver = true;
bool CommentOver = true;
bool StringStraddle = false;
bool separate = false;

int main(int argc, char *argv[]) {
    TreeNode *syntaxTree;
    char pgm[120]; /* source code file name */
    /* 参数必须有两个 */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    strcpy(pgm, argv[1]);
    /* strchr 在pgm中寻找第一个出现.的位置 */
    if (strchr(pgm, '.') == NULL)
        strcat(pgm, ".tny");
    source = fopen(pgm, "r");
    if (source == NULL) {
        fprintf(stderr, "File %s not found\n", pgm);
        exit(1);
    }
    /* stdout是一个标准输出流 */
    listing = stdout; /* send listing to screen */
    fprintf(listing, "\nTINY COMPILATION: %s\n\n", pgm);

    while (getToken() != ENDFILE);

    fclose(source);
//    system("pause");
    return 0;
}
