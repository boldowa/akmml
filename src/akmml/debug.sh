##################################################
# akmml debug script
##################################################
binary=build/debug/unix/bin/akmml

# run gdb
if test -e "$binary" ; then
gdb "$binary"
fi

