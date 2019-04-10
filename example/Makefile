source_dir = ../src
src = $(wildcard $(source_dir)/*)

main: main.cpp libt.so libt1.so libmap.so
	g++ -g -o main main.cpp -std=c++11 -I$(source_dir) ./libt.so ./libt1.so ./libmap.so

libt.so: test.cpp $(src)
	g++ -g -O3 -fPIC -shared -std=c++11 -I$(source_dir) -o libt.so test.cpp $(src)

libt1.so: test1.cpp $(src)
	g++ -g -O3 -fPIC -shared -std=c++11 -I$(source_dir) -o libt1.so test1.cpp $(src)

libmap.so: $(source_dir)/static_key_map.*
	g++ -g -O3 -fPIC -shared -std=c++11 -o libmap.so $(source_dir)/static_key_map.cpp

clean:
	rm lib*.so main
