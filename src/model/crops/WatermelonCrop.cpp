#include "WatermelonCrop.h"

#define MIN_MELONS 2
#define MAX_MELONS 5
#define MIN_SEEDS 1
#define MAX_SEEDS 3

float WatermelonCrop::getMinimumGrowthToHarvest() {
	return 0.5f;
}
void WatermelonCrop::harvest(ItemContainer* ic) {
	int melons = roll(MIN_MELONS, MAX_MELONS);
	int seeds = roll(MIN_SEEDS, MAX_SEEDS);
	ic->add(ItemStack::create(WATERMELON_SLICE, melons));
	ic->add(ItemStack::create(WATERMELON_SEED, seeds));
}