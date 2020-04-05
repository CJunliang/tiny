/****************************************************/
/* File: scan.h                                     */
/* The scanner interface for the TINY compiler      */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_

/* MAXTOKENLEN is the maximum size of a token */
/* token的最大数目 */
#define MAXTOKENLEN 255

/* tokenString array stores the lexeme of each token */
/* tokenString数组存储每个token的词素 */
extern char tokenString[MAXTOKENLEN + 1];

/* function getToken returns the 
 * next token in source file
 * 函数getToken返回源文件中的下一个token
 */
TokenType getToken(void);

#endif
