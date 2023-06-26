#include "../headers/calcula_distancia.h"
#include <stdio.h>
#include <assert.h>

// Código inspirado em https://www.geeksforgeeks.org/program-distance-two-points-earth/
static double para_radianos (double angulo){
    return (angulo /(180/3.14159));
}

double calcula_distancia(double lat1, double long1, double lat2, double long2){
    lat1 = para_radianos(lat1);
    long1 = para_radianos(long1);
    lat2 = para_radianos(lat2);
    long2 = para_radianos(long2);

    double dlat = lat1-lat2;
    double dlong = long1-long2;

    double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);

    return(2 * asin(sqrt(ans)) * 6371);     // 6371 é o raio da terra em KM
}
void calcula_distancia_testa() {
    double lat2 = 52.520008;   // Berlim, Alemanha
    double long2 = 13.404954;
    double lat1 = 37.7749;     // São Francisco, EUA
    double long1 = -122.4194;


    double distancia = calcula_distancia(lat1, long1, lat2, long2);
    assert (distancia == calcula_distancia(lat2, long2, lat1, long1));
    printf("Distância entre Berlim e São Francisco: %.2f km\n", distancia);
}