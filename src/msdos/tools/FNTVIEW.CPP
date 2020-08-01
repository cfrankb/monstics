/* PROGRAMME: FNTview.CPP
   BUT		: Permettre la visualisation d'une image en format .FNT
   AUTEUR	: Francois Blanchette
*/

#include <stdio.h>
#include <process.h>
#include <alloc.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <conio.h>

char far ImaData[16384];	/* Line, Row, X,Y */
FILE *ImaFile;

void drawima(int len, int hei)
{

	char *source = ImaData;
	for (int y=0; y<hei; y++)
		for (int x=0; x<len; x++)
		{
			int dest = x*8+y*0x0a00;
			asm {   pusha
					push ds
					push es

					mov dx,0xa000
					mov es,dx
					mov di,dest
					lds si,source

					xor bx,bx
					mov dx,8
				  }
L2:
			  asm{
					mov cx,8
				 }
L1:
			asm{	mov al,[si]
					mov es:[di],al
					inc si
					inc di
					loop L1

					add di,0x140-8
					mov cx,dx
					dec dx
					loop L2

					pop es
					pop ds
					popa

				}




					source = source +64;
		}


}

void setmode(char Mode)
{

	asm {   push ds /* Indispensable  PUSH DS, PUSHA*/
			pusha
			mov ah,0
			mov al,Mode
			int 0x10

			mov ah,0xf
			int 0x10

			popa
			pop ds /* Indispensable POPA, POP DS */
		}
}

void SetXY(char x,char y)
{
 asm{			mov bh,0
				mov dl,x
				mov dh,y
				mov ah,2
				int 0x10
	}
}

void main(int Nb, char *args[])
{
	char Hei=16, Len=16;

	if (Nb>=2)
	{
		ImaFile = fopen(args[1], "rb");
		if (ImaFile)
		{

			fread(ImaData, Hei*Len*64, 1, ImaFile);
			fclose (ImaFile);
		}
		else
		{
		printf("FATALE:Incapable d'ouvrir %c%s%c",34,args[1],34);
		exit(2);
		}
	}
	else
	{
		puts("\nFATALE:Parametre manquant sur la ligne de commandes.");
		printf("Syntaxe: %s <NomImage>\n\n", args[0]);
		puts("exemple:");
		printf("%s INTRO.IMA\n", args[0]);
		exit(1);
	}

	setmode(0x13);
	drawima(Len,Hei);
	SetXY(0,20);
	printf("FICHIER: %s", args[1]);
	getche();
	setmode(3);

}
