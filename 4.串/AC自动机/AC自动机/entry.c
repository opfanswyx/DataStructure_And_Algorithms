/*
Author: Atticus
Email: opfanswyx@outlook.com
*/
#include "acsmx.h"

/*
*  Text Data Buffer
*/ 
unsigned char text[MAXLEN];
extern int nline;

int main (int argc, char **argv) 
{
	int i, nocase = 0;
	FILE *fd;
	char filename[20];
	ACSM_STRUCT * acsm;

	if (argc < 3)
	{
		fprintf (stderr,"Usage: acsmx filename pattern1 pattern2 ...  -nocase\n");
		exit (0);
	}

	acsm = acsmNew ();

	strcpy (filename, argv[1]);					//获取文件名

	fd = fopen(filename,"r");					//打开文件
	if(fd == NULL)
	{
		fprintf(stderr,"Open file error!\n");
		exit(1);
	}

	//选择是否大小写敏感
	for (i = 1; i < argc; i++)
		if (strcmp (argv[i], "-nocase") == 0)
			nocase = 1;
	
	for (i = 2; i < argc; i++)
	{
		if (argv[i][0] == '-')
			continue;
		/*将命令行上得非'-'开头的字符串作为自动机字典树构造来源*/
		acsmAddPattern (acsm, argv[i], strlen (argv[i]), nocase);
	}

	/* Generate GtoTo Table and Fail Table */
	acsmCompile (acsm);

	/*Search Pattern*/
	while ( fgets(text,MAXLEN,fd) )
	{
		acsmSearch (acsm, text, strlen (text), PrintMatch);
		nline++;
	}

	PrintSummary(acsm->acsmPatterns);

	acsmFree (acsm);

	printf ("\n### AC Match Finished ###\n");

	return (0);
}

