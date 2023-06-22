build_dir := build

all: build

build:
	mkdir -p $(build_dir)
	cd $(build_dir) && cmake ..
	cmake --build $(build_dir)

clean:
	rm -rf $(build_dir)

run:
	./build/LetItOut
