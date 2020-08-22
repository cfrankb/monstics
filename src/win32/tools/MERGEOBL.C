//
// FICHIER: MERGE.C
// AUTEUR : FRANCOIS BLANCHETTE        
// BUT    : 
// DATE   : 26 DECEMBRE 1998
//

#include <stdio.h>
#include <process.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
        
#define begin_struct typedef struct {
#define end_struct(_struct) } _struct;  
    
begin_struct        
	char Id[4];
	long nSize; // 32bits 
	long nCurrFrame;
end_struct (OBL4HEADER);

begin_struct        
	long nLen;
	long nHei;
	long nMapped;
end_struct (OBL4);
    
void main(int nArgs, char *szFilenames[])
{

	char szTemp[_MAX_PATH];
	char *szWhere;

	FILE *tfile;
	FILE *sfile;
	    
	int n;
	int i=0;
	int nImages=0;
	
	OBL4HEADER FilterHeader;
	OBL4 FrameHeader;
	char *pData =NULL;	

	puts ("MERGEOBL - OBL4 merger utility");
	puts ("(C) 1998 Francois Blanchette\n");
	    
	tfile = fopen ("merge.obl", "wb");	    
	if (tfile==NULL) {
		puts("Cannot create output file");
		exit (1);
	}		

	fwrite (&FilterHeader, sizeof(OBL4HEADER), 1, tfile);

	while (i<nArgs-1)
	{                     
		strcpy (szTemp, szFilenames[i+1]);
		szWhere = szTemp;
		while (szWhere && _stricmp(szWhere, ".obl")!=0 ) {
			szWhere = strrchr( szFilenames[i+1], '.');
			if (szWhere && _stricmp(szWhere, ".obl")!=0)
				szWhere++;
		}

		if (_stricmp(szWhere, ".obl")!=0)
			strcat (szTemp, ".obl");
		
		sfile = fopen ( szTemp, "rb");      
		if (sfile!=NULL)
		{
			fread (&FilterHeader, sizeof (OBL4HEADER),1, sfile);
			if (memcmp (FilterHeader.Id,"OBL4", 4) ==0)
			{		
				for (n=0; n<FilterHeader.nSize; n++)
				{
					fread (&FrameHeader, sizeof (OBL4), 1, sfile);
					pData = malloc (FrameHeader.nLen * FrameHeader.nHei);
					fread (pData, FrameHeader.nLen * FrameHeader.nHei, 1, sfile);

					fwrite (&FrameHeader, sizeof (OBL4), 1, tfile);
					fwrite (pData, FrameHeader.nLen * FrameHeader.nHei, 1, tfile);
					free (pData);			
				}              
			
			
				nImages = nImages + FilterHeader.nSize;
				fclose (sfile);			
				printf("%c%s%c Added.\n", 34, szTemp, 34);
			}
			else
			{
				fclose (sfile);			
				printf("File %c%s%c not OBL4.\n", 34, szTemp, 34);			
			}
		}                                             
		else
		{
			printf("Cannot open for reading %c%s%c.\n", 34, szTemp, 34);
		}

		i++;		
	}

	fseek (tfile, 0, SEEK_SET);	 
	memcpy(FilterHeader.Id, "OBL4", 4);
	FilterHeader.nCurrFrame =0;
	FilterHeader.nSize = nImages;
	fwrite (&FilterHeader, sizeof(OBL4HEADER), 1, tfile);
	fclose (tfile);			
	
	puts("\nProgram completed!");
}