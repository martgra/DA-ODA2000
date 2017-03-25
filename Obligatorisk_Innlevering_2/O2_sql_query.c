#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int skriv_rad(void *, int, char **, char **);

int main() 
{
	char    *err = NULL;
	sqlite3 *db;
	size_t len = 0;
	char text[300]="select file_name FROM filesystem NATURAL JOIN inode_data NATURAL JOIN users  		WHERE user_name='";	
	char text11[300]="select file_path FROM filesystem WHERE inode_number='";
	char text22[300]="select file_name FROM filesystem WHERE file_path='";	
	char text2[20];
	char *text3="';";
	int select;
	

	printf("for å finne filene til en bestemt bruker, trykk 1\nfor å finne filstiene til en bestemt inode trykk 2\nfor å finne alle filene i en oppgitt katalog, trykk 3\n");

	scanf("%i", &select);
	
	if (select == 1)
	{
		printf("skriv inn ønsket brukernavn\n");
		scanf("%s",text2);
		strcat(text, text2);
		strcat(text, text3);
		printf("filene til %s\n", text2);

		if ( SQLITE_OK != sqlite3_open("O2_database.db", &db) )
			exit(1);
		sqlite3_exec(db, text, skriv_rad, 0, &err);
		sqlite3_close(db);
		
		return 0;
	}
	

	if (select == 2)
	{
		printf("skriv inn ønsket inode nr\n");
		scanf("%s",text2);
		strcat(text11, text2);
		strcat(text11, text3);
		printf("stien til %s\n", text2);

		if ( SQLITE_OK != sqlite3_open("O2_database.db", &db) )
			exit(1);
		sqlite3_exec(db, text11, skriv_rad, 0, &err);
		sqlite3_close(db);
		
		return 0;
	}

	if (select == 3)
	{
		printf("skriv inn ønsket sti\n");
		scanf("%s",text2);
		strcat(text22, text2);
		strcat(text22, text3);
		printf("filene i %s\n", text2);

		if ( SQLITE_OK != sqlite3_open("O2_database.db", &db) )
			exit(1);
		sqlite3_exec(db, text22, skriv_rad, 0, &err);
		sqlite3_close(db);
		
		return 0;
	}




	
}

int skriv_rad(void *ubrukt, int ant_kol, char **kolonne, char **kol_navn) 
{
	int i;
	for(i=0; i<ant_kol; i++)
		printf("%s:\t%s\n", kol_navn[i], kolonne[i] );

	return 0;
}
