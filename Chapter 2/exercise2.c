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

/* Exercise 2-2. Write a loop equivalent to the for loop above without using && or ||.
 */
 for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
	s[i] = c; 

int lgetline(char s[], int lim)
{
        int c, i, state;

        i = 0;
        state = IN;
        while (i < lim - 1) {
                if ((c = getchar()) == '\n') {
                        s[i] = c;
                        ++i;
                        s[i] = '\0';
                        return i;
                }
                if (c == EOF) {
                        s[i] = '\0';
                        return i;
                }
                s[i] = c;
                i++;
        }
        if (c == '\n') {
                s[i] = c;
                ++i;
        }
        s[i] = '\0';
        return i;
}

