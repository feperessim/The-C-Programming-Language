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

/* Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of type t. (Block structure will help.) */

#include <stdio.h>

#define SWAP(t,x,y) {t tmp;\
                       tmp = y;\
                       y = x;\
                       x = tmp;\
                    }
int main(void)
{
    int a = 100;
    int b = 50;
              
    SWAP(int, a, b);
    printf("A = %d B = %d\n", a, b);
    return 0;
}    
