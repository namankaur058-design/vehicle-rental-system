
#include <stdio.h>
#include <string.h>

#define MAX 20
#define TOTAL 5

struct Vehicle {
    int id;
    char name[30];
    float price;
    int available;
};

struct Booking {
    int bookingID;
    char customer[50];
    char phone[15];
    int vehicleID;
    int days;
    float amount;
    int active;
};

struct Vehicle vehicles[TOTAL] = {
    {1, "Swift", 1500, 1},
    {2, "Creta", 2500, 1},
    {3, "Thar", 3000, 1},
    {4, "Activa", 500, 1},
    {5, "Royal Enfield", 1200, 1}
};

struct Booking bookings[MAX];

int bookingCount = 0;
int totalEarnings = 0;

// Display available vehicles
void displayVehicles() {
    printf("\n------ AVAILABLE VEHICLES ------\n");
    printf("ID\tVehicle\t\tPrice/Day\n");

    for (int i = 0; i < TOTAL; i++) {
        if (vehicles[i].available) {
            printf("%d\t%-16s Rs. %.2f\n",
                   vehicles[i].id,
                   vehicles[i].name,
                   vehicles[i].price);
        }
    }
}

// Rent a vehicle
void rentVehicle() {
    if (bookingCount >= MAX) {
        printf("\nBooking limit reached!\n");
        return;
    }

    char name[50], phone[15];
    int id, days, index = -1;

    displayVehicles();

    printf("\nEnter customer name: ");
    scanf(" %49[^\n]", name);

    printf("Enter phone number: ");
    scanf("%14s", phone);

    printf("Enter vehicle ID: ");
    scanf("%d", &id);

    for (int i = 0; i < TOTAL; i++) {
        if (vehicles[i].id == id && vehicles[i].available) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\nVehicle not available or invalid ID!\n");
        return;
    }

    printf("Enter rental days: ");
    scanf("%d", &days);

    if (days <= 0) {
        printf("\nInvalid number of days!\n");
        return;
    }

    float amount = vehicles[index].price * days;

    bookings[bookingCount].bookingID = bookingCount + 101;
    strcpy(bookings[bookingCount].customer, name);
    strcpy(bookings[bookingCount].phone, phone);
    bookings[bookingCount].vehicleID = id;
    bookings[bookingCount].days = days;
    bookings[bookingCount].amount = amount;
    bookings[bookingCount].active = 1;

    vehicles[index].available = 0;

    totalEarnings += amount;
    bookingCount++;

    printf("\n------ RENTAL BILL ------\n");
    printf("Booking ID: %d\n", bookingCount + 100);
    printf("Customer: %s\n", name);
    printf("Phone: %s\n", phone);
    printf("Vehicle: %s\n", vehicles[index].name);
    printf("Rental Days: %d\n", days);
    printf("Total Amount: Rs. %.2f\n", amount);
    printf("\nBooking Successful!\n");
}

// Return a vehicle
void returnVehicle() {
    int id, found = 0;

    printf("\nEnter Booking ID: ");
    scanf("%d", &id);

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == id &&
            bookings[i].active == 1) {

            bookings[i].active = 0;

            for (int j = 0; j < TOTAL; j++) {
                if (vehicles[j].id == bookings[i].vehicleID) {
                    vehicles[j].available = 1;
                    break;
                }
            }

            printf("\nVehicle returned successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nInvalid booking ID or vehicle already returned!\n");
    }
}

// Display booking details
void displayBookings() {
    if (bookingCount == 0) {
        printf("\nNo bookings available!\n");
        return;
    }

    printf("\n------ BOOKING DETAILS ------\n");

    for (int i = 0; i < bookingCount; i++) {
        printf("\nBooking ID: %d\n", bookings[i].bookingID);
        printf("Customer: %s\n", bookings[i].customer);
        printf("Phone: %s\n", bookings[i].phone);
        printf("Vehicle ID: %d\n", bookings[i].vehicleID);
        printf("Rental Days: %d\n", bookings[i].days);
        printf("Amount: Rs. %.2f\n", bookings[i].amount);

        if (bookings[i].active)
            printf("Status: Active\n");
        else
            printf("Status: Returned\n");
    }
}

// Admin dashboard
void adminDashboard() {
    int activeBookings = 0;

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].active)
            activeBookings++;
    }

    printf("\n------ ADMIN DASHBOARD ------\n");
    printf("Total Bookings: %d\n", bookingCount);
    printf("Active Bookings: %d\n", activeBookings);
    printf("Total Earnings: Rs. %d\n", totalEarnings);
}

int main() {
    int choice;

    do {
        printf("\n================================\n");
        printf("   VEHICLE RENTAL MANAGEMENT\n");
        printf("================================\n");
        printf("1. View Available Vehicles\n");
        printf("2. Rent a Vehicle\n");
        printf("3. Return a Vehicle\n");
        printf("4. View Booking Details\n");
        printf("5. Admin Dashboard\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayVehicles();
                break;

            case 2:
                rentVehicle();
                break;

            case 3:
                returnVehicle();
                break;

            case 4:
                displayBookings();
                break;

            case 5:
                adminDashboard();
                break;

            case 6:
                printf("\nThank you for using our system!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}
