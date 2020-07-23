#include "json.hpp"
#include <iostream>
#include <fstream>

#pragma warning(disable:4996)

using nlohmann::json;
using namespace std;

int main()
{
	vector<string> listOfScene = { "scene1_map.json", "scene2_map.json", "scene3_map.json", "scene4_map.json" };
	string parentPath = "C:\\Users\\HoangMai\\Downloads\\CastleVania\\05-ScenceManager\\textures\\";

	for (string fname : listOfScene) {
		string fPath = parentPath + fname;

		ifstream f(fPath);
		json j = json::parse(f);

		cout << j["height"] << endl;

		int gridWidth = 88;
		int gridHeight = 196;

		for (int i = 0; i < j["layers"].size(); ++i)
		{
			if (j["layers"][i]["name"] == "Wall")
			{
				int minXGrid, minYGrid, maxXGrid, maxYGrid;

				for (int k = 0; k < j["layers"][i]["objects"].size(); ++k) {
					json jArray = json::array(); // create array to store grid position
					int width = j["layers"][i]["objects"][k]["width"];
					int height = j["layers"][i]["objects"][k]["height"];
					float x = j["layers"][i]["objects"][k]["x"];
					float y = j["layers"][i]["objects"][k]["y"];

					minXGrid = int(x) / int(gridWidth);
					minYGrid = int(y) / int(gridHeight);
					maxXGrid = int(x + width) / int(gridWidth);
					maxYGrid = int(y + height) / int(gridHeight);

					for (int i = minXGrid; i <= maxXGrid; i++)
						for (int j = minYGrid; j <= maxYGrid; j++) {
							json jObject = json::basic_json();
							jObject.push_back(json::object_t::value_type("col", i));
							jObject.push_back(json::object_t::value_type("row", j));
							jArray.push_back(jObject); // add col and row to array
						}
					//Add grid position to objects
					j["layers"][i]["objects"][k].push_back(json::object_t::value_type("gridPos", jArray));
				}
			}

			if (j["layers"][i]["name"] == "Torch")
			{
				int minXGrid, minYGrid, maxXGrid, maxYGrid;

				for (int k = 0; k < j["layers"][i]["objects"].size(); ++k) {
					json jArray = json::array(); // create array to store grid position
					int width = j["layers"][i]["objects"][k]["width"];
					int height = j["layers"][i]["objects"][k]["height"];
					float x = j["layers"][i]["objects"][k]["x"];
					float y = j["layers"][i]["objects"][k]["y"];

					minXGrid = int(x) / int(gridWidth);
					minYGrid = int(y) / int(gridHeight);
					maxXGrid = int(x + width) / int(gridWidth);
					maxYGrid = int(y + height) / int(gridHeight);

					for (int i = minXGrid; i <= maxXGrid; i++)
						for (int j = minYGrid; j <= maxYGrid; j++) {
							json jObject = json::basic_json();
							jObject.push_back(json::object_t::value_type("col", i));
							jObject.push_back(json::object_t::value_type("row", j));
							jArray.push_back(jObject); // add col and row to array
						}
					//Add grid position to objects
					j["layers"][i]["objects"][k].push_back(json::object_t::value_type("gridPos", jArray));
				}
			}

			if (j["layers"][i]["name"] == "Portal")
			{
				int minXGrid, minYGrid, maxXGrid, maxYGrid;

				for (int k = 0; k < j["layers"][i]["objects"].size(); ++k) {
					json jArray = json::array(); // create array to store grid position
					int width = j["layers"][i]["objects"][k]["width"];
					int height = j["layers"][i]["objects"][k]["height"];
					float x = j["layers"][i]["objects"][k]["x"];
					float y = j["layers"][i]["objects"][k]["y"];

					minXGrid = int(x) / int(gridWidth);
					minYGrid = int(y) / int(gridHeight);
					maxXGrid = int(x + width) / int(gridWidth);
					maxYGrid = int(y + height) / int(gridHeight);

					for (int i = minXGrid; i <= maxXGrid; i++)
						for (int j = minYGrid; j <= maxYGrid; j++) {
							json jObject = json::basic_json();
							jObject.push_back(json::object_t::value_type("col", i));
							jObject.push_back(json::object_t::value_type("row", j));
							jArray.push_back(jObject); // add col and row to array
						}
					//Add grid position to objects
					j["layers"][i]["objects"][k].push_back(json::object_t::value_type("gridPos", jArray));
				}
			}

			if (j["layers"][i]["name"] == "Hidden Objects")
			{
				int minXGrid, minYGrid, maxXGrid, maxYGrid;

				for (int k = 0; k < j["layers"][i]["objects"].size(); ++k) {
					json jArray = json::array(); // create array to store grid position
					int width = j["layers"][i]["objects"][k]["width"];
					int height = j["layers"][i]["objects"][k]["height"];
					float x = j["layers"][i]["objects"][k]["x"];
					float y = j["layers"][i]["objects"][k]["y"];

					minXGrid = int(x) / int(gridWidth);
					minYGrid = int(y) / int(gridHeight);
					maxXGrid = int(x + width) / int(gridWidth);
					maxYGrid = int(y + height) / int(gridHeight);

					for (int i = minXGrid; i <= maxXGrid; i++)
						for (int j = minYGrid; j <= maxYGrid; j++) {
							json jObject = json::basic_json();
							jObject.push_back(json::object_t::value_type("col", i));
							jObject.push_back(json::object_t::value_type("row", j));
							jArray.push_back(jObject); // add col and row to array
						}
					//Add grid position to objects
					j["layers"][i]["objects"][k].push_back(json::object_t::value_type("gridPos", jArray));
				}
			}

			if (j["layers"][i]["name"] == "Candle")
			{
				int minXGrid, minYGrid, maxXGrid, maxYGrid;

				for (int k = 0; k < j["layers"][i]["objects"].size(); ++k) {
					json jArray = json::array(); // create array to store grid position
					int width = j["layers"][i]["objects"][k]["width"];
					int height = j["layers"][i]["objects"][k]["height"];
					float x = j["layers"][i]["objects"][k]["x"];
					float y = j["layers"][i]["objects"][k]["y"];

					minXGrid = int(x) / int(gridWidth);
					minYGrid = int(y) / int(gridHeight);
					maxXGrid = int(x + width) / int(gridWidth);
					maxYGrid = int(y + height) / int(gridHeight);

					for (int i = minXGrid; i <= maxXGrid; i++)
						for (int j = minYGrid; j <= maxYGrid; j++) {
							json jObject = json::basic_json();
							jObject.push_back(json::object_t::value_type("col", i));
							jObject.push_back(json::object_t::value_type("row", j));
							jArray.push_back(jObject); // add col and row to array
						}
					//Add grid position to objects
					j["layers"][i]["objects"][k].push_back(json::object_t::value_type("gridPos", jArray));
				}
			}

			if (j["layers"][i]["name"] == "Stair")
			{
				int minXGrid, minYGrid, maxXGrid, maxYGrid;

				for (int k = 0; k < j["layers"][i]["objects"].size(); ++k) {
					json jArray = json::array(); // create array to store grid position
					int width = j["layers"][i]["objects"][k]["width"];
					int height = j["layers"][i]["objects"][k]["height"];
					float x = j["layers"][i]["objects"][k]["x"];
					float y = j["layers"][i]["objects"][k]["y"];

					minXGrid = int(x) / int(gridWidth);
					minYGrid = int(y) / int(gridHeight);
					maxXGrid = int(x + width) / int(gridWidth);
					maxYGrid = int(y + height) / int(gridHeight);

					for (int i = minXGrid; i <= maxXGrid; i++)
						for (int j = minYGrid; j <= maxYGrid; j++) {
							json jObject = json::basic_json();
							jObject.push_back(json::object_t::value_type("col", i));
							jObject.push_back(json::object_t::value_type("row", j));
							jArray.push_back(jObject); // add col and row to array
						}
					//Add grid position to objects
					j["layers"][i]["objects"][k].push_back(json::object_t::value_type("gridPos", jArray));
				}
			}
			if (j["layers"][i]["name"] == "Brick")
			{
				int minXGrid, minYGrid, maxXGrid, maxYGrid;

				for (int k = 0; k < j["layers"][i]["objects"].size(); ++k) {
					json jArray = json::array(); // create array to store grid position
					int width = j["layers"][i]["objects"][k]["width"];
					int height = j["layers"][i]["objects"][k]["height"];
					float x = j["layers"][i]["objects"][k]["x"];
					float y = j["layers"][i]["objects"][k]["y"];

					minXGrid = int(x) / int(gridWidth);
					minYGrid = int(y) / int(gridHeight);
					maxXGrid = int(x + width) / int(gridWidth);
					maxYGrid = int(y + height) / int(gridHeight);

					for (int i = minXGrid; i <= maxXGrid; i++)
						for (int j = minYGrid; j <= maxYGrid; j++) {
							json jObject = json::basic_json();
							jObject.push_back(json::object_t::value_type("col", i));
							jObject.push_back(json::object_t::value_type("row", j));
							jArray.push_back(jObject); // add col and row to array
						}
					//Add grid position to objects
					j["layers"][i]["objects"][k].push_back(json::object_t::value_type("gridPos", jArray));
				}
			}

			if (j["layers"][i]["name"] == "ZombieZone")
			{
				int minXGrid, minYGrid, maxXGrid, maxYGrid;

				for (int k = 0; k < j["layers"][i]["objects"].size(); ++k) {
					json jArray = json::array(); // create array to store grid position
					int width = j["layers"][i]["objects"][k]["width"];
					int height = j["layers"][i]["objects"][k]["height"];
					float x = j["layers"][i]["objects"][k]["x"];
					float y = j["layers"][i]["objects"][k]["y"];

					minXGrid = int(x) / int(gridWidth);
					minYGrid = int(y) / int(gridHeight);
					maxXGrid = int(x + width) / int(gridWidth);
					maxYGrid = int(y + height) / int(gridHeight);

					for (int i = minXGrid; i <= maxXGrid; i++)
						for (int j = minYGrid; j <= maxYGrid; j++) {
							json jObject = json::basic_json();
							jObject.push_back(json::object_t::value_type("col", i));
							jObject.push_back(json::object_t::value_type("row", j));
							jArray.push_back(jObject); // add col and row to array
						}
					//Add grid position to objects
					j["layers"][i]["objects"][k].push_back(json::object_t::value_type("gridPos", jArray));
				}
			}

			if (j["layers"][i]["name"] == "1-way Wall")
			{
				int minXGrid, minYGrid, maxXGrid, maxYGrid;

				for (int k = 0; k < j["layers"][i]["objects"].size(); ++k) {
					json jArray = json::array(); // create array to store grid position
					int width = j["layers"][i]["objects"][k]["width"];
					int height = j["layers"][i]["objects"][k]["height"];
					float x = j["layers"][i]["objects"][k]["x"];
					float y = j["layers"][i]["objects"][k]["y"];

					minXGrid = int(x) / int(gridWidth);
					minYGrid = int(y) / int(gridHeight);
					maxXGrid = int(x + width) / int(gridWidth);
					maxYGrid = int(y + height) / int(gridHeight);

					for (int i = minXGrid; i <= maxXGrid; i++)
						for (int j = minYGrid; j <= maxYGrid; j++) {
							json jObject = json::basic_json();
							jObject.push_back(json::object_t::value_type("col", i));
							jObject.push_back(json::object_t::value_type("row", j));
							jArray.push_back(jObject); // add col and row to array
						}
					//Add grid position to objects
					j["layers"][i]["objects"][k].push_back(json::object_t::value_type("gridPos", jArray));
				}
			}

			if (j["layers"][i]["name"] == "ActiveBox")
			{
				int minXGrid, minYGrid, maxXGrid, maxYGrid;

				for (int k = 0; k < j["layers"][i]["objects"].size(); ++k) {
					json jArray = json::array(); // create array to store grid position
					int width = j["layers"][i]["objects"][k]["width"];
					int height = j["layers"][i]["objects"][k]["height"];
					float x = j["layers"][i]["objects"][k]["x"];
					float y = j["layers"][i]["objects"][k]["y"];

					minXGrid = int(x) / int(gridWidth);
					minYGrid = int(y) / int(gridHeight);
					maxXGrid = int(x + width) / int(gridWidth);
					maxYGrid = int(y + height) / int(gridHeight);

					for (int i = minXGrid; i <= maxXGrid; i++)
						for (int j = minYGrid; j <= maxYGrid; j++) {
							json jObject = json::basic_json();
							jObject.push_back(json::object_t::value_type("col", i));
							jObject.push_back(json::object_t::value_type("row", j));
							jArray.push_back(jObject); // add col and row to array
						}
					//Add grid position to objects
					j["layers"][i]["objects"][k].push_back(json::object_t::value_type("gridPos", jArray));
				}
			}
		}


		std::ofstream file(fPath);
		file << j;
	}
}