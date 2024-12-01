#include "cubiomes/finders.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <seed>\n", argv[0]);
        return 1;
    }

    // Get the seed from the command line
    int64_t seed = atoll(argv[1]);

    // Define world boundaries for search
    int startX = -5000, endX = 5000;
    int startZ = -5000, endZ = 5000;

    // Initialize biome generator
    LayerStack layers;
    setupGenerator(&layers, MC_1_16); // Minecraft 1.16 version
    applySeed(&layers, seed);

    // Initialize structure finders
    StructureConfig shipwreckConfig = SHIPWRECK_CONFIG;
    StructureConfig treasureConfig = BURIED_TREASURE_CONFIG;

    // Output JSON structure
    printf("{\"shipwrecks\":[");

    int first = 1;
    for (int x = startX; x < endX; x += 16) {
        for (int z = startZ; z < endZ; z += 16) {
            Pos pos;

            // Check for shipwrecks
            if (getStructurePos(shipwreckConfig, seed, x, z, &pos)) {
                if (!first) printf(",");
                printf("{\"x\":%d,\"z\":%d}", pos.x, pos.z);
                first = 0;
            }
        }
    }

    printf("],\"treasures\":[");

    first = 1;
    for (int x = startX; x < endX; x += 16) {
        for (int z = startZ; z < endZ; z += 16) {
            Pos pos;

            // Check for buried treasures
            if (getStructurePos(treasureConfig, seed, x, z, &pos)) {
                if (!first) printf(",");
                printf("{\"x\":%d,\"z\":%d}", pos.x, pos.z);
                first = 0;
            }
        }
    }

    printf("]}");
    return 0;
}
