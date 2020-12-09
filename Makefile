test-c: point_search.c point_alg.c node.c test.c
	gcc point_search.c point_alg.c node.c test.c -o test-c.out -O3

test-debug-c: point_search.c point_alg.c node.c test.c
	gcc point_search.c point_alg.c node.c test.c -o test-debug-c.out -g -O3

test-c++: point_search.c point_alg.c node.c test.c
	g++ point_search.c point_alg.c node.c test.c -o test-c++.out -O3

test-debug-c++: point_search.c point_alg.c node.c test.c
	g++ point_search.c point_alg.c node.c test.c -o test-debug-c++.out -g -O3

unsafe-test-c: point_search.c point_alg.c node.c test.c
	gcc point_search.c point_alg.c node.c test.c -o unsafe-test-c.out -Ofast

unsafe-test-c++: point_search.c point_alg.c node.c test.c
	g++ point_search.c point_alg.c node.c test.c -o unsafe-test-c++.out -Ofast

dll-c: point_search.c point_alg.c node.c dllmain.c
	gcc -c -DBUILDING_EXAMPLE_DLL point_search.c point_alg.c node.c dllmain.c -O3
	gcc -shared -o solution.dll dllmain.o point_search.o point_alg.o node.o -Wl,--out-implib,solution.a -O3

dll-c++: point_search.c point_alg.c node.c dllmain.c
	g++ -c -DBUILDING_EXAMPLE_DLL dllmain.c point_search.c point_alg.c -O3
	g++ -shared -o solution.dll dllmain.o point_search.o point_alg.o node.o -Wl,--out-implib,solution.a -O3

clean:
	rm -f *.out
	rm -f *.o
	rm -f *.a
	rm -f *.dll