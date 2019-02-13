/*
** Copyright (C) 2002 Martin Roesch <roesch@sourcefire.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/


/*
**   ACSMX.H 
**
**
*/
#ifndef ACSMX_H
#define ACSMX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*   Prototypes
*/
#define ALPHABET_SIZE    256    	//字母表大小 
#define MAXLEN 256					//最大长度

#define ACSM_FAIL_STATE   -1     	//fail指针初始状态

typedef struct _acsm_pattern {      

	struct  _acsm_pattern *next;			//链表下一个节点
	unsigned char         *patrn;			//转换为大写字符模式串
	unsigned char         *casepatrn;		//区分大小写模式字符串
	int      n;								//模式串长度
	int      nocase;						//大小写敏感标志
	void   	 *id;
	int		 nmatch;

} ACSM_PATTERN;

//状态机表
typedef struct  {    

	/* Next state - based on input character */
	int      NextState[ ALPHABET_SIZE ];  

	/* Failure state - used while building NFA & DFA  */
	int      FailState;   

	/* List of patterns that end here, if any */
	ACSM_PATTERN *MatchList;   

}ACSM_STATETABLE; 


/*
* State machine Struct
*/
typedef struct {

	int acsmMaxStates;  						//状态机最大状态数
	int acsmNumStates;  						//状态机实际状态数

	ACSM_PATTERN    * acsmPatterns;				//模式串链表	
	ACSM_STATETABLE * acsmStateTable;			//状态表

}ACSM_STRUCT;

/*
*   Prototypes 原型
*/
ACSM_STRUCT * acsmNew ();
int acsmAddPattern( ACSM_STRUCT * p, unsigned char * pat, int n,int nocase);
int acsmCompile ( ACSM_STRUCT * acsm );
//int acsmSearch ( ACSM_STRUCT * acsm,unsigned char * T, int n, int (*Match) (ACSM_PATTERN * pattern,ACSM_PATTERN * mlist, int nline,int index));
int acsmSearch (ACSM_STRUCT * acsm, unsigned char *Tx, int n,void (*PrintMatch) (ACSM_PATTERN * pattern,ACSM_PATTERN * mlist, int nline,int index));
void acsmFree ( ACSM_STRUCT * acsm );
void PrintMatch (ACSM_PATTERN * pattern,ACSM_PATTERN * mlist, int nline,int index) ;
void PrintSummary (ACSM_PATTERN * pattern) ;

#endif
