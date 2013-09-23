/*
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int c;
    int ant;
    int i;

    while((c = getchar()) != EOF  ) {
        if ( ( ant>=170 ) && ( c==170 ) ) {
            if ((c = getchar()) != EOF && (c == 32)) {
                for (i=0;i<32;i++) {
                    c = getchar();
                    if (  i==28 ) {
                            printf("%d Atención ",c);
                            c = getchar();
                            printf("%d\n",c);
                            c = getchar();
                            printf("%d Meditación ",c);
                            c = getchar();
                            printf(" %d\n",c);
                    }
                }
            }
        }
        ant=c;
    }
    return 0;
}
