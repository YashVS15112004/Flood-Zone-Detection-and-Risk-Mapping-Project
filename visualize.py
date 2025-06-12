import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

def load_map(filename):
    with open(filename) as f:
        rows, cols = map(int, f.readline().split())
        data = list(map(int, f.read().split()))
        return np.array(data).reshape((rows, cols))

def get_largest_zone(zone_map):
    unique, counts = np.unique(zone_map[zone_map != -1], return_counts=True)
    if len(unique) == 0:
        return None
    largest_zone_id = unique[np.argmax(counts)]
    return largest_zone_id

def plot_maps(zone_map, elevation_map):
    largest_zone = get_largest_zone(zone_map)

    fig, axs = plt.subplots(1, 2, figsize=(14, 6))

    im1 = axs[0].imshow(elevation_map, cmap='terrain')
    axs[0].set_title("Elevation Map")
    plt.colorbar(im1, ax=axs[0])
    axs[0].axis("off")

    masked = np.ma.masked_where(zone_map == -1, zone_map)
    cmap = plt.get_cmap('tab20')
    norm = mcolors.BoundaryNorm(np.unique(masked.compressed()), cmap.N)

    zone_colors = cmap(norm(masked.filled(0)))

    highlight = (zone_map == largest_zone)
    zone_colors[highlight] = [1, 0, 0, 1]  

    axs[1].imshow(zone_colors)
    axs[1].set_title(f"Flood Zones (Red = Largest: {largest_zone})")
    axs[1].axis("off")

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    zone_map = load_map("zone_map.txt")
    elevation_map = load_map("elevation_map.txt")
    plot_maps(zone_map, elevation_map)
