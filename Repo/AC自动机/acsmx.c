/*
**
** Multi-Pattern Search Engine
**
** Aho-Corasick State Machine -  uses a Deterministic Finite Automata - DFA
**
** Copyright (C) 2002 Sourcefire,Inc.
** Marc Norton
**
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
**
**
**   Reference - Efficient String matching: An Aid to Bibliographic Search
**               Alfred V Aho and Margaret J Corasick
**               Bell Labratories 
**               Copyright(C) 1975 Association for Computing Machinery,Inc
**
**   Implemented from the 4 algorithms in the paper by Aho & Corasick
**   and some implementation ideas from 'Practical Algorithms in C'
**
**   Notes:
**     1) This version uses about 1024 bytes per pattern character - heavy  on the memory. 
**     2) This algorithm finds all occurrences of all patterns within a  
**        body of text.
**     3) Support is included to handle upper and lower case matching.     
**     4) Some comopilers optimize the search routine well, others don't, this makes all the difference.
**     5) Aho inspects all bytes of the search text, but only once so it's very efficient,
**        if the patterns are all large than the Modified Wu-Manbar method is often faster.
**     6) I don't subscribe to any one method is best for all searching needs,
**        the data decides which method is best,
**        and we don't know until after the search method has been tested on the specific data sets.
**        
**
**  May 2002  : Marc Norton 1st Version  
**  June 2002 : Modified interface for SNORT, added case support
**  Aug 2002  : Cleaned up comments, and removed dead code.
**  Nov 2,2002: Fixed queue_init() , added count=0
**              
**  Wangyao : wangyao@cs.hit.edu.cn
**
**  Apr 24,2007: WangYao Combined Build_NFA() and Convert_NFA_To_DFA() into Build_DFA();
**				 And Delete Some redundancy Code 
**	
*/  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "acsmx.h"

//打印信息宏
#define MEMASSERT(p,s) if(!p){fprintf(stderr,"ACSM-No Memory: %s!\n",s);exit(0);}

/*Define the number of the line,when match a keyword*/
extern int nline = 1;

/*
* Malloc the AC Memory
* 封装的malloc函数
*/ 
static void *AC_MALLOC (int n) 
{
	void *p;
	p = malloc (n);

	return p;
}

/*
*Free the AC Memory
*封装的free函数
*/ 
static void AC_FREE (void *p) 
{
	if (p)
		free (p);
}


/*
*Simple QUEUE NODE
*队列节点
*/ 
typedef struct _qnode
{
	int state;					//????????
	struct _qnode *next;
}QNODE;

/*
*Simple QUEUE Structure
*队列结构，队列头，尾指针
*/ 
typedef struct _queue
{
	QNODE * head, *tail;
	int count;				//队列里成员数量
}QUEUE;

/*
*Init the Queue
*初始化队列
*/ 
static void queue_init (QUEUE *s) 
{
	s->head = s->tail = 0;
	s->count = 0;
}


/*
*  Add Tail Item to queue
*  队尾添加成员
*/ 
static void queue_add (QUEUE *s, int state) 
{
	QNODE *q;
	/*Queue is empty*/
	if (!s->head)
	{
		q = s->tail = s->head = (QNODE *) AC_MALLOC (sizeof (QNODE));
		/*if malloc failed,exit the problom*/
		MEMASSERT (q, "queue_add");
		q->state = state;
		q->next = 0; /*Set the New Node's Next Null*/
	}
	else
	{
		q = (QNODE *) AC_MALLOC (sizeof (QNODE));
		MEMASSERT (q, "queue_add");
		q->state = state;								//????????????
		q->next = 0;
		/*Add the new Node into the queue*/
		s->tail->next = q;
		/*set the new node is the Queue's Tail*/
		s->tail = q;
	}
	s->count++;
}


