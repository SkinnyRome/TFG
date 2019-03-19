#include "VoronoiDiagram.h"
#include <Heightmap\Heightmap.h>
#include <algorithm>
#include <set>

using Site = std::pair<tools::Point, float>;


tools::Point VoronoiDiagram::CreateRandomSite(const Heightmap &h)
{
	float x = tools::GetRandomValueBetween(0.0f, static_cast<float>(h.GetWidth()) - 1);
	float y = tools::GetRandomValueBetween(0.0f, static_cast<float>(h.GetHeight()) - 1);

	return tools::Point(x, y);
}

VoronoiDiagram::VoronoiDiagram(VoronoiProperties p):_properties(p), _sitesCoefficients(p.numOfSites,0.0f)
{
	_sitesCoefficients[0] = -1.0f;
	_sitesCoefficients[1] = 1.0f;

}


VoronoiDiagram::~VoronoiDiagram()
{
}

void VoronoiDiagram::GenerateHeightmap(Heightmap & h)
{
	//Second implementation
	struct comp {
		bool operator()(const Site& rhp, const Site& lhp) const {
			return rhp.second < lhp.second;
		}
	};
	

	std::vector<Site> sites;
	float value = 0.0f;
	for (int i = 0; i < _properties.numOfSites; i++) {
		value = tools::GetRandomValueBetween(0.8f, 1.0f);
		tools::Point p = CreateRandomSite(h);
		sites.push_back(Site(p, value));

		h[(int)p.x][(int)p.y] = value;
	}

	/*
	float minDistance;
	float maxDistance = static_cast<float>(sqrt(pow((h.GetWidth()), 2) + pow((h.GetHeight()), 2)));
	bool isSite;*/

	float distance, height;
	for (int i = 0; i < h.GetWidth(); i++) {
		for (int j = 0; j < h.GetHeight(); j++) {
		distance = height = 0.0f;


			/*First implementation
			minDistance = static_cast<float>(h.GetWidth() * h.GetHeight());
			isSite = false;
			Site nearestSite;
			float distance, height;
			distance = height = 0.0f;
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
				height = nearestSite.second - (minDistance * _properties.fallOff);
				//combined
				height -= pow(minDistance, _properties.dropOff);

				h[i][j] = height;
			}
			*/

			/*Second implementation*/
			std::set<Site, comp> orderedSites;
			int s = 0;
			while (s < _properties.numOfSites) {

				distance = pow((sites[s].first.x - i), 2) + pow((sites[s].first.y - j), 2);

				orderedSites.insert(Site(sites[s].first, distance));

				s++;
			}

			int b = 0;
			for (Site site : orderedSites) {
				height += site.second * _sitesCoefficients[b];
				b++;
			}

			h[i][j] = height;
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
