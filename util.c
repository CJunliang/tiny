/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 * 过程printToken将token及其词素打印到列表文件
 */
void printToken(TokenType token, const char *tokenString) {
    switch (token) {
        case TRUE:
        case FALSE:
        case OR:
        case AND:
        case NOT:
        case INT:
        case BOOL:
        case STRING:
        case FLOAT:
        case DOUBLE:
        case DO:
        case WHILE:
        case IF:
        case THEN:
        case ELSE:
        case END:
        case REPEAT:
        case UNTIL:
        case READ:
        case WRITE:
            fprintf(listing, "KEY, value= %s\n", tokenString);
            break;
        case ASSIGN:
        case LT:
        case EQ:
        case LPAREN:
        case RPAREN:
        case SEMI:
        case PLUS:
        case MINUS:
        case TIMES:
        case OVER:
        case MT:
        case LE:
        case ME:
        case COMMA:
        case PERCENT:
            fprintf(listing, "SYM, value= %s\n", tokenString);
            break;
        case ENDFILE:
            fprintf(listing, "EOF");
            if (!StringOver)
                fprintf(listing, ", The line %d of string right quote match error.", StrOrCommentLine);
            if (!CommentOver)
                fprintf(listing, ", The line %d of comment right parenthesis matching error.", StrOrCommentLine);
            fprintf(listing, "\n");
            break;
        case NUM:
            fprintf(listing, "NUM, val= %s\n", tokenString);
            break;
        case ID:
            fprintf(listing, "ID, name= %s\n", tokenString);
            break;
        case ERRORID:
            fprintf(listing, "ID '%s' doesn't conform to format.\n", tokenString);
            break;
        case STR:
            fprintf(listing, "STR, val='%s'\n", tokenString);
            break;
        case ERROR:
            fprintf(listing, "ERROR: %s\n", tokenString);
            break;
        default: /* should never happen */
            fprintf(listing, "Unknown token: %d\n", token);
    }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 * 函数newStmtNode创建用于语法树构建的新语句节点
 */
TreeNode *newStmtNode(StmtKind kind) {
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else {
        for (i = 0; i < MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->kind.stmt = kind;
        t->lineno = lineno;
    }
    return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 * 函数newExpNode创建用于语法树构建的新表达式节点
 */
TreeNode *newExpNode(ExpKind kind) {
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else {
        for (i = 0; i < MAXCHILDREN; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->kind.exp = kind;
        t->lineno = lineno;
        t->type = Void;
    }
    return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 * 函数copyString分配并创建现有字符串的新副本
 */
char *copyString(char *s) {
    int n;
    char *t;
    if (s == NULL)
        return NULL;
    n = strlen(s) + 1;
    t = (char *) malloc(n);
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else
        strcpy(t, s);
    return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 * printTree使用变量indentno来存储要缩进的当前空间数
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
/* 宏以增加/减少缩进 */
#define INDENT indentno += 2
#define UNINDENT indentno -= 2

/* printSpaces indents by printing spaces */
/* printSpaces通过打印空间缩进 */
static void printSpaces(void) {
    int i;
    for (i = 0; i < indentno; i++)
        fprintf(listing, " ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 * 过程printTree使用缩进将语法树打印到列表文件中以指示子树
 */
void printTree(TreeNode *tree) {
    int i;
    INDENT;
    while (tree != NULL) {
        printSpaces();
        if (tree->nodekind == StmtK) {
            switch (tree->kind.stmt) {
                case IfK:
                    fprintf(listing, "If\n");
                    break;
                case RepeatK:
                    fprintf(listing, "Repeat\n");
                    break;
                case AssignK:
                    fprintf(listing, "Assign to: %s\n", tree->attr.name);
                    break;
                case ReadK:
                    fprintf(listing, "Read: %s\n", tree->attr.name);
                    break;
                case WriteK:
                    fprintf(listing, "Write\n");
                    break;
                default:
                    fprintf(listing, "Unknown ExpNode kind\n");
                    break;
            }
        } else if (tree->nodekind == ExpK) {
            switch (tree->kind.exp) {
                case OpK:
                    fprintf(listing, "Op: ");
                    printToken(tree->attr.op, "\0");
                    break;
                case ConstK:
                    fprintf(listing, "Const: %d\n", tree->attr.val);
                    break;
                case IdK:
                    fprintf(listing, "Id: %s\n", tree->attr.name);
                    break;
                default:
                    fprintf(listing, "Unknown ExpNode kind\n");
                    break;
            }
        } else
            fprintf(listing, "Unknown node kind\n");
        for (i = 0; i < MAXCHILDREN; i++)
            printTree(tree->child[i]);
        tree = tree->sibling;
    }
    UNINDENT;
}
