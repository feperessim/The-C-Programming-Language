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

/* Exercise 5-8. There is no error checking in day_of_year or month_day. Remedy this defect.
 */
#include <stdio.h>
#include <stdlib.h>

#define ONE 1
#define THREE_HUNDRED_AND_SIXTY_SIX 366
#define THREE_HUNDRED_AND_SIXTY_FIVE (THREE_HUNDRED_AND_SIXTY_SIX - ONE)
#define TWELVE 12

static char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
 
/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
        int i, leap;

        leap = ((((year % 4) == 0) && ((year%100) != 0)) || ((year%400) == 0));
	if (leap && (day > daytab[leap][month] || month > TWELVE)) {
		printf("Invalid input\n");
		exit(EXIT_FAILURE);
	}
	else if ((!(leap)) && (day > daytab[leap][month] || month > TWELVE)) {
		printf("Invalid Input\n");
		exit(EXIT_FAILURE);
	}	
        for (i = 1; i < month; i++)
                day += daytab[leap][i];
        return day;
}
 
/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
        int i, leap;
 
        leap = ((((year % 4) == 0) && ((year % 100) == 0)) || ((year % 400) == 0));
	if (leap && (yearday  >  THREE_HUNDRED_AND_SIXTY_SIX)) {
                printf("Invalid input\n");
                exit(EXIT_FAILURE);
        }
        else if ((!(leap)) && (yearday > THREE_HUNDRED_AND_SIXTY_FIVE)) {
                printf("Invalid Input");
                exit(EXIT_FAILURE);
        }
        for (i = 1; yearday > daytab[leap][i]; i++)
                yearday -= daytab[leap][i];
        *pmonth = i;
        *pday = yearday;
}

int main(void)
{
        int a, b;
        
	printf("%dth day of the year\n", day_of_year(2001, 5, 30));
        month_day(2000, 366, &a, &b);
        printf("month = %d  day = %d\n", a, b);
        return 0;
}
