testme: testme.c FORCE
	gcc -o testme testme.c -coverage
	testme || true
	gcov testme.gcda

FORCE: