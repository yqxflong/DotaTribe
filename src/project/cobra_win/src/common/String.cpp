#include "../../include/common/String.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using  namespace  cobra_win;



int     String::copy(char* pDes, char* pSrc, size_t iLen)
{
	assert( (pDes!=NULL) && (iLen>0) && (pSrc!=NULL) );
	assert( !((pSrc<pDes)&&(pSrc+strlen(pSrc)>=pDes)) );
	assert( !((pSrc>pDes)&&(pDes+strlen(pSrc)>=pSrc)) );

	if (strlen(pSrc) < iLen)
	{
		strcpy(pDes, pSrc);
		return strlen(pSrc);
	}

	memcpy(pDes, pSrc, iLen-1);
	pDes[iLen-1] = '\0';

	return iLen-1;
}

int     String::find(char* pBuffer, char finder)
{
	assert(pBuffer != NULL);

	char* pStr = strchr(pBuffer, finder);
	if (pStr == NULL)
		return -1;

	return int(pStr-pBuffer);
}

int     String::find(char* pBuffer, char* pFinderStr)
{
	assert( (pBuffer!=NULL) && (strlen(pBuffer)>0) && (pFinderStr!=NULL) && (strlen(pFinderStr)>0) );

	char* pStr = strstr(pBuffer, pFinderStr);
	if (pStr == NULL)
		return -1;

	return int(pStr-pBuffer);
}

bool    String::compare(char* pBuffer1, char* pBuffer2, bool bCare)
{
	assert( (pBuffer1!=NULL) && (pBuffer2!=NULL) );

	if (bCare)
	{
		if (strcmp(pBuffer1, pBuffer2) != 0)
			return false;

		return true;
	}

	size_t iLen = strlen(pBuffer1);
    if (iLen != strlen(pBuffer2))
        return false;
    
    for (size_t i=0; i<iLen; i++)
    {
        char temp1 = pBuffer1[i];
        char temp2 = pBuffer2[i];
        
        if(temp1>='A' && temp1<='Z')
            temp1 += 32;
        
        if(temp2>='A' && temp2<='Z')
            temp2 += 32;
        
        if (temp1 != temp2)
            return false;
    }

	return true;
}
