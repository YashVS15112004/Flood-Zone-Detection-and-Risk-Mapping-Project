#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;


int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};


class DisjointSet {
private:
    vector<int> parent, rank;

public:
    DisjointSet(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return;
        if (rank[xr] < rank[yr]) parent[xr] = yr;
        else if (rank[xr] > rank[yr]) parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
    }
};

class Grid {
private:
    vector<vector<int>> grid;
    vector<vector<int>> elevation;
    int rows, cols;

public:
    void inputGrid() {
        cout << "Enter number of rows and columns: ";
        cin >> rows >> cols;
        grid.resize(rows, vector<int>(cols));
        elevation.resize(rows, vector<int>(cols));

        cout << "Enter flood map (1 = flooded, 0 = safe):\n";
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                cin >> grid[i][j];

        cout << "Enter elevation data:\n";
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                cin >> elevation[i][j];
    }

    void generateRandom(int r, int c) {
        rows = r;
        cols = c;
        grid.resize(rows, vector<int>(cols));
        elevation.resize(rows, vector<int>(cols));
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                grid[i][j] = rand() % 2;
                elevation[i][j] = rand() % 100 + 1;
            }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int getValue(int i, int j) const { return grid[i][j]; }
    int getElevation(int i, int j) const { return elevation[i][j]; }
    bool isInBounds(int i, int j) const {
        return i >= 0 && i < rows && j >= 0 && j < cols;
    }

    void display() const {
        cout << "\nFlood Map (# = Flooded, . = Safe):\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << (grid[i][j] ? "# " : ". ");
            cout << endl;
        }

        cout << "\nElevation Map:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << setw(3) << elevation[i][j] << " ";
            cout << endl;
        }
    }
};



class FloodAnalyzer {
private:
    Grid& grid;
    DisjointSet* ds;
    vector<vector<int>> zoneMap;
    map<int, int> zoneSize;
    map<int, int> zoneRisk;
    int zoneCount;

    int index(int i, int j) {
        return i * grid.getCols() + j;
    }

    
public:
    FloodAnalyzer(Grid& g) : grid(g) {
        int total = grid.getRows() * grid.getCols();
        ds = new DisjointSet(total);
        zoneMap.resize(grid.getRows(), vector<int>(grid.getCols(), -1));
        zoneCount = 0;
    }

    ~FloodAnalyzer() {
        delete ds;
    }

    void detectFloodZones() {
        int rows = grid.getRows();
        int cols = grid.getCols();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid.getValue(i, j) == 1) {
                    for (int d = 0; d < 4; d++) {
                        int ni = i + dx[d], nj = j + dy[d];
                        if (grid.isInBounds(ni, nj) && grid.getValue(ni, nj) == 1)
                            ds->unionSets(index(i, j), index(ni, nj));
                    }
                }
            }
        }

        set<int> uniqueRoots;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid.getValue(i, j) == 1) {
                    int root = ds->find(index(i, j));
                    zoneMap[i][j] = root;
                    uniqueRoots.insert(root);
                    zoneSize[root]++;
                    zoneRisk[root] += grid.getElevation(i, j);
                }
            }
        }

        zoneCount = uniqueRoots.size();
    }

    const vector<vector<int>>& getZoneMap() const {
        return zoneMap;
    }

    void displayRiskMap() {
        cout << "\nZone Risk Map (Zone ID mod 10):\n";
        for (int i = 0; i < grid.getRows(); i++) {
            for (int j = 0; j < grid.getCols(); j++) {
                if (zoneMap[i][j] != -1)
                    cout << zoneMap[i][j] % 10 << " ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
    }

    void displayZoneStats() {
        cout << "\n--- Flood Zone Statistics ---\n";
        cout << left << setw(10) << "Zone ID" << setw(10) << "Size" << setw(15) << "Avg Elevation" << endl;
        for (auto& pair : zoneSize) {
            int id = pair.first;
            int size = pair.second;
            float avg = (float)zoneRisk[id] / size;
            cout << left << setw(10) << id << setw(10) << size << setw(15) << fixed << setprecision(2) << avg << endl;
        }
        cout << "\nTotal Flood Zones Detected: " << zoneCount << endl;
    }

    void detailedZoneMap() {
        cout << "\nDetailed Zone Mapping (Root IDs):\n";
        for (int i = 0; i < grid.getRows(); i++) {
            for (int j = 0; j < grid.getCols(); j++) {
                if (zoneMap[i][j] != -1)
                    cout << setw(4) << zoneMap[i][j];
                else
                    cout << "   .";
            }
            cout << endl;
        }
    }
    
    
};


void exportZoneMapToFile(const Grid& grid, const vector<vector<int>>& zoneMap, const string& filename) {
    ofstream fout(filename);
    int rows = grid.getRows(), cols = grid.getCols();
    fout << rows << " " << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fout << zoneMap[i][j] << " ";
        }
        fout << "\n";
    }
    fout.close();
}
void exportElevationToFile(const Grid& grid, const string& filename) {
    ofstream fout(filename);
    int rows = grid.getRows(), cols = grid.getCols();
    fout << rows << " " << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            fout << grid.getElevation(i, j) << " ";
        fout << "\n";
    }
    fout.close();
}


int main() {
    srand(time(0));
    cout << "=== Flood Zone Detection & Risk Mapping ===" << endl;

    Grid g;
    int choice;
    cout << "1. Manual Input\n2. Random Grid\nChoose option: ";
    cin >> choice;

    if (choice == 1)
        g.inputGrid();
    else {
        int r, c;
        cout << "Enter rows and columns: ";
        cin >> r >> c;
        g.generateRandom(r, c);
    }

    g.display();

    FloodAnalyzer analyzer(g);
    analyzer.detectFloodZones();
    analyzer.displayRiskMap();
    analyzer.displayZoneStats();
    analyzer.detailedZoneMap();

    exportZoneMapToFile(g, analyzer.getZoneMap(), "zone_map.txt");
    exportElevationToFile(g, "elevation_map.txt");


    return 0;
}
