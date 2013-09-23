:<<EOLICENSE
/*
 *   Copyright 2013 Dlabs Hackerspace <socios@dlabs.co>
 *
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
EOLICENSE


while read grupo; do
     [[ $grupo = "aaaa" ]] && {
        read grupo
        [[ ${grupo:2:4} == "20" ]] && {
            for ((a=1; a <= 16 ; a++)); do
                read grupo;
                [[ $a == 14 ]] && echo "Concentración: ${grupo:2:4}";
            done
        }
    }
done < <(/usr/bin/hexdump -v -e '1/2 "%04x"' -e '"\n"' $1 )
