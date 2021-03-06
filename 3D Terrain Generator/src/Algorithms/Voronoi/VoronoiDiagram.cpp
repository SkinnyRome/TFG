#include "VoronoiDiagram.h"
#include <Heightmap\Heightmap.h>
#include <algorithm>
#include <set>

VoronoiDiagram::Properties VoronoiDiagram::default_properties = { 1, 1.0f, 0.0f, 1.0f};

using Site = std::pair<tools::Point, float>;


tools::Point VoronoiDiagram::CreateRandomSite(const Heightmap &h) const
{
	float x = tools::GetRandomValueBetween(0.0f, static_cast<float>(h.GetSize()) - 1);
	float y = tools::GetRandomValueBetween(0.0f, static_cast<float>(h.GetSize()) - 1);

	return tools::Point(x, y);
}

VoronoiDiagram::VoronoiDiagram(Properties p):prop(p), _sitesCoefficients(2,0.0f)
{
	_sitesCoefficients[0] = -1.0f + prop.distance_between;
	_sitesCoefficients[1] = static_cast<float>(abs(_sitesCoefficients[0] * prop.slope_softness));
	

}


void VoronoiDiagram::GenerateHeightmap(Heightmap & h) const
{
	//Second implementation
	struct comp {
		bool operator()(const Site& rhp, const Site& lhp) const {
			return rhp.second < lhp.second;
		}
	};
	

	std::vector<Site> sites;
	float value = 0.0f;
	for (int i = 0; i < prop.numOfSites; i++) {
		value = tools::GetRandomValueBetween(
			0.5f * prop.average_height,
			1.0f * prop.average_height
		);
		tools::Point p = CreateRandomSite(h);
		sites.push_back(Site(p, value));

		h[(int)p.x][(int)p.y] = value;
	}

	
	float minDistance;
	float maxDistance = static_cast<float>(sqrt(pow((h.GetSize()), 2) + pow((h.GetSize()), 2)));
	bool isSite;

	float distance, height;
	for (int i = 0; i < h.GetSize(); i++) {
		for (int j = 0; j < h.GetSize(); j++) {
		distance = height = 0.0f;


			//First implementation
			/*
			minDistance = static_cast<float>(h.GetSize() * h.GetSize());
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
			while (s < prop.numOfSites) {

				distance = pow((sites[s].first.x - i), 2) + pow((sites[s].first.y - j), 2);

				orderedSites.insert(Site(sites[s].first, distance));

				s++;
			}

			int b = 0;
			auto it = orderedSites.begin();
			while (it != orderedSites.end() && b < 2) {
				
				height += (*it).second * _sitesCoefficients[b];
				b++;
				it++;
			}

			h[i][j] = height;
		}
	}

	h.Normalize();

}


VoronoiDiagram::Properties::Properties(int nOS, float s, float d, float a)
{
	//Invariants
	numOfSites = (nOS < 1 || nOS > 200) ? default_properties.numOfSites : nOS;
	slope_softness = (s < 0.0f || s > 1.0f) ? default_properties.slope_softness : s;
	distance_between = (d < 0.0f || d > 1.0f) ? default_properties.distance_between : d;
	average_height = (a < 0.1f || a > 1.0f) ? default_properties.average_height : a;
}
