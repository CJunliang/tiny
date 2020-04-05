/****************************************************/
/* File: util.h                                     */
/* Utility functions for the TINY compiler          */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 * 过程printToken打印token和它的词素到列表文件
 */
void printToken(TokenType, const char *);

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 * 函数newStmtNode创建用于语法树构建的新语句节点
 */
TreeNode *newStmtNode(StmtKind);

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 * 函数newExpNode创建用于语法树构建的新表达式节点
 */
TreeNode *newExpNode(ExpKind);

/* Function copyString allocates and makes a new
 * copy of an existing string
 * 函数copyString分配并创建现有字符串的新副本
 */
char *copyString(char *);

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 * 过程printTree使用缩进将语法树打印到列表文件中以指示子树
 */
void printTree(TreeNode *);

#endif
