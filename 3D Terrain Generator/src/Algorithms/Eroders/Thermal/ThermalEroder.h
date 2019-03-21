#ifndef THERMALERODER_H
#define THERMALERODER_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif


class Heightmap;

class TERRAINGENERATOR_API ThermalEroder
{
private:

	bool IsAccessible(const int& i, const int& j, const int &w, const int &h);

public:


	ThermalEroder();
	~ThermalEroder();

	void Erode(Heightmap& h);
};

#endif //THERMALERODER_H