/*
*  Remove Head Item from queue
*  队列头弹出成员
*/ 
static int queue_remove (QUEUE * s) 
{
	int state = 0;
	QNODE * q;
	/*Remove A QueueNode From the head of the Queue*/
	if (s->head)
	{
		q = s->head;
		state = q->state;
		s->head = s->head->next;
		s->count--;

		/*If Queue is Empty,After Remove A QueueNode*/
		if (!s->head)
		{
			s->tail = 0;
			s->count = 0;
		}
		/*Free the QueNode Memory*/
		AC_FREE (q);
	}
	return state;
}


/*
*Return The count of the Node in the Queue
*返回队列中成员总数
*/ 
static int queue_count (QUEUE * s) 
{
	return s->count;
}


/*
*Free the Queue Memory
*释放队列结构
*/ 
static void queue_free (QUEUE * s) 
{
	while (queue_count (s))
	{
		queue_remove (s);
	}
}


/*
** Case Translation Table 
** 翻译表
*/ 
static unsigned char xlatcase[256];

/*
* Init the xlatcase Table,Trans alpha to UpperMode
* Just for the NoCase State
* 初始化翻译表，将字母统一转换为大写模式
* 为了不区分大小写模式
*/ 
static void init_xlatcase () 
{
	int i;
	for (i = 0; i < 256; i++)
	{
		xlatcase[i] = toupper (i);
	}
}

/*
*Convert the pattern string into upper
*将模式字符串转换为大写字母
*/ 
static void ConvertCaseEx (unsigned char *d, unsigned char *s, int m) 
{
	int i;
	for (i = 0; i < m; i++)
	{
		d[i] = xlatcase[s[i]];
	}
}

/*
*  Add a pattern to the list of patterns terminated at this state.
*  Insert at front of list.	头插法
*/ 
static void AddMatchListEntry (ACSM_STRUCT * acsm, int state, ACSM_PATTERN * px) 
{
	ACSM_PATTERN * p;
	p = (ACSM_PATTERN *) AC_MALLOC (sizeof (ACSM_PATTERN));
	MEMASSERT (p, "AddMatchListEntry");
	memcpy (p, px, sizeof (ACSM_PATTERN));

	/*Add the new pattern to the pattern  list*/
	p->next = acsm->acsmStateTable[state].MatchList;
	acsm->acsmStateTable[state].MatchList = p;
}

/* 
* Add Pattern States
* 将字符串链表里的字符串构造成字典树
*/ 
static void AddPatternStates (ACSM_STRUCT * acsm, ACSM_PATTERN * p) 
{
	unsigned char *pattern;
	int state = 0, next, n;
	n = p->n; 								/*The number of alpha in the pattern string*/
	pattern = p->patrn;

	/* 
	*  Match up pattern with existing states
	*/ 
	for (; n > 0; pattern++, n--)
	{
		next = acsm->acsmStateTable[state].NextState[*pattern];
		if (next == ACSM_FAIL_STATE)
			break;
		state = next;
	}

	/*
	*   Add new states for the rest of the pattern bytes, 1 state per byte
	*/ 
	for (; n > 0; pattern++, n--)
	{
		acsm->acsmNumStates++;
		acsm->acsmStateTable[state].NextState[*pattern] = acsm->acsmNumStates;
		state = acsm->acsmNumStates;
	}
	/*Here,An accept state,just add into the MatchListof the state*/
	AddMatchListEntry (acsm, state, p);
}


