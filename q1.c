#include "q1.h"

/*
 * A basic menu based structure has been provided
*/

int main(void){

    //Our three Linked Lists
    struct car *available_head = NULL;
	struct car *rented_head = NULL;
	struct car *repair_head = NULL;

    int choice;
    char plate[8];
    int mileage;
    double profit;
    struct car *temp_car;

    //Read the data from the file
    read_file_into_list("available.txt", &available_head);
    read_file_into_list("rented.txt", &rented_head);
    read_file_into_list("repair.txt", &repair_head);

    do
    {
        prompt();

        //printf("Enter a Choice: ");
        if (scanf("%d", &choice) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        getchar();
        
        /*
         * You will need to add all the cases
         * Call the appropriate functions
         * You would also need to save data to disc upon exit
         * File Format: plate,mileage,return_date
         * Error Handling needs to happen too
        */

        switch (choice)
        {

        //Add a new car to the available-for-rent list
        case 1:
            printf("Enter the plate number (7 characters): ");
            if (scanf("%7s", plate) != 1)
            {
                printf("Invalid input. Please try again.\n");
                continue;
            }
            if (strlen(plate) != 7)
            {
                printf("Invalid plate number. Please try again.\n");
                continue;
            }
            printf("Enter the mileage: ");
            if (scanf("%d", &mileage) != 1)
            {
                printf("Invalid input. Please try again.\n");
                continue;
            }
            if(is_plate_in_list(available_head, plate) || 
                is_plate_in_list(rented_head, plate) || 
                is_plate_in_list(repair_head, plate)){
                printf("Car with the same plate number already exists in the system.\n");
                }else{
                    if (insert_to_list(&available_head, plate, mileage, -1) != NULL){
                        printf("Car added Sucsessfully!.\n");
                    }
                }
            break;
        
        //Add a returned car to the available-for-rent list
        case 2:
            printf("Enter the plat number (7 characters): ");
            scanf("%s", plate);
            printf("Enter the mileage: ");
            scanf("%d", &mileage);
            temp_car = remove_car_from_list(&rented_head, plate);
            if (temp_car != NULL){
                profit = profit_calculator(temp_car->mileage, mileage);
                printf("The profit for this car is: %.2lf\n", profit);
                available_head = insert_to_list(&available_head, plate, mileage, -1);
                free(temp_car);
            }else{
                printf("Car not found in the rented list.\n");
            }
            break;

        //Add a returned car to the repair list
        case 3:
            printf("Enter the plat number of returned car (7 characters): ");
            scanf("%s", plate);
            temp_car = remove_car_from_list(&rented_head, plate);
            if (temp_car != NULL){
                repair_head = insert_to_list(&repair_head, plate, temp_car->mileage, -1);
                printf("Car added to the repair list.\n");
                free(temp_car);
            }else{
                printf("Car not found in the repair list.\n");
            }
            break;

        //Transfer a car from the repair list to the available-for-rent list
        case 4:
            printf("Enter the plat number of the car to be transferred (7 characters): ");
            scanf("%s", plate);
            temp_car = remove_car_from_list(&repair_head, plate);
            if (temp_car != NULL){
                available_head = insert_to_list(&available_head, plate, temp_car->mileage, -1);
                printf("Car transferred to the available-for-rent list.\n");
                free(temp_car);
            }else{
                printf("Car not found in the repair list.\n");
            }
            break;

        //Rent the first available car
        case 5:
            rent_first_available_car(&available_head, &rented_head);
            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            break;

        //Print all the lists
        case 6:
            //Print all the lists
            printf("Available for rent:\n");
            if(available_head != NULL){
                sort_list(&available_head, true, false);
            }
            print_list(available_head);

            printf("Rented:\n");
            print_list(rented_head);

            printf("Repair:\n");
            print_list(repair_head);
            break;

        //Quit
        case 7:
            //quit and save to file
            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);

            free_list(&available_head);
            free_list(&rented_head);
            free_list(&repair_head);

            printf("Data saved! Exiting...\n");
            exit(0);
            break;

        //Invalid choice
        default:
            printf("Invalid choice. Please try again.\n");

        }

        
    } while (true);
    

    return 0;
}





