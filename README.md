## 🌊 Flood Zone Detection and Risk Mapping
A practical implementation of flood zone detection and risk mapping on a 2D terrain using Non-Linear Data Structures (NLDS) and Disjoint Set Union (DSU). This project efficiently identifies contiguous flood zones, analyzes flood risk levels, and provides a CLI-based visualization tool—ideal for real-world flood monitoring, urban planning, and disaster mitigation.

## ✨ Features
### Flood Zone Detection:
Identifies flooded cells based on user-defined elevation thresholds.
Groups connected flooded cells (4-directional) into contiguous zones using Union-Find (DSU).
### Risk Analysis:
Computes each zone’s size, average elevation, and surrounding resistance.
Estimates relative flood risk levels for prioritization.
### Visualization:
Interactive CLI menu with flood spread animation.
Color-coded risk maps.
Export functionality for easy sharing and analysis.
### Scalability:
Efficient processing of large grid-based terrain data.
Supports real-world scenarios in flood monitoring and urban planning.
## 🛠️ Tech Stack
Programming Language: Python
Data Structures: Non-Linear Data Structures (DSU)
Visualization: Command-Line Interface (CLI)
File Handling: CSV (or similar) for elevation data
