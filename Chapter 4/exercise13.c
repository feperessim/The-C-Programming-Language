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

/* Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the string s in place.
 */
#include <stdio.h>                                                                                                                                           
#include <string.h>                                                                                                                                          
                                                                                                                                                             
void reverse(char s[])                                                                                                                                       
{                                                                                                                                                            
        int c;
	static int j, i;

	if (j == 0)
		j = strlen(s) - 1;
	if (i < j) {                                                                                                      
                c = s[i];                                                                                                                                    
                s[i++] = s[j];                                                                                                                               
                s[j--] = c;
		reverse(s);
        }                                                                                                                                                 
}
                                                                                                                                                            
int main(void)
{
        char s[] = "Reverse that amazing";

        reverse(s);
        printf("%s\n", s);
        return 0;
}
