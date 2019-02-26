#!/bin/bash
e=0; [[ $(sha512sum list.h | cut -d " " -f 1) == f490b44b840b59332f025012e68710ac41494b7d9dcc677bdf16f4c183db9e7cf44fea6c09e8570fff26ef6d1690b77c617a5550509af42267d4065282696f55 ]] || { printf 'error: list.h was modified! re-download it and try again\n'>&2; e=1; }; exit $e
