CXX=g++
CXXFLAGS= -Wall -O2

STEM=$(basename $(s))
BIN=./bin/$(STEM)

default:
	@echo "$(CXX) $(s) -o $(BIN) $(CXXFLAGS) -std=c++14"
	@$(CXX) $(s) -o $(BIN) $(CXXFLAGS) -std=c++14
	@echo "$(shell pwd)/bin/$(STEM)"
	@$(BIN)

c:
	@echo "gcc $(s) -o $(BIN) $(CXXFLAGS)"
	@gcc $(s) -o $(BIN) $(CXXFLAGS)

cc:
	@echo "$(CXX) $(s) -o $(BIN) $(CXXFLAGS)"
	@$(CXX) $(s) -o $(BIN) $(CXXFLAGS)

c11:
	@echo "$(CXX) $(s) -o $(BIN) $(CXXFLAGS) -std=c++11"
	@$(CXX) $(s) -o $(BIN) $(CXXFLAGS) -std=c++11

c14:
	@echo "$(CXX) $(s) -o $(BIN) $(CXXFLAGS) -std=c++14"
	@$(CXX) $(s) -o $(BIN) $(CXXFLAGS) -std=c++14

java:
	@echo "javac $(s)"
	@javac $(s)
	@echo "java $(STEM)"
	@java $(STEM)
	@echo "$(LGREEN)rm -rf $(STEM).class"
	@rm -rf "$(STEM).class"
