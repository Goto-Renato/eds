#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// K -> bitola frontal (front track) 
// L -> entre eixos (wheelbase) 
// dr -> bitola traseira (rear track) 
// lr -> distancia entre o cg e a roda R3 
// r ->  raio da roda 
// valores em milimetros
// V -> velocidade do veiculo em km/h

#define L 2.285 / 1000
#define lr 0.835 / 1000
#define dr 1.35 / 1000
#define r 533.4 / 1000 * M_PI
#define K 1.210 / 1000
#define V 50 / 3.6 
#define to_radians M_PI / 180
#define to_degree 180/M_PI

// calcula o angulo da roda dianteira interna
float inner_steering_angle(int steering_angle)
{
    float angle;    
    angle = atan((L * tan(steering_angle * to_radians))/(L - ((K/2) * tan(steering_angle * to_radians)))) * to_degree;
    return angle;
}

// calcula o angulo da roda dianteira externa
float outer_steering_angle(int steering_angle)
{
    float angle;
    
    angle = atan((L * tan(steering_angle * to_radians))/(L + ((K/2) * tan(steering_angle * to_radians))))*to_degree;
    return angle;
}

// calcula o raio de giro do veiculo
void wheel_turning_radius(float *R1, float *R2, float *R3, float *R4, float inner_angle, float outer_angle, float steering_angle)
{
    *R1 = L/sin(inner_angle * to_radians);
    *R2 = L/sin(outer_angle * to_radians);
    *R3 = (L/tan(steering_angle * to_radians))-(dr/2);
    *R4 = (L/tan(steering_angle * to_radians))+(dr/2);
}

// calcula o raio de giro do centro de gravidade
float cg_radius(float *Rcg, float *R3)
{
    *Rcg = sqrt(pow((*R3 + (dr/2)),2) + pow(lr, 2));
}

// calcula a velocidade das rodas em linha reta
void wheel_speeds_straight(float *W1, float *W2, float *W3, float *W4)
{
    *W1 = *W2 = *W3 = *W4 = ((V) / (r)) * 60;
}

void wheel_speeds(float *W1, float *W2, float *W3, float *W4, float *R1, float *R2, float *R3, float *R4, float *Rcg)
{
    // multiplica por 60 para ter em rpm  
    *W1 = ((V * *R1) / (*Rcg * r)) * 60;
    *W2 = ((V * *R2) / (*Rcg * r)) * 60;
    *W3 = ((V * *R3) / (*Rcg * r)) * 60;
    *W4 = ((V * *R4) / (*Rcg * r)) * 60;
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
    
    wheel_speeds_straight(&W1_speed[0], &W2_speed[0], &W3_speed[0], &W4_speed[0]);
    //printf("RPM wheel 1 = %.3f | RPM wheel 2 = %.3f \n", W1_speed[0], W2_speed[0]);
    printf("%.3f %.3f\n", W1_speed[0], W2_speed[0]);
    
    for(steering_angle = 1; steering_angle < 15; steering_angle++)
    {
        inner_angle = inner_steering_angle(steering_angle);
        outer_angle = outer_steering_angle(steering_angle);        
        wheel_turning_radius(&R1, &R2, &R3, &R4, inner_angle, outer_angle, steering_angle);
        cg_radius(&Rcg, &R3);
        wheel_speeds(&W1_speed[steering_angle], &W2_speed[steering_angle], &W3_speed[steering_angle], &W4_speed[steering_angle], &R1, &R2, &R3, &R4, &Rcg);
        
        //printf("RPM wheel 1 = %.3f | RPM wheel 2 = %.3f \n", W1_speed[steering_angle], W2_speed[steering_angle]);
        
        printf("%.3f %.3f\n", W1_speed[steering_angle], W2_speed[steering_angle]);
    }    
    return 0;
}
