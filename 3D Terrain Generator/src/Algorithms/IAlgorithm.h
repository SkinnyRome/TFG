#ifndef INTERFACE_ALGORITHM_H
#define INTERFACE_ALGORITHM_H

class Heightmap;

class IAlgorithm {
public:

	virtual void GenerateHeightmap(Heightmap &h) const = 0;
	virtual ~IAlgorithm(){};
};

#endif //INTERFACE_ALGORITHM_H