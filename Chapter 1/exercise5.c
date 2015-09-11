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

/* Exercise 1-5. Modify the temperature conversion program to print the table in reverse order, that is, from 300
 * degrees to 0.
 */
#include <stdio.h>

/* print Fahrenheit-Celsius table */
int main(void)
{
        int fahr;

        for(fahr = 300; fahr >= 0; fahr = fahr - 20)
                printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
	return 0;
}

