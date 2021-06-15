#! /bin/sh

make re
make os

./ft_containers > myout
./ft_containers_native > nativeout

diff myout nativeout