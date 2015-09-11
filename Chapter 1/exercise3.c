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

/* Exercise 1-3. Modify the temperature conversion program to print a heading above the table.
 */
#include <stdio.h>

/* printf Fahrenheit-Celsius table
 *      for fahr = 0, 20, ..., 3000; floating-point version */
int main(void)
{
        float fahr, celsius;
        float lower, upper, step;

        lower = 0;      /* lower limit of temperatuire scale */
        upper = 300;    /* upper limit */
        step = 20;      /* step size */

	printf("Celsius\tFahrenheit\n");
        fahr = lower;
        while (fahr <= upper){
                celsius = (5.0/9.0) *(fahr - 32.0);
                printf("%3.0f %10.1f\n", fahr, celsius);
                fahr = fahr + step;
        }
	return 0;
}

