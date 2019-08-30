
build: *.pyx *.cpp *.h

	rm -rf PyWire.cpp
	rm -rf PyMap.cpp
	python3 setup_map.py build_ext --inplace
	python3 setup_wire.py build_ext --inplace
