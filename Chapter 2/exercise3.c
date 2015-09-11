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

/* Exercise 2-3. Write a function htoi(s), which converts a string of hexadecimal digits (including an
optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 9, a through f,
and A through F.
*/

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int htoi(char *s)
{
	int i = 0, converted = 0, sign = 1;
	int size = strlen(s);

	if (s[0] == '-') {
		sign = -1;
		i++;
		size--;
	}
	if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X')) {
		size -= 2;
		i += 2;
	}	
	for (;s[i] != '\0'; i++	) {
		int v;
		if (isdigit(s[i])) {
			v = (s[i] - '0');
		}	
		else {
			v = toupper(s[i]) - 'A' + 10;
		}

		converted += v * ((int)(pow(16, (size -1))));
		size--;
	}
	return converted * sign;
}
int main(void)
{
        printf("\n%d\n", htoi("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"));
       return 0;
}

