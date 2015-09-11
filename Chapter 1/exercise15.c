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

/* Exercise 1-15. Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.
 */

#include <stdio.h>

#define MAX_TEMP 300

int cel_fahr(int);
int main(void)
{
	int farh;

	for (farh = 0; farh <= MAX_TEMP; farh += 20)
		printf("C° %d - F° %d\n", farh, cel_fahr(farh));
	return 0;	
}
int cel_fahr(int farh)
{
 	return  5 * (farh - 32) / 9;
}	 