/*
*   Build Non-Deterministic Finite Automata
*   bfs算法，构建fail指针
*/ 
static void Build_DFA (ACSM_STRUCT * acsm) 
{
	int r, s;
	int i;
	QUEUE q, *queue = &q;
	ACSM_PATTERN * mlist=0;
	ACSM_PATTERN * px=0;

	/* Init a Queue 创建一个队列*/ 
	queue_init (queue);

	/* Add the state 0 transitions 1st */
	/*1st depth Node's FailState is 0, fail(x)=0 */
	for (i = 0; i < ALPHABET_SIZE; i++)
	{
		s = acsm->acsmStateTable[0].NextState[i];
		if (s)
		{
			queue_add (queue, s);
			acsm->acsmStateTable[s].FailState = 0;
		}
	}

	/* Build the fail state transitions for each valid state */ 
	while (queue_count (queue) > 0)
	{
		r = queue_remove (queue);

		/* Find Final States for any Failure */ 
		for (i = 0; i < ALPHABET_SIZE; i++)
		{
			int fs, next;
			/*** Note NextState[i] is a const variable in this block ***/
			if ((s = acsm->acsmStateTable[r].NextState[i]) != ACSM_FAIL_STATE)
			{
				queue_add (queue, s);
				fs = acsm->acsmStateTable[r].FailState;

				/* 
				*  Locate the next valid state for 'i' starting at s 
				*/ 
				/**** Note the  variable "next" ****/
				/*** Note "NextState[i]" is a const variable in this block ***/
				while ((next=acsm->acsmStateTable[fs].NextState[i]) ==
					ACSM_FAIL_STATE)
				{
					fs = acsm->acsmStateTable[fs].FailState;
				}

				/*
				*  Update 's' state failure state to point to the next valid state
				*/ 
				acsm->acsmStateTable[s].FailState = next;
			}
			else
			{
				acsm->acsmStateTable[r].NextState[i] =
					acsm->acsmStateTable[acsm->acsmStateTable[r].FailState].NextState[i];
			}
		}
	}

	/* Clean up the queue */ 
	queue_free (queue);
}


/*
* Init the acsm DataStruct
* 创建一个自动机结构体
*/ 
ACSM_STRUCT * acsmNew () 
{
	ACSM_STRUCT *p;
	init_xlatcase ();
	p = (ACSM_STRUCT *) AC_MALLOC (sizeof (ACSM_STRUCT));
	MEMASSERT (p, "acsmNew");
	if (p)
		memset (p, 0, sizeof (ACSM_STRUCT));
	return p;
}


/*
*   Add a pattern to the list of patterns for this state machine
*   添加构造字典树的到字符串到字符串链表
*/ 
int acsmAddPattern (ACSM_STRUCT * p, unsigned char *pat, int n, int nocase) 
{
	ACSM_PATTERN * plist;
	plist = (ACSM_PATTERN *) AC_MALLOC (sizeof (ACSM_PATTERN));
	MEMASSERT (plist, "acsmAddPattern");
	plist->patrn = (unsigned char *) AC_MALLOC (n+1);
	memset(plist->patrn+n,0,1);
	ConvertCaseEx (plist->patrn, pat, n);
	plist->casepatrn = (unsigned char *) AC_MALLOC (n+1);
	memset(plist->casepatrn+n,0,1);
	memcpy (plist->casepatrn, pat, n);
	plist->n = n;
	plist->nocase = nocase;
	plist->nmatch=0;							//???????????

	/*Add the pattern into the pattern list*/
	/*头插法，将字符串信息链表添加到自动机相对应的结构体*/
	plist->next = p->acsmPatterns;
	p->acsmPatterns = plist;

	return 0;
}

/*
*   Compile State Machine
*   编译状态机
*/ 
int acsmCompile (ACSM_STRUCT * acsm) 
{
	int i, k;
	ACSM_PATTERN * plist;

	/* Count number of states */ 
	acsm->acsmMaxStates = 1; 						/*State 0*/
	for (plist = acsm->acsmPatterns; plist != NULL; plist = plist->next)
	{
		/*将每个字符串的长度加起来*/
		acsm->acsmMaxStates += plist->n;
	}

	acsm->acsmStateTable = (ACSM_STATETABLE *) AC_MALLOC (sizeof (ACSM_STATETABLE) * acsm->acsmMaxStates);
	MEMASSERT (acsm->acsmStateTable, "acsmCompile");
	memset (acsm->acsmStateTable, 0,sizeof (ACSM_STATETABLE) * acsm->acsmMaxStates);

	/* Initialize state zero as a branch */ 
	acsm->acsmNumStates = 0;

	/* Initialize all States NextStates to FAILED */ 
	for (k = 0; k < acsm->acsmMaxStates; k++)
	{
		for (i = 0; i < ALPHABET_SIZE; i++)		//ALPHABET == 256
		{
			acsm->acsmStateTable[k].NextState[i] = ACSM_FAIL_STATE;  //ACSM_FAIL_STATE == -1 
		}
	}

	/* This is very import */
	/* Add each Pattern to the State Table */ 
	for (plist = acsm->acsmPatterns; plist != NULL; plist = plist->next)
	{
		/*将字符串链表里的字符串构造成字典树*/
		AddPatternStates (acsm, plist);
	}

	/* Set all failed state transitions which from state 0 to return to the 0'th state */ 
	for (i = 0; i < ALPHABET_SIZE; i++)
	{
		if (acsm->acsmStateTable[0].NextState[i] == ACSM_FAIL_STATE)
		{
			acsm->acsmStateTable[0].NextState[i] = 0;
		}
	}

	/* Build the NFA  */ 
	Build_DFA (acsm);

	return 0;
}


