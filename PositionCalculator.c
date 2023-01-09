#include <stdio.h>
#include <math.h>
#include <string.h>

struct user_t{
    char name[50];
    double latitude, longitude, altitude, time;
};

struct distances{
    char name[50];
    double distance;
};

int n;

void scan_user(struct user_t* our_user);
void scan_user_file(struct user_t other_user[50]);
void fill_users(struct user_t* our_user,struct user_t other_user[50]);
void position_difference(struct user_t* our_user,struct user_t other_user[50], struct distances struct_array[50]);
struct distances closest_user(struct distances *struct_array);

int main(void) {
    struct user_t our_user;
    struct user_t other_user[50];
    struct distances struct_array[50];

    fill_users(&our_user, other_user);
    position_difference(&our_user, other_user, struct_array);
    struct distances close_user = closest_user(struct_array);
    printf("name:%s\ndistance:%lf", close_user.name, close_user.distance);
    return 0;
}

void fill_users(struct user_t* our_user,struct user_t other_user[50]){

    scan_user(our_user);
    scan_user_file(other_user);
}

void position_difference(struct user_t* our_user,struct user_t other_user[50], struct distances struct_array[50]){

    double latitude, longitude, altitude, result;

    for(int i = 0; i < n; i++){
        latitude = our_user->latitude-other_user[i].latitude;
        longitude = our_user->longitude-other_user[i].longitude;
        altitude = our_user->altitude-other_user[i].altitude;
        result = pow(latitude,2) + pow(longitude,2) + pow(altitude,2);
        struct_array[i].distance = sqrt(result);
        strcpy(struct_array[i].name, other_user[i].name);
    }
}

void scan_user(struct user_t* our_user){

    printf("Enter name of user:\n");
    scanf("%s", our_user->name);
    printf("Enter latitude of user:\n");
    scanf("%lf", &our_user->latitude);
    printf("Enter longitude of user:\n");
    scanf("%lf", &our_user->longitude);
    printf("Enter altitude of user:\n");
    scanf("%lf", &our_user->altitude);
    printf("Enter elapsed time of user in nanoseconds:\n");
    scanf("%lf", &our_user->time);
}

void scan_user_file(struct user_t other_user[50]){

    FILE *input_file;
    char directory[50];

    printf("Enter directory of the file:\n");
    scanf("%s", directory);
    input_file = fopen(directory, "r");
    if(input_file == NULL){
        printf("File not found\n");
    }
    else{
        fscanf(input_file, "%d", &n);
        for(int i = 0; i < n; i++){
            fscanf(input_file, "%s %lf %lf %lf %lf", other_user[i].name, &other_user[i].latitude, &other_user[i].longitude, &other_user[i].altitude, &other_user[i].time);
        }
    }
    fclose(input_file);
}

struct distances closest_user(struct distances struct_array[50]){
    double MIN = struct_array[0].distance;
    struct distances closest;
    for(int i = 1; i < n; i++){
        if(MIN > struct_array[i].distance){
        MIN = struct_array[i].distance;
        closest = struct_array[i];
        }
    }
    return closest;
}

