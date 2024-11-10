/*
Name: Bharatkumar Garsondiya
Student ID: 1303213
Assignment 2, Question 1
*/




#include "q1.h"


/* function will display the primary user interface
    This is already done for you*/
void prompt(void){

  printf("1. Add a new car to the available-for-rent list,\n");
  printf("2. Add a returned car to the available-for-rent list,\n");
  printf("3. Add a returned car to the repair list,\n");
  printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
  printf("5. Rent the first available car,\n");
  printf("6. Print all the lists,\n");
  printf("7. Quit.\n");
  printf("Enter your choice: ");
  //scanf("%d", &choice);
}

/**
 * Inserts a new car into the linked list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @param mileage Integer representing the car's mileage.
 * @param return_date Integer representing the car's return date, you can have -1 represent no return date.
 * @return Pointer to the newly added car in the list.
 */
struct car * insert_to_list(struct car ** head, char plate[], int mileage, int return_date){

    //Check if the plate is already in the list
    struct car *new_car = malloc(sizeof(struct car));

    if (new_car == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    //Check if the plate is already in the list
    strncpy(new_car->plate, plate, 7);

    new_car->plate[7] = '\0';

    new_car->mileage = mileage;
    new_car->return_date = return_date;
    new_car->next = NULL;
    new_car->next = *head;
    *head = new_car;

    return new_car;
}

/**
 * Rents the first available car in the list.
 * @param available_head Pointer to the head of the available-for-rent list.
 * @param rented_head Pointer to the head of the rented list.
 * This function removes the first car from the available-for-rent list and adds it to the rented list.
 */
void rent_first_available_car(struct car **available_head, struct car **rented_head){

    if (*available_head == NULL){
        printf("No car available for rent.\n");
    }

    int return_date;
    printf("Enter the return date(YYMMDD Formate): ");
    scanf("%d", &return_date);

    int year = return_date / 10000;
    int month = (return_date % 10000) / 100;
    int day = return_date % 100;

    //Check if the date is valid
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        printf("Invalid date formate: %d\n", return_date);
        return;
    }


    //Remove the first car from the available list
    struct car *car_to_rent = remove_first_from_list(available_head);
    if (car_to_rent == NULL){
        printf("No car available for rent.\n");
        return;
    }

    car_to_rent->return_date = return_date;

    //Insert the car to the rented list
    struct car *new_rented = insert_to_list(rented_head, car_to_rent->plate, car_to_rent->mileage, car_to_rent->return_date);

    if (new_rented != NULL){
        printf("Car rented successfully: %s\n", new_rented->plate);
    }else{
        printf("Error renting car\n");
        insert_to_list(available_head, car_to_rent->plate, car_to_rent->mileage, car_to_rent->return_date);
    }

    //Free the memory
    free(car_to_rent);

    
}

/**
 * Prints all the cars in the list.
 * @param head Pointer to the head of the list.
 * This function prints out the car details, it should not print return date if it does not exist.
 */
void print_list(struct car *head){

    while (head != NULL)
    {
        printf("Plate: %s, Mileage: %d", head->plate, head->mileage);
        if (head->return_date != -1)
        {
            printf(", Return Date: %d", head->return_date);
        }
        printf("\n");

        //Move to the next car
        head = head->next;
    }
    
}

/**
 * Checks if a car's plate is already in the list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Boolean value indicating if the plate is found.
 */
bool is_plate_in_list(struct car * head, char plate[]){
    while (head != NULL)
    {
        if (strcmp(head->plate, plate) == 0)
        {
            return true;
        }

        //Move to the next car
        head = head->next;
    }
    return false;
}

/**
 * Swaps two cars in the list.
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * Swaps the plate, mileage, and return date of two cars.
 */
void swap(struct car *a, struct car *b){

    int temp_mileage = a->mileage;
    int temp_return_date = a->return_date;
    char temp_plate[8];

    strncpy(temp_plate, a->plate, 8);

    //Swap the values
    a->mileage = b->mileage;
    a->return_date = b->return_date;
    strncpy(a->plate, b->plate, 8);

    b->mileage = temp_mileage;
    b->return_date = temp_return_date;
    strncpy(b->plate, temp_plate, 8);

}

