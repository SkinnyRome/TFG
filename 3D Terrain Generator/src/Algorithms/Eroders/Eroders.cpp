#include "Eroders.h"
#include <Heightmap\Heightmap.h>
#include <Tools\TerrainGenerationTools.h>

using namespace Erosion;

void Erosion::ErodeHeightmap(Heightmap& h, Properties p) {

	switch (p.type)
	{
	case ErosionType::THERMAL:
		ThermalErosion(h, p.number_of_iterations, p.pThermal.talus_angle, p.pThermal.cFactor);
		break;
	case ErosionType::HYDRAULIC:
		HydraulicErosion(h, p.number_of_iterations,p.pHydraulic.capacity_constant,
			p.pHydraulic.evaporation_constant, p.pHydraulic.rain_constant,
			p.pHydraulic.sediment_constant);
		break;
	default:
#ifdef _DEBUG
		std::cout << "The erosion type is neither valid or setted";
#endif
		break;
	}


}




void Erosion::ThermalErosion(Heightmap & h, int nIterations, float tAngle, float cFactor)
{
	const int hWidth = h.GetSize();
	const int hHeight = h.GetSize();

	const float talusAngle = tAngle / (float)h.GetSize();
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

void Erosion::HydraulicErosion(Heightmap & h, int nIterations, float c_c, float e_c, float r_c, float s_c )
{
	//Water heightmap
	Heightmap water(h.GetSize());

	//Sediment heightmap
	Heightmap sediment(h.GetSize());

	float rain_value{};

	const int hWidth = h.GetSize();
	const int hHeight = h.GetSize();

	const int iterations = nIterations;


	for (int it = 0; it < iterations; it++) {

		//Set Kr value
		rain_value = tools::GetRandomValueBetween(0.01f, r_c);

		//Add water
		water = water + rain_value;


		//Convert to sediment
		h = h - (water * s_c);

		//Add sediment
		sediment = sediment + (water * s_c);

		//Normalize
		//h.Normalize();

		std::vector<std::pair<Cell, float>> vNeighbours;

		for (int i = 0; i < hWidth; i++) {
			for (int j = 0; j < hHeight; j++) {

				float a = h[i][j] + water[i][j];
				float aTotal = 0.0f;
				float dTotal = 0.0f;
				int cells = 0;
				for (const Cell& c : vNeighboursIndex) {

					Cell neigh_cell(i + c.first, j + c.second);

					if (IsInRange(neigh_cell.first, neigh_cell.second, hWidth, hHeight)) {
						float a_neighbour = h[neigh_cell.first][neigh_cell.second] + water[neigh_cell.first][neigh_cell.second];
						float d = a - a_neighbour;
						if (d > 0.0f) {
							dTotal += d;
							aTotal += a_neighbour;
							cells += 1;
							vNeighbours.push_back({ std::move(neigh_cell), d });
						}

					}

				}

				float a_average = aTotal / static_cast<float>(cells);
				
				for (auto& n : vNeighbours) {
					float a_neighbour = h[n.first.first][n.first.second] + water[n.first.first][n.first.second];
					float a_diference = a - a_average;

					float d_i = a - a_neighbour;
					//Move water
					float water_moved = std::fminf(water[i][j], a_diference) * (d_i / dTotal);

					//Move sediment
					float seditmen_moved = sediment[i][j] * (water_moved / water[i][j]);

					water[i][j] -= water_moved;
					water[n.first.first][n.first.second] += water_moved;

					sediment[i][j] -= seditmen_moved;
					sediment[n.first.first][n.first.second] += seditmen_moved;
				}
					
				//Water evaporation
				water[i][j] = water[i][j] * (1 - e_c);

				float max_sediment = c_c * water[i][j];
				
				float sediment_amount = fmaxf(0.0f, sediment[i][j] - max_sediment);

				sediment[i][j] -= sediment_amount;
				
				h[i][j] += sediment_amount;

				vNeighbours.clear();
			}

		}

	}


	h.Normalize();

}

Properties::Properties(ErosionType t):type(t)
{
		
	number_of_iterations = 5;
	
	switch (type)
	{
	case ErosionType::THERMAL:
		pThermal.talus_angle = 0.4f;
		pThermal.cFactor = 0.5f;
		break;
	case ErosionType::HYDRAULIC:
		pHydraulic.capacity_constant = 0.1f;
		pHydraulic.evaporation_constant = 0.5f;
		pHydraulic.rain_constant = 0.4f;
		pHydraulic.sediment_constant = 0.1f;
		break;
	default:
		break;
	}
}


bool Erosion::IsInRange(const int i, const int j, const int w, const int h)
{
	return ((i >= 0 && i < w) && (j >= 0 && j < h));
}

