/*
 *  Copyright 2001-2008 Texas Instruments - http://www.ti.com/
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*  ----------------------------------- Host OS  */
#include <host_os.h>

/*  ----------------------------------- DSP/BIOS Bridge */
#include <std.h>
#include <dbdefs.h>

/*  ----------------------------------- Trace & Debug */
#include <dbc.h>

/*  ----------------------------------- This */
#include <uuidutil.h>

/*
 *  ======== UUID_UuidToString ========
 *  Purpose:
 *      Converts a struct DSP_UUID to a string.
 *      Note: snprintf format specifier is:
 *      %[flags] [width] [.precision] [{h | l | I64 | L}]type
 */
VOID UUID_UuidToString(IN struct DSP_UUID *pUuid, OUT CHAR *pszUuid, IN INT size)
{
	INT i;			/* return result from snprintf. */

	/* DBC_Require(pUuid && pszUuid); */

	i = snprintf(pszUuid, size,
		"%.8X_%.4X_%.4X_%.2X%.2X_%.2X%.2X%.2X%.2X%.2X%.2X",
		(UINT)pUuid->ulData1, pUuid->usData2, pUuid->usData3,
		pUuid->ucData4, pUuid->ucData5, pUuid->ucData6[0],
		pUuid->ucData6[1], pUuid->ucData6[2], pUuid->ucData6[3],
		pUuid->ucData6[4], pUuid->ucData6[5]);

	/* DBC_Ensure(i != -1); */
}

/*
 *  ======== htoi ========
 *  Purpose:
 *      Converts a hex value to a decimal integer.
 */

int htoi(char c)
{
	switch (c) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	case 'a':
		return 10;
	case 'b':
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	}
	return 0;
}

/*
 *  ======== UUID_UuidFromString ========
 *  Purpose:
 *      Converts a string to a struct DSP_UUID.
 */
VOID UUID_UuidFromString(IN CHAR *pszUuid, OUT struct DSP_UUID *pUuid)
{
	CHAR c;
	INT i, j;
	LONG result;
	CHAR *temp = pszUuid;

	result = 0;
	for (i = 0;i < 8;i++) {
		/* Get first character in string*/
		c = *temp;
		/* Increase the results by new value */
		result *= 16;
		result += htoi(c);
		/* Go to next character in string */
		temp++;
	}
	pUuid->ulData1 = result;
	/* Step over underscore */
	temp++;
	result = 0;
	for (i = 0;i < 4;i++) {
		/* Get first character in string */
		c = *temp;
		/* Increase the results by new value */
		result *= 16;
		result += htoi(c);
		/* Go to next character in string */
		temp++;
	}
	pUuid->usData2 = (USHORT)result;
	/* Step over underscore */
	temp++;
	result = 0;
	for (i = 0;i < 4;i++) {
		/* Get first character in string */
		c = *temp;
		/* Increase the results by new value */
		result *= 16;
		result += htoi(c);
		/* Go to next character in string*/
		temp++;
	}
	pUuid->usData3 = (USHORT) result;
	/* Step over underscore */
	temp++;
	result = 0;
	for (i = 0;i < 2;i++) {
		/* Get first character in string */
		c = *temp;
		/* Increase the results by new value */
		result *= 16;
		result += htoi(c);
		/* Go to next character in string */
		temp++;
	}
	pUuid->ucData4 = (UCHAR)result;
	result = 0;
	for (i = 0;i < 2;i++) {
		/* Get first character in string */
		c = *temp;
		/* Increase the results by new value */
		result *= 16;
		result += htoi(c);
		/* Go to next character in string */
		temp++;
	}
	pUuid->ucData5 = (UCHAR)result;
	/* Step over underscore */
	temp++;
	for (j = 0;j < 6;j++) {
		result = 0;
		for (i = 0;i < 2;i++) {
			/* Get first character in string */
			c = *temp;
			/* Increase the results by new value */
			result *= 16;
			result += htoi(c);
			/* Go to next character in string */
			temp++;
		}
		pUuid->ucData6[j] = (UCHAR)result;
	}
}