/**
 * Sorts the list of cars based on mileage or return date.
 * @param head Pointer to the head of the list.
 * @param sort_by_mileage Boolean to sort by mileage.
 * @param sort_by_return_date Boolean to sort by return date.
 */
void sort_list(struct car ** head, bool sort_by_mileage, bool sort_by_return_date){
    if (*head == NULL || (*head)->next == NULL){
        return;
    }

    struct car *i, *j;
    bool swapped;

    //Bubble sort
    do{
        swapped = false;
        i = *head;

        //Loop through the list
        while (i->next != NULL){
            j = i->next;
            bool should_swap = false;

            if (sort_by_mileage){
                should_swap = i->mileage > j->mileage;
            }
            else if (sort_by_return_date){
                if (i->return_date != -1 && j->return_date != -1){
                    should_swap = (i -> return_date > j->return_date);
                }
            }

            //Swap the cars
            if (should_swap){
                char temp_plate[8];
                strcpy (temp_plate, i->plate);
                int temp_mileage = i->mileage;
                int temp_return_date = i->return_date;

                strcpy(i->plate, j->plate);
                i->mileage = j->mileage;
                i->return_date = j->return_date;

                strcpy(j->plate, temp_plate);
                j->mileage = temp_mileage;
                j->return_date = temp_return_date;

                swapped = true;
            }
            //Move to the next car
            i = i->next;
        }
        //Continue until no more swaps are needed
    }   while (swapped);
}
/**
 * Removes a car from the list by its plate number.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Pointer to the removed car.
 */
struct car * remove_car_from_list(struct car **head, char plate[]){

    struct car *prev = NULL, *curr = *head;

    //Find the car
    while (curr != NULL && strcmp(curr->plate, plate) != 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        return NULL;
    }

    if (prev == NULL)
    {
        *head = curr->next;
    }else{
        prev->next = curr->next;
    }

    return curr;
}

/**
 * Removes the first car from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car.
 */
struct car * remove_first_from_list(struct car **head){
    
    if (*head == NULL)
    {
        return NULL;
    }

    //Remove the first car
    struct car *temp = *head;
    *head = (*head)->next;

    return temp;
}

/**
 * Calculates the profit based on the mileage difference.
 * @param initial_mileage Integer representing the car's starting mileage.
 * @param final_mileage Integer representing the car's final mileage.
 * @return Double value representing the calculated profit.
 */
double profit_calculator(int initial_mileage, int final_mileage){

    //Rate per mile
    double rate_per_milage = 0.1;

    return (final_mileage - initial_mileage) * rate_per_milage;
}

/**
 * Writes the list of cars to a file.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Writes the details of each car in the list to a file.
 */
void write_list_to_file(char *filename, struct car *head){

    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error opening file: %s .\n", filename);
        return;
    }

    //Write the details of each car to the file
    struct car *current = head;

    while (current != NULL)
    {
        fprintf(file, "%s,%d,%d\n", current->plate, current->mileage, current->return_date);
        current = current->next;
    }

    fclose(file);
}

/**
 * Reads car details from a file and adds them to the list.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Reads data from the file and inserts each car into the list.
 */
void read_file_into_list(char *filename, struct car **head){

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file: %s .\n", filename);
        return;
    }

    char plate[8];
    int mileage, return_date;
    char line[100];

    while(fgets(line, sizeof(line), file) != NULL){
       if(sscanf(line, "%7[^,],%d,%d", plate, &mileage, &return_date) == 3){
        insert_to_list(head, plate, mileage, return_date);
    }
    
}

fclose(file);
}

/**
 * Prints the date in the format of year/month/day.
 * @param date Integer representing the date in YYMMDD format.
 */
void date(int date){

    int year = date / 10000;
    int month = (date % 10000) / 100;
    int day = date % 100;

    //Check if the date is valid
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        printf("Invalid date formate: %d\n", date);
    }
    else
    {
        printf("Date is Valid: Year: %d, Month: %d, Day: %d\n", year, month, day);
    }
}

/**
 * Frees all the memory allocated for the cars in the list.
 * @param head Pointer to the head of the list.
 * Frees each car node in the list.
 */
void free_list(struct car ** head){

    //Free each car in the list
    struct car *current = *head;
    
    while (current != NULL)
    {
        struct car *next = current->next;
        free(current);
        current = next;
    }

    //Set the head to NULL
    *head = NULL;
}

