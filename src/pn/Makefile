CXXFLAGS = -Wpedantic

pn: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@
	./$@ --run-ut

.PHONY: clean
clean:
	rm -fv pn
