#include "VoronoiDiagram.h"
#include <Heightmap\Heightmap.h>
#include <algorithm>
#include <vector>


tools::Point VoronoiDiagram::CreateRandomSite(const Heightmap &h)
{
	float x = tools::GetRandomValueBetween(0.0f, static_cast<float>(h.GetWidth()) - 1);
	float y = tools::GetRandomValueBetween(0.0f, static_cast<float>(h.GetHeight()) - 1);

	return tools::Point(x, y);
}

VoronoiDiagram::VoronoiDiagram(VoronoiProperties p):_properties(p)
{
}


VoronoiDiagram::~VoronoiDiagram()
{
}

void VoronoiDiagram::GenerateHeightmap(Heightmap & h)
{

	

	std::vector<std::pair<tools::Point, float>> sites;

	for (int i = 0; i < _properties.numOfSites; i++) {
		float value = tools::GetRandomValueBetween(0.8f, 1.0f);
		tools::Point p = CreateRandomSite(h);
		sites.push_back(std::pair<tools::Point, float>(p, value));

		h[(int)p.x][(int)p.y] = value;
	}


	float minDistance;
	float maxDistance = static_cast<float>(sqrt(pow((h.GetWidth()), 2) + pow((h.GetHeight()), 2)));
	bool isSite;

	for (int i = 0; i < h.GetWidth(); i++) {
		for (int j = 0; j < h.GetHeight(); j++) {


			minDistance = static_cast<float>(h.GetWidth() * h.GetHeight());
			isSite = false;
			std::pair<tools::Point, float> nearestSite;
			float distance;
			int s = 0;
			while (s < _properties.numOfSites && !isSite) {

				distance = sqrt(pow((sites[s].first.x - i), 2) + pow((sites[s].first.y - j), 2)) / maxDistance;

				if (distance == 0.0f)
					isSite = true;

				if (!isSite && distance < minDistance) {
					minDistance = distance;
					nearestSite = sites[s];
				}

				s++;
			}


			if (!isSite) {
				//lineal
				float height = nearestSite.second - (minDistance * _properties.fallOff);
				//combined
				//h -= pow(minDistance, dropOff);

				h[i][j] = height;
			}

		}
	}

	h.Normalize();

}

VoronoiDiagram::VoronoiProperties::VoronoiProperties():numOfSites(15), fallOff(0.3f), dropOff(0.5f)
{
}

VoronoiDiagram::VoronoiProperties::VoronoiProperties(int nOS, float fO, float dO):numOfSites(nOS), fallOff(fO), dropOff(dO)
{
}
