#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// K -> bitola frontal (front track)
// L -> entre eixos (wheelbase)
// dr -> bitola traseira (rear track)
// lr -> distancia entre o cg e a roda R3
// r ->  raio da roda
// V -> velocidade do veiculo

#define L 2.285
#define lr 0.835
#define dr 1.35
#define r 0.395
#define K 1.219
#define V 50

// calcula o angulo da roda dianteira interna
float inner_steering_angle(int steering_angle)
{
    float angle, aux;    
    
    aux = M_PI / 180;
    angle = atan((L * tan(steering_angle * aux))/(L - ((K/2) * tan(steering_angle * aux))));
    return angle;
}

// calcula o angulo da roda dianteira externa
float outer_steering_angle(int steering_angle)
{
    float angle, aux;
    aux = M_PI / 180;
    angle = atan((L * tan(steering_angle * aux))/(L + ((K/2) * tan(steering_angle * aux))));
    return angle;
}

// calcula o raio de giro do veiculo
void wheel_turning_radius(float R1, float R2, float R3, float R4, float inner_angle, float outer_angle, float steering_angle)
{
    float aux;
    aux = M_PI / 180;
    R1 = L/sin(inner_angle * aux);
    R2 = L/sin(outer_angle * aux);
    R3 = (L/tan(steering_angle * aux))-(dr/2);
    R4 = (L/tan(steering_angle * aux))+(dr/2);
}

float cg_radius(float Rcg, float R3)
{
    Rcg = sqrt((R3 + pow(dr/2, 2)) + pow(lr, 2));
}

void wheel_speeds(float W1, float W2, float W3, float W4, float R1, float R2, float R3, float R4, float Rcg)
{
    W1 = (V * R1) / (Rcg * r);
    W2 = (V * R2) / (Rcg * r);
    W3 = (V * R3) / (Rcg * r);
    W4 = (V * R4) / (Rcg * r);
}

int main(void)
{
    // steering_angle -> angulo de esterço do volante
    // inner_angle, outer_angle -> angulos das rodas
    // R1-4 -> raio de giro do veiculo em cada roda sendo R1 fl, R2 fr, R3 rl, R4 rr
    // W1-4 -> velocidade angular das rodas no instante t
    // W1-4_speed -> velocidade das rodas de acordo com o angulo entre 0º e 15º
    
    int steering_angle = 0;
    float inner_angle = 0, outer_angle = 0;
    float R1 = 0, R2 = 0, R3 = 0, R4 = 0, Rcg = 0; 
    float W1_speed[15], W2_speed[15], W3_speed[15], W4_speed[15];
    
    
    for(steering_angle = 0; steering_angle < 15; steering_angle++)
    {
        inner_angle = inner_steering_angle(steering_angle);
        outer_angle = outer_steering_angle(steering_angle);
        printf("%f\n", outer_angle);
        wheel_turning_radius(R1, R2, R3, R4, inner_angle, outer_angle, steering_angle);
        cg_radius(Rcg, R3);
        wheel_speeds(W1_speed[steering_angle], W2_speed[steering_angle], W3_speed[steering_angle], W4_speed[steering_angle], R1, R2, R3, R4, Rcg);
        
        // printf("RPM wheel 1 = %f | RPM wheel 2 = %f \n", W1_speed[steering_angle], W2_speed[steering_angle]);
    }
    
}
