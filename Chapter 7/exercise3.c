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

/* Exercise 7-3. Revise minprintf to handle more of the other facilities of printf. */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#define MAX_SIZE 1000

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
        va_list ap;     /* points to each unnamed arg in turn */
        char *p, *sval, cval, local_fmt[MAX_SIZE];
        int ival, i;
        double dval;
        void *pval;
	unsigned uval;

        va_start(ap,fmt);       /* make ap point to 1st unnamed arg */
        for (p = fmt; *p; p++) {
		if (*p != '%') {
                        putchar(*p);
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
                        ival = va_arg(ap, int);
                        printf(local_fmt, ival);
                        break;
		case 'u':
		case 'o':
		case 'x':
		case 'X':
			uval = va_arg(ap, unsigned);
                        printf(local_fmt, uval);
                        break;
                case 'f':
	                dval = va_arg(ap, double);
                        printf(local_fmt, dval);
			break;
		case 'g':
                case 'e':
                case 'E':
                        dval = va_arg(ap, double);
			printf(local_fmt, dval);
			break;
		case 'c':
			cval = va_arg(ap, int);
			printf(local_fmt, cval);
			break;
                case 's':
			sval = va_arg(ap, char *);
			printf(local_fmt,sval);
                        break;
		case 'p':
	        	pval = va_arg(ap, void *);
               		printf(local_fmt, pval);
			break;
                default:
                        putchar(*p);
                        break;
                }
        }
	va_end(ap);
}

int main(void)
{
	minprintf("String %s\n", "This is a string");
	minprintf("Integers %d %d %d\n", -1, 0, 1);
	minprintf("Doubles %f %f %g %e %E\n", 0.236, 1.3*10e25, 1.25555555, 1.8888888, 1.999999);
	minprintf("Single Char %c\n", 'a');
	minprintf("Pointer address os a string literal: %p\n", "Address of this string");
	minprintf("Unsigned types %u %u\n", 1, -1);
	return 0;
}
