#include "CutAlgorithm.h"
#include <Heightmap\Heightmap.h>



CutAlgorithm::CutAlgorithm()
{
}


CutAlgorithm::~CutAlgorithm()
{
}


void CutAlgorithm::GenerateHeightmap(Heightmap & h)
{

	const int nIterations = 10000;

	std::vector<PuntosYValor> puntosDeCorte;
	puntosDeCorte.reserve(nIterations);


	for (int i = 0; i < nIterations; i++) {

		puntosDeCorte.push_back(RandomCut(0, h.GetWidth(), h.GetHeight()));

	}

	DoCuts(puntosDeCorte, h);

	h.Normalize();

}

Point CutAlgorithm::ClosestPointOnSegment(const Point & a, const Point & b, const Point & p)
{
	Point diff = p - a;
	Point dir = b - a;

	float t = (diff * dir) / (dir * dir);

	return (dir * t) + a ;
}

void CutAlgorithm::DoCuts(const std::vector<PuntosYValor>& v, Heightmap &h)
{

	float totalIterations = static_cast<float>(v.size()) * h.GetWidth() * h.GetHeight();
	long int it = 0;

	for (int i = 0; i < h.GetWidth(); i++) {
		for (int j = 0; j < h.GetHeight(); j++) {
			Point p(static_cast<float>(i), (float)j);

			for (size_t pv = 0; pv < v.size(); pv++) {

				(ClosestPointOnSegment(v[pv].first.first, v[pv].first.second, p).modulo() > p.modulo()) ? h[i][j] += v[pv].second : h[i][j] += (-v[pv].second);
				it += 1;
			}
		}
	}
}

PuntosYValor CutAlgorithm::RandomCut(int axis, int width, int height)
{
	int x1, x2, y1, y2;


	//X Axis
	if (axis == 0) {

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

	float valor = GetRandomValueBetween(-0.5f, 0.5f);

	return PuntosYValor(std::pair<Point, Point>(Point((float)x1, (float)y1), Point((float)x2, (float)y2)), valor);

}
