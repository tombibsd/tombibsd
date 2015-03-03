items=$(
	sed -ne '/^additem / { s/^additem //; s/ .*$//; p; }' postinstall
)
for i in $items; do
	echo "===> $i"
	sed -ne "/^additem $i /,/^}/p" \
	    <postinstall \
	    >a
	sed -ne "/^additem $i /,/^}/p" \
	    <../../etc/install.d/$i \
	    >b
	diff -u a b
done
