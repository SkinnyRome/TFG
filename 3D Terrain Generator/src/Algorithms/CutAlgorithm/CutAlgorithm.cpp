#include "CutAlgorithm.h"
#include <Heightmap\Heightmap.h>

using namespace tools;

CutAlgorithm::Properties CutAlgorithm::default_properties = { 3 , 0.5f };

CutAlgorithm::CutAlgorithm(Properties p):prop(p){}


void CutAlgorithm::CutHeightmap(Heightmap & h) const
{

	std::vector<Cut> puntosDeCorte;

	for (int i = 0; i < prop.num_of_slopes; i++) {

		puntosDeCorte.push_back(CreateRandomCut(h.GetWidth(), h.GetHeight()));

	}

	DoCuts(puntosDeCorte, h);

	h.Normalize();

}

void CutAlgorithm::SetProperties(const Properties p)
{ 
	prop = p;
}

CutAlgorithm::Properties CutAlgorithm::GetProperties() const
{
	return prop;
}

Point CutAlgorithm::ClosestPointOnSegment(const Point & a, const Point & b, const Point & p) const
{
	Point diff = p - a;
	Point dir = b - a;

	float t = (diff * dir) / (dir * dir);

	return (dir * t) + a ;
}

void CutAlgorithm::DoCuts(const std::vector<Cut>& v, Heightmap &h) const
{

	float totalIterations = static_cast<float>(v.size()) * h.GetWidth() * h.GetHeight();
	long int it = 0;

	for (int i = 0; i < h.GetWidth(); i++) {
		for (int j = 0; j < h.GetHeight(); j++) {
			Point p(static_cast<float>(i), static_cast<float>(j));

			//float point_offset = (p.second >) ? GetRandomValueBetween() : ;

			for (const auto& pv : v) {
				if (h[i][j] > pv.second.second) {
					(ClosestPointOnSegment(pv.first.first, pv.first.second, p).modulo() > p.modulo()) ? h[i][j] += pv.second.first : h[i][j] += (-pv.second.first);
					it += 1;
				}
			}
		}
	}
}

Cut CutAlgorithm::CreateRandomCut(int width, int height) const
{
	int x1, x2, y1, y2;

	static int axis = 0;

	//X Axis
	if ((axis % 2)== 0) {

		x1 = 0;
		y1 = rand() % (height - 1);


		x2 = width - 1;
		y2 = rand() % (height - 1);

	}
	//Y Axis
	else {

		x1 = rand() % (width - 1);
		y1 = 0;

		x2 = rand() % (width - 1);
		y2 = height - 1;


	}

	float value = GetRandomValueBetween(0.0f, prop.roughness);
	float cut_height = GetRandomValueBetween(0.0f, 0.9f);

	axis++;

	return Cut
	(
		{Point((float)x1, (float)y1) , Point((float)x2, (float)y2)},
		{value, cut_height}
	);

}

CutAlgorithm::Properties::Properties(int nSlopes, float fRoughness)
{

	num_of_slopes = (nSlopes > 10 || nSlopes < 0) ? default_properties.num_of_slopes : nSlopes;

	roughness = 0.01f + (0.02f * ((fRoughness > 1.0f || fRoughness < 0.0f) ? default_properties.roughness : fRoughness));

}
