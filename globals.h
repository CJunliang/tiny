/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//#ifndef FALSE
//#define FALSE 0
//#endif
//
//#ifndef TRUE
//#define TRUE 1
//#endif

/* MAXRESERVED = the number of reserved words */
/* 保留字/关键字的数量 */
#define MAXRESERVED 20

/* typedef 为类型取一个新的名字 */
/* enum 枚举 */
/* typedef enum 用typedef关键字将枚举类型定义成别名，并利用该别名进行变量声明 */
typedef enum
/* book-keeping tokens */
{
    ENDFILE,
    ERROR,
    /* reserved words */
    IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,
    TRUE,FALSE,OR,AND,NOT,INT,BOOL,STRING,FLOAT,DOUBLE,DO,WHILE,
    /* multicharacter tokens */
    ID,
    NUM,
    STR,
    /* special symbols */
    ASSIGN,    /* := */
    EQ,        /* = */
    LT,        /* < */
    PLUS,      /* + */
    MINUS,     /* - */
    TIMES,     /* * */
    OVER,      /* / */
    LPAREN,    /* ( */
    RPAREN,    /* ) */
    SEMI,      /* ; */
    MT,        /* > */
    LE,        /* <= */
    ME,        /* >= */
    COMMA,     /* , */
    QUOTATION, /* ' */
    PERCENT    /* % */
} TokenType;

/* extern 在一个文件中引用另一个文件中定义的变量或者函数 */
/* 一下4个变量都在mian.c定义 */
extern FILE *source;  /* source code text file */
extern FILE *listing; /* listing output text file */
extern FILE *code; /* code text file for TM simulator */

extern int lineno;      /* source line number for listing */
extern int CommentLine; /*指示comment的行数*/
extern int StringLine;  /*指示string的函数*/

/**************************************************/
/***********   Syntax tree for parsing ************/
/***********          语法树解析        ************/
/**************************************************/

typedef enum
{
    StmtK,
    ExpK
} NodeKind;
typedef enum
{
    IfK,
    RepeatK,
    AssignK,
    ReadK,
    WriteK
} StmtKind;
typedef enum
{
    OpK,
    ConstK,
    IdK
} ExpKind;

/* ExpType is used for type checking */
/* ExpType用于类型检查 */
typedef enum
{
    Void,
    Integer,
    Boolean
} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
{
    struct treeNode *child[MAXCHILDREN];
    struct treeNode *sibling; /* 兄弟 */
    int lineno;
    NodeKind nodekind;
    union
    {
        StmtKind stmt;
        ExpKind exp;
    } kind;
    union
    {
        TokenType op;
        int val;
        char *name;
    } attr;
    ExpType type; /* for type checking of exps */
} TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/***********          跟踪标志          ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 * EchoSource = TRUE导致源程序在解析过程中以行号回显到列表文件
 */
extern bool EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 * TraceScan = TRUE会导致token信息被打印到列表文件中，因为扫描器可以识别每个token
 */
extern bool TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 * TraceParse = TRUE导致语法树以线性化形式打印到列表文件（对children使用缩进）
 */
extern bool TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 * TraceAnalyze = TRUE导致将符号表插入和查找报告给列表文件
 */
extern bool TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 * TraceCode = TRUE导致在生成代码时将注释写入TM代码文件
 */
extern bool TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern bool Error;

/*true指示string和comment闭合*/
extern bool StringOver;
extern bool CommentOver;
/*True指示string跨行*/
extern bool StringStraddle;
/*true指示id，num和keyword之间有空白符*/
extern bool separate;
#endif
