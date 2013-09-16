#pragma	    once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#ifndef BOOL
#define BOOL int
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#define ASSERT(x) assert(x)

extern int lineno;//line number of source code
extern FILE *sourceFile;
extern FILE *targetFile;//the file generated code stored

typedef enum 
{
	kEndFile = 0,
	kError,
	kID ,
	kNumber,
	//keywords
	kIf,
	kElse,
	kInt,
	kReturn,
	kVoid,
	kWhile,
	//Special sign
	kPlus,
	kMinus,
	kMul,
	kDiv,
	kLT,
	kLE,
	kGT,
	kGE,
	kEQ,
	kNE,
	kAssign,
	kSemicolon,
	kComma,//,
	kLParen,//(
	kRParen,//)
	kLMParen,//[
	kRMParen,//]
	kLBParen,//{
	kRBParen,//}
	kBoolean,//currently this token is not in source file.I just added it for type checking
}TokenType;
static struct
{
	TokenType token;
	const char* str;
}g_token2String[] =
{ 
	{kEndFile, "EOF"},
	{kError, "Error"},
	{kID ,       " "},
	{kNumber,    " "},
	{kIf,       "If"},
	{kElse,   "else"},
	{kInt,     "int"},
	{kReturn, "return"},
	{kVoid,"void"},
	{kWhile,"while"},
	{kPlus,"+"},
	{kMinus,"-"},
	{kMul,"*"},
	{kDiv,"/"},
	{kLT,"<"},
	{kGT,">"},
	{kEQ,"=="},
	{kNE,"!="},
	{kAssign,"="},
	{kSemicolon,";"},
	{kComma,","},
	{kLParen,"{"},
	{kLParen,"("},
	{kRParen,")"},
	{kLMParen,"["},
	{kRMParen,"]"},
	{kLBParen,"{"},//{
	{kRBParen,"}"},//}
	{kBoolean,"bool"},//currentl
};

typedef enum { kVarDeclaration,kFunDeclaration,kParam,kStmt,kExp} NodeKind;
typedef enum {kIfStmt,kWhileStmt,kReturnStmt,kCallStmt/*the function call*/} StmtKind;
typedef enum {kConstExp,kOpExp,kIDExp} ExpKind;



#define MAXCHILDREN 3
typedef struct treeNode
{
	struct treeNode *child[MAXCHILDREN];
	struct treeNode *sibling;
	int lineno;
	NodeKind nodeKind;
	union 
	{
		StmtKind stmt; ExpKind exp;
	}kind;
	union 
	{
		TokenType op;
		int val;
		char *name;
	}attr;
	BOOL bIsArray;
	int iArraySize ;
	TokenType type;
	char* scope;//the scope is generated by  the scope string,like function name
	//int place;//for the nonterminal node
	BOOL bIsAlreadyGenereated;//only useful for args because p code's args sequences are different from x86.
}TreeNode;

//////////////////////////////////////////////////////////////////////////
//The following has function used both by parser and symbol table
/////////////////////////////////////////////////////////////////////////
#define GLOBALSCOPE  "1_Global"//this string shouldn't be  appeared in source code.
#define MAINFUNCTION  "main"//in this language .only one main function exists
#define INPUTFUNTION "input"
#define OUTPUTFUNCTION "output"

