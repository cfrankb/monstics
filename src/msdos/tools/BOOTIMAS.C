
/* FICHIER: BOOTIMA.C
   BUT    : FAIRE UNE IMAGE DU "BOOT SECTOR"
   AUTEUR : FRANCOIS BLANCHETTE */

#include <user\friendly.h>
/* absread example */

#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <dos.h>
#define MAJ(_Car) (((_Car >= 'a') && (_Car <= 'z')) ? (_Car - 'a' + 'A') : (_Car))

FILE *FICHIER;
int main(void)
{
	char drive;
	char Filename[128];
  int i, strt, ch_out, sector;
  char buf[512];
	puts("BOOTIMA.EXE");
	puts("programme de generation d'image du BOOT SECTOR");
	puts("(c) 1995 FRANCOIS BLANCHETTE\n");
	printf("Fichier:");
	gets(Filename);
	fflush(stdin);

	drive=0;
	while ((drive <'A') || (drive >'C'))
{  printf("Lecteur:");
	drive=MAJ(getch());
	putchar(drive);
	putchar('\n');}

  if (drive !='C')
	  printf("Insert a diskette into drive %c and press any key\n", drive);
  else
	  puts("Press a key to capture master boot sector.");

  fflush(stdin);
  getch();
  sector = 0;
  if (absread(drive-'A', 1, sector, &buf) != 0)
  {
	 perror("Disk problem");
	 exit(1);
  }
  printf("Read OK\n");
  strt = 3;
  for (i=0; i<80; i++)
  {
	 ch_out = buf[strt+i];
	 putchar(ch_out);
  }
  printf("\n");

  FICHIER = fopen(Filename, "wb");
  if (FICHIER==0)
  {

	puts("Erreur d'ecriture.");
	exit(1);
  }
  fwrite(buf, 512, 1, FICHIER);
  fclose(FICHIER);


  return(0);
}

/*
void main()
{
	char Drive[128];



} */