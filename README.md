# 🌊 Flood Zone Detection and Risk Mapping

A practical and efficient implementation of flood zone detection and risk mapping on a 2D terrain using **Non-Linear Data Structures (NLDS)** and **Disjoint Set Union (DSU)**. This project identifies contiguous flood zones, analyzes flood risk levels, and provides an interactive CLI-based visualization tool—ideal for real-world **flood monitoring**, **urban planning**, and **disaster mitigation**.

---

## ✨ Features

### 🔍 Flood Zone Detection
- Detects flooded cells based on user-defined elevation thresholds.
- Groups connected flooded cells (4-directional) into contiguous zones using **Union-Find (DSU)**.

### 📊 Risk Analysis
- Computes each zone’s:
  - Size
  - Average elevation
  - Surrounding resistance
- Estimates relative flood risk levels to aid in **prioritization**.

### 🎨 Visualization
- Interactive **Command-Line Interface (CLI)** menu.
- Flood spread animation and **color-coded risk maps**.
- Export results for easy sharing and further analysis.

### 🚀 Scalability
- Optimized for **large grid-based terrain data**.
- Suitable for real-world use in flood-prone areas and urban planning projects.

---

## 🛠️ Tech Stack

| Category        | Tools/Technologies        |
|----------------|----------------------------|
| Programming     | Python                    |
| Data Structures | Non-Linear DS (DSU)       |
| Visualization   | CLI (Text-based Interface)|
| Data Input      | CSV or similar formats     |

---
