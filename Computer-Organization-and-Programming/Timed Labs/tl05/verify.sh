#!/bin/bash
e=0; [[ $(sha512sum binary_search_tree.h | cut -d " " -f 1) == d1dbdea3e2e3d78651bcb8c4e21aa8e0257f3658efb9296a49fe447dc355f75a4e37707cf5e39736d032efdd3f33049a7d4009217992d4c5d22beddcde30ec7f ]] || { printf 'error: binary_search_tree.h was modified! re-download it and try again\n'>&2; e=1; }; exit $e
