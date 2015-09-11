/* Copyright (C) 2015 Felipe de Lima Peressim
 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Exercise 7-4. Write a private version of scanf analogous to minprintf from the previous section. */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#define MAX_SIZE 10000

void minscanf(char *fmt, ...)
{
	va_list ap;     /* points to each unnamed arg in turn */
        char *p, *sval, *cval, local_fmt[MAX_SIZE];
        int *ival, i;
        void *pval;
        unsigned *uval;
	float *fval;

        va_start(ap,fmt);       /* make ap point to 1st unnamed arg */
        for (p = fmt; *p; p++) {
		if (*p != '%') {
                        continue;
                }
		i = 0 ;
		local_fmt[i++] = '%';
		while ((*p + 1) && !isalpha(*(p + 1))) {
			local_fmt[i++] = *++p;
		}
		local_fmt[i++] = *(p+1);
		local_fmt[i] = '\0';
		switch (*++p) {
                case 'd':
		case 'i':
                        ival = va_arg(ap, int*);
                        scanf(local_fmt, ival);
                        break;
		case 'u':
		case 'o':
		case 'x':
		case 'X':
			uval = va_arg(ap, unsigned *);
                        scanf(local_fmt, uval);
                        break;
                case 'f':
		case 'g':
                case 'e':
                case 'E':
                        fval = va_arg(ap, float *);
			scanf(local_fmt, fval);
			break;
		case 'c':
			cval = va_arg(ap, char *);
			scanf(local_fmt, cval);
			break;
                case 's':
			sval = va_arg(ap, char *);
			scanf(local_fmt,sval);
                        break;
		case 'p':
	        	pval = va_arg(ap, void *);
               		scanf(local_fmt, pval);
			break;
                default:
			scanf(local_fmt);
                        break;
                }
		i = 0;
        }
	va_end(ap);
}
int main(void)
{
	int i;
	unsigned u;
	float f;
	char string[10];
	char c;

	minscanf("%d %u %f %c %s", &i, &u, &f,  &c, string);
	printf("%d %u %f %c %s\n", i, u, f, c, string);
	return 0;
}
