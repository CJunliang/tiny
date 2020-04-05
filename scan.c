/****************************************************/
/* File: scan.c                                     */
/* The scanner implementation for the TINY compiler */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"

/* states in scanner DFA */
typedef enum {
    START,
    INASSIGN,  /* 分配 */
    INCOMMENT, /* 注释 */
    INNUM,       /* 数字 */
    INSTRING,   /*string*/
    INID,       /* ID */
    INME,       /*大于*/
    INLE,       /*小于*/
    DONE
} StateType;

/* lexeme of identifier or reserved word */
/* 标识符或保留字的词素 */
char tokenString[MAXTOKENLEN + 1];

/* BUFLEN = length of the input buffer for
   source code lines */
/* BUFLEN =源代码行的输入缓冲区的长度 */
#define BUFLEN 256

static char lineBuf[BUFLEN]; /* holds the current line */
static int linepos = 0;         /* current position in LineBuf */
static int bufsize = 0;         /* current size of buffer string */
static bool EOF_flag = false; /* corrects ungetNextChar behavior on EOF 纠正了EOF上的ungetNextChar行为*/

/* getNextChar fetches the next non-blank character
   from lineBuf, reading in a new line if lineBuf is
   exhausted */
/* getNextChar从lineBuf获取下一个非空白字符，如果用完lineBuf则换行 */
static int getNextChar(void) {
    if (!(linepos < bufsize)) {
        /* 行号 */
        lineno++;
        /* fgets会读取到第一个换行符/文件末尾/缓冲区最大长度少一个字符 */
        if (fgets(lineBuf, BUFLEN - 1, source)) {
            if (EchoSource)
                fprintf(listing, "%d: %s", lineno, lineBuf);
            bufsize = strlen(lineBuf);
            linepos = 0;
            return lineBuf[linepos++];
        } else {
            EOF_flag = true;
            return EOF;
        }
    } else
        return lineBuf[linepos++];
}

/* ungetNextChar backtracks one character
   in lineBuf */
/* ungetNextChar在lineBuf中回溯一个字符 */
static void ungetNextChar(void) {
    if (!EOF_flag)
        linepos--;
}

/* lookup table of reserved words */
/* 保留字查询表 */
static struct {
    char *str;
    TokenType tok;
} reservedWords[MAXRESERVED] = {
        {"if",     IF},
        {"then",   THEN},
        {"else",   ELSE},
        {"end",    END},
        {"repeat", REPEAT},
        {"until",  UNTIL},
        {"read",   READ},
        {"write",  WRITE},
        /* add reserved words */
        {"true",   TRUE},
        {"false",  FALSE},
        {"or",     OR},
        {"and",    AND},
        {"not",    NOT},
        {"int",    INT},
        {"bool",   BOOL},
        {"string", STRING},
        {"float",  FLOAT},
        {"double", DOUBLE},
        {"do",     DO},
        {"while",  WHILE}};

/* lookup an identifier to see if it is a reserved word */
/* 查找标识符以查看它是否为保留字，不是表明它是ID */
/* uses linear search */
/* 使用线性搜索 */
static TokenType reservedLookup(char *s) {
    int i;
    for (i = 0; i < MAXRESERVED; i++)
        if (!strcmp(s, reservedWords[i].str))
            return reservedWords[i].tok;
    return ID;
}

/*检验ID是否符合要求*/
static TokenType IDFormatLookup(char *s) {
    int i;
    /*ID从第二个字符开始范围是0-9a-zA-Z*/
    for (int i = 1; i < strlen(s); i++) {
        char c = s[i];
        if (!(isalpha(c) || isdigit(c)))
            return ERRORID;
    }
    return ID;
}
/****************************************/
/* the primary function of the scanner  */
/****************************************/
/* function getToken returns the 
 * next token in source file
 * 函数getToken返回源文件中的下一个token
 */
