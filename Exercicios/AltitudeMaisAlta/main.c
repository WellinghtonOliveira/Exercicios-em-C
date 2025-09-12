#include <stdio.h>

int largestAltitude();

int main() {


    int gainSize = 5;
    int gain[5] = {-5,1,5,0,-7};
    
    printf("%d", largestAltitude(gain, gainSize));

    return 0;
}


int largestAltitude(int* gain, int gainSize) {
    int altitude = 0;
    int maxAltitude = 0;

    for (int i = 0; i < gainSize; i++) {
        altitude += gain[i];
        if (altitude > maxAltitude)
            maxAltitude = altitude;
    }

    return maxAltitude;
}
