buildG++:
	g++ main.cpp -o XOEAI
buildClang:
	clang -stdlib=libc++ -lc++ main.cpp -o XOEAI

buildTestG++:
	g++ ./tests/TestMain.cpp -o ./tests/TestMain
buildTestClang:
	clang -stdlib=libc++ -lc++ ./tests/TestMain.cpp -o ./tests/TestMain


g++: buildG++
	./XOEAI
clang: buildClang
	./XOEAI


testG++: buildTestG++
	./tests/TestMain

testClang: buildTestClang
	./tests/TestMain


run: ./XOEAI
	./XOEAI
runTest: ./tests/TestMain
	./tests/TestMain

clean:
	rm ./XOEAI
	rm ./tests/TestMain


