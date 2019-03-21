#include "ThermalEroder.h"
#include <Heightmap\Heightmap.h>

using Cell = std::pair<int, int>;

bool ThermalEroder::IsAccessible(const int & i, const int & j, const int & w, const int & h)
{
	return ((i >= 0 && i < w) && (j >= 0 && j < h));
}

ThermalEroder::ThermalEroder()
{
}


ThermalEroder::~ThermalEroder()
{
}

void ThermalEroder::Erode(Heightmap & h)
{
	const int hWidth = h.GetWidth();
	const int hHeight = h.GetHeight();

	const float talusAngle = 4.0f / (float)h.GetWidth();
	const float c = 0.5f;

	const int iterations = 50;

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

					if (IsAccessible(mNeighbourCell.first, mNeighbourCell.second, hWidth, hHeight)) {
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
