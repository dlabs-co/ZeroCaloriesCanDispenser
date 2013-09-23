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