/*64KB Memory*/
static unsigned char Tc[64*1024];

/*
*   Search Text or Binary Data for Pattern matches
*   自动机匹配过程
*/ 
int acsmSearch (ACSM_STRUCT * acsm, unsigned char *Tx, int n,void (*PrintMatch) (ACSM_PATTERN * pattern,ACSM_PATTERN * mlist, int nline,int index)) 
{
	int state;
	ACSM_PATTERN * mlist;
	unsigned char *Tend;
	ACSM_STATETABLE * StateTable = acsm->acsmStateTable;
	int nfound = 0; /*Number of the found(matched) patten string*/
	unsigned char *T;
	int index;

	/* Case conversion */ 
	ConvertCaseEx (Tc, Tx, n);
	T = Tc;
	Tend = T + n;

	for (state = 0; T < Tend; T++)
	{
		state = StateTable[state].NextState[*T];

		/* State is a accept state? */
		if( StateTable[state].MatchList != NULL )
		{
			for( mlist=StateTable[state].MatchList; mlist!=NULL;
				mlist=mlist->next )
			{
				/*Get the index  of the Match Pattern String in  the Text*/
				index = T - mlist->n + 1 - Tc;

				//mlist->nmatch++;
				nfound++;
				PrintMatch (acsm->acsmPatterns,mlist, nline,index);
			}
		}
	}

	return nfound;
}


/*
*   Free all memory
*   释放自动机结构
*/ 
void acsmFree (ACSM_STRUCT * acsm) 
{
	int i;
	ACSM_PATTERN * mlist, *ilist;
	for (i = 0; i < acsm->acsmMaxStates; i++)

	{
		if (acsm->acsmStateTable[i].MatchList != NULL)

		{
			mlist = acsm->acsmStateTable[i].MatchList;
			while (mlist)
			{
				ilist = mlist;
				mlist = mlist->next;
				AC_FREE (ilist);
			}
		}
	}
	AC_FREE (acsm->acsmStateTable);
}

/* 
*   Print A Match String's Information
*   打印匹配字符串信息
*/ 
void PrintMatch (ACSM_PATTERN * pattern,ACSM_PATTERN * mlist, int nline,int index) 
{
	/* Count the Each Match Pattern */
	ACSM_PATTERN *temp = pattern;
	for (;temp!=NULL;temp=temp->next)
	{
		if (!strcmp(temp->patrn,mlist->patrn)) //strcmp succeed return 0,So here use "!" operation
		{
			temp->nmatch++;
		}
		
	}
	
	if(mlist->nocase)
		fprintf (stdout, "Match KeyWord %s at %d line %d char\n", mlist->patrn,nline,index);
	else
		fprintf (stdout, "Match KeyWord %s at %d line %d char\n", mlist->casepatrn,nline,index);

}

/*
* Print Summary Information of the AC Match
*/
void PrintSummary (ACSM_PATTERN * pattern)
{	
	ACSM_PATTERN * mlist = pattern;
	printf("\n### Summary ###\n");
	for (;mlist!=NULL;mlist=mlist->next)
	{
		if(mlist->nocase)
			printf("%12s : %5d\n",mlist->patrn,mlist->nmatch);
		else
			printf("%12s : %5d\n",mlist->casepatrn,mlist->nmatch);
	}
}
