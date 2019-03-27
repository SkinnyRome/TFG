#include "ThermalEroder.h"
#include <Heightmap\Heightmap.h>
#include <Tools\TerrainGenerationTools.h>



bool IsInRange(const int & i, const int & j, const int & w, const int & h)
{
	return ((i >= 0 && i < w) && (j >= 0 && j < h));
}

void ErodeHeightmap(Heightmap& h, ErosionProperties p) {

	switch (p.type)
	{
	case ErosionType::THERMAL:
		ThermalErosion(h, p.pThermal.nIterations, p.pThermal.tAngle, p.pThermal.cFactor);
		break;
	case ErosionType::HYDRAULIC:
		HydraulicErosion(h, 5);
		break;
	default:
#ifdef _DEBUG
		std::cout << "The erosion type is neither valid or setted";
#endif
		break;
	}


}




void ThermalErosion(Heightmap & h, int nIterations, float tAngle, float cFactor)
{
	const int hWidth = h.GetWidth();
	const int hHeight = h.GetHeight();

	const float talusAngle = tAngle / (float)h.GetWidth();
	const float c = cFactor;

	const int iterations = nIterations;

	const std::vector<Cell> vNeighboursIndex = { {1,0},{0,1},{-1,0},{0,-1} };	//Von Neuman neigbours index.


	for (int it = 0; it < iterations; it++) {

		std::vector<std::pair<Cell, float>> vNeighbours;

		for (int i = 0; i < hWidth; i++) {
			for (int j = 0; j < hHeight; j++) {

				float dMax = 0.0f;
				float dTotal = 0.0f;
				float d;
				int n = 0;
				for (const Cell& c : vNeighboursIndex) {

					Cell mNeighbourCell(i + c.first, j + c.second);

					if (IsInRange(mNeighbourCell.first, mNeighbourCell.second, hWidth, hHeight)) {
						d = h[i][j] - h[mNeighbourCell.first][mNeighbourCell.second];

						if (d > talusAngle) {

							dTotal += d;
							vNeighbours.push_back({ std::move(mNeighbourCell), d });

							dMax = (d > dMax) ? d : dMax;

						}

					}

				}


				for (std::pair<Cell, float>& n : vNeighbours) {
					h[n.first.first][n.first.second] += ((c * (dMax - talusAngle)) * (n.second / dTotal));
				}

				vNeighbours.clear();
			}

		}

	}

	h.Normalize();
}

void HydraulicErosion(Heightmap & h, int nIterations)
{
	//Water heightmap
	Heightmap water(h.GetWidth(), h.GetHeight());

	//Sediment heightmap
	Heightmap sediment(h.GetWidth(), h.GetHeight());



	float Kr = 0.01f;
	float Ks = 0.01f;
	float Ke = 0.5f;
	float Kc = 0.01f;

	const int hWidth = h.GetWidth();
	const int hHeight = h.GetHeight();

	const int iterations = nIterations;


	for (int it = 0; it < iterations; it++) {

		//Set Kr value
		Kr = tools::GetRandomValueBetween(0.01f, 0.1f);

		//Add water
		water = water + Kr;


		//Convert to sediment
		h = h - (water * Ks);

		//Add sediment
		sediment = sediment + (water * Ks);

		//Normalize
		//h.Normalize();

		std::vector<std::pair<Cell, float>> vNeighbours;

		for (int i = 0; i < hWidth; i++) {
			for (int j = 0; j < hHeight; j++) {

				float a = h[i][j] + water[i][j];
				float a_min = 1.0f;
				Cell low_neigbour {};
				float dMax = 0.0f;
				float aTotal = 0.0f;
				float dTotal = 0.0f;
				float d;
				int cells = 0;
				int n = 0;
				for (const Cell& c : vNeighboursIndex) {

					Cell neigh_cell(i + c.first, j + c.second);

					if (IsInRange(neigh_cell.first, neigh_cell.second, hWidth, hHeight)) {
						float a_neighbour = h[neigh_cell.first][neigh_cell.second] + water[neigh_cell.first][neigh_cell.second];
						float d = a - a_neighbour;
						if (d > 0.0f) {
							dTotal += d;
							aTotal += a;
							cells += 1;
							vNeighbours.push_back({ std::move(neigh_cell), d });
						}

					}

				}

				float a_average = aTotal / static_cast<float>(cells);
				
				for (auto& n : vNeighbours) {
					float a_diference = a - a_average;
					float d_i = a - n.second;
					//Move water
					float water_moved = std::fminf(water[i][j], a_diference) * (d_i / dTotal);
					water[i][j] -= water_moved;
					water[n.first.first][n.first.second] += water_moved;

					//Move sediment
					float seditmen_moved = sediment[i][j] * (water_moved / water[i][j]);
					sediment[i][j] -= seditmen_moved;
					sediment[n.first.first][n.first.second] += seditmen_moved;
				}
					
				//Water evaporation
				water[i][j] = water[i][j] * (1 - Ke);

				float max_sediment = Kc * water[i][j];
				
				float sediment_amount = fmaxf(0.0f, sediment[i][j] - max_sediment);

				sediment[i][j] -= sediment_amount;
				
				h[i][j] += sediment_amount;

				vNeighbours.clear();
			}

		}

	}





	h.Normalize();

}

ErosionProperties::ErosionProperties(ErosionType t):type(t)
{
	switch (type)
	{
	case ErosionType::THERMAL:
		pThermal.nIterations = 5;
		pThermal.tAngle = 0.4f;
		pThermal.cFactor = 0.5f;
		break;
	case ErosionType::HYDRAULIC:
		break;
	default:
		break;
	}
}
