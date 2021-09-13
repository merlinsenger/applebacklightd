// Apple iMac display back light daemon
// Sets the display back light (brightness) according to user input
// Merlin Senger, December 2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

// Sensor sysfs input files
#define FROM "/sys/class/backlight/acpi_video0/brightness"
#define TO   "/sys/class/backlight/radeon_bl0/brightness"

// Minimum and maximum output brightness
#define MIN 1
#define MAX 255

// Maximum string buffer length
#define BUFLEN 4

// Sleep time between brightness adjustment
#define SLEEP 1

// Program output
#define FORMAT0 "applebacklightd: Set backlight from %s to %s\n"
#define FORMAT1 "applebacklightd: ACPI is %i, setting Radeon to %i\n"

// Main function with infinite loop
int main()
{
    FILE *from, *to;
    char str[BUFLEN];
    int acpi, radeon;

    printf(FORMAT0, FROM, TO);

    while(1) {
        // Sleep a while
        sleep(SLEEP);

        // Read ACPI brightness from sysfs
        from = fopen(FROM, "r");
        if (from == NULL) {
            printf("Could not open file %s\n",FROM);
            return 1;
        }
        if (fgets(str, BUFLEN, from) == NULL) {
            printf("Could not read from file %s\n",FROM);
            return 1;
        }
        fclose(from);

        // Continue if value has not changed
        if (acpi == atoi(str)) continue;

        // Calculate new Radeon value
        acpi = atoi(str);
        radeon = acpi * 16;
        if (radeon < MIN) radeon = MIN;
        if (radeon > MAX) radeon = MAX;
        printf(FORMAT1, acpi, radeon);

        // Convert to string and write to Radeon sysfs file
        snprintf(str, BUFLEN, "%i", radeon);
        to = fopen(TO, "w");
        if (to == NULL) {
            printf("Could not open file %s\n",TO);
            printf("Do you have sufficient priviliges (are you root?)\n");
            return 1;
        }
        fputs(str, to);
        fclose(to);
    }

    return 1;
}