TokenType getToken(void) { /* index for storing into tokenString */
    int tokenStringIndex = 0;
    /* holds current token to be returned */
    TokenType currentToken;
    /* current state - always begins at START */
    StateType state = START;
    /* flag to indicate save to tokenString */
    /* 指示保存到tokenString的标志，即是否保存该字符 */
    bool save;
    /* state一定要转到done才结束 */
    while (state != DONE) {
        int c = getNextChar();
        char ch = (char) c;
        save = true;
        /* 查看状态转换图 */
        switch (state) {
            case START:
                if (isdigit(c))
                    state = INNUM;
                    /* isalpha判断是否是英文字母 */
                else if (isalpha(c))
                    state = INID;
                else if (c == ':')
                    state = INASSIGN;
                else if (c == '>')
                    state = INME;
                else if (c == '<')
                    state = INLE;
                else if ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r'))
                    save = false;
                else if (c == '{') {
                    save = false;
                    state = INCOMMENT;
                } else if (c == '\'') {
                    save = false;
                    state = INSTRING;
                    currentToken = STR;
                } else {
                    /* other */
                    state = DONE;
                    switch (c) {
                        case EOF:
                            save = false;
                            currentToken = ENDFILE;
                            break;
                        case '=':
                            currentToken = EQ;
                            break;
                        case '+':
                            currentToken = PLUS;
                            break;
                        case '-':
                            currentToken = MINUS;
                            break;
                        case '*':
                            currentToken = TIMES;
                            break;
                        case '/':
                            currentToken = OVER;
                            break;
                        case '(':
                            currentToken = LPAREN;
                            break;
                        case ')':
                            currentToken = RPAREN;
                            break;
                        case ';':
                            currentToken = SEMI;
                            break;
                        case ',':
                            currentToken = COMMA;
                            break;
                        case '%':
                            currentToken = PERCENT;
                            break;
                        default:
                            /* 不识别其他字符 */
                            currentToken = ERROR;
                            break;
                    }
                }
                break;
            case INCOMMENT:
                /* 注释 */
                save = false;
                if (c == EOF) {
                    state = DONE;
                    currentToken = ENDFILE;
                } else if (c == '}')
                    state = START;
                break;
            case INSTRING:
                if (c == '\'') {
                    save = false;
                    state = DONE;
                }
                break;
            case INASSIGN:
                state = DONE;
                if (c == '=')
                    currentToken = ASSIGN;
                else { /* backup in the input 在输入中备份，:=要连续*/
                    /* ungetNextChar在lineBuf中回溯一个字符 */
                    ungetNextChar();
                    save = false;
                    currentToken = ERROR;
                }
                break;
            case INLE:
                state = DONE;
                if (c == '=')
                    currentToken = LE;
                else {
                    ungetNextChar();
                    save = false;
                    currentToken = LT;
                }
                break;
            case INME:
                state = DONE;
                if (c == '=')
                    currentToken = ME;
                else {
                    ungetNextChar();
                    save = false;
                    currentToken = MT;
                }
                break;
            case INNUM:
                if (!isdigit(c)) { /* backup in the input */
                    ungetNextChar();
                    save = false;
                    state = DONE;
                    currentToken = NUM;
                }
                break;
            case INID:
                if (!(isalpha(c) || isdigit(c))) { /* backup in the input */
                    ungetNextChar();
                    save = false;
                    state = DONE;
                    currentToken = ID;
                }
                break;
            case DONE:
            default: /* should never happen */
                fprintf(listing, "Scanner Bug: state= %d\n", state);
                state = DONE;
                currentToken = ERROR;
                break;
        }
        if ((save) && (tokenStringIndex <= MAXTOKENLEN))
            tokenString[tokenStringIndex++] = (char) c;
        if (state == DONE) {
            tokenString[tokenStringIndex] = '\0';
            /*检验是否是关键字*/
            if (currentToken == ID)
                currentToken = reservedLookup(tokenString);
            /*检验ID是否符合要求*/
            if (currentToken == ID)
                currentToken = IDFormatLookup(tokenString);
        }
    }
    if (TraceScan) {
        fprintf(listing, "\t%d: ", lineno);
        printToken(currentToken, tokenString);
    }
    return currentToken;
} /* end getToken */
