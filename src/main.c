/* BillBuddy - Grocery & Restaurant Bill Calculator (C console version)
   Features: item menu, editable price, stock tracking, delivery,
   cash/UPI payment, printable bill and daily sales file.            */
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 10
#define GST 5.0f                 /* GST percentage */

struct Item {                    /* one product / dish */
    char  name[30];
    float price;
    int   stock;
};

struct Item grocery[MAX] = {
    {"Rice 1kg",70,50},{"Milk 1L",56,50},{"Bread",40,50},{"Eggs (12)",84,50},
    {"Tomato 1kg",30,50},{"Onion 1kg",35,50},{"Potato 1kg",28,50},
    {"Sugar 1kg",48,50},{"Tea 250g",120,50},{"Apples 1kg",180,50}};
struct Item restaurant[MAX] = {
    {"Paneer Butter Masala",240,30},{"Veg Biryani",180,30},{"Masala Dosa",110,30},
    {"Margherita Pizza",280,30},{"Veg Burger",140,30},{"White Sauce Pasta",190,30},
    {"Cold Coffee",90,30},{"Gulab Jamun",70,30}};

/* Core formula: total = subtotal + GST + delivery */
float calcBill(float subtotal, float gstPercent, float delivery) {
    return subtotal + subtotal * gstPercent / 100 + delivery;
}

void showMenu(struct Item *it, int n) {
    int i;
    printf("\n No  Item                      Price   Stock\n");
    for (i = 0; i < n; i++)
        printf(" %-3d %-25s %6.2f  %d\n", i + 1, it[i].name, it[i].price, it[i].stock);
}

/* Print a simple black & white bill */
void printBill(char *shop, struct Item *it, int n, int *qty, int home,
               char *addr, float delivery, int upi, char *ref) {
    int i; float sub = 0; time_t t = time(NULL);
    printf("\n==============================\n   %s\n==============================\n", shop);
    printf("Date: %s", ctime(&t));
    printf("Order: %s\n", home ? "Home Delivery" : "Counter");
    if (home) printf("Address: %s\n", addr);
    printf("------------------------------\n");
    for (i = 0; i < n; i++)
        if (qty[i] > 0) {
            printf("%-20s %2d x %6.2f = %8.2f\n", it[i].name, qty[i], it[i].price, qty[i] * it[i].price);
            sub += qty[i] * it[i].price;
            it[i].stock -= qty[i];            /* reduce stock */
        }
    printf("------------------------------\nSubtotal : %.2f\nGST 5%%   : %.2f\n", sub, sub * GST / 100);
    if (home) printf("Delivery : %.2f\n", delivery);
    printf("TOTAL    : %.2f\n", calcBill(sub, GST, delivery));
    printf("Paid by  : %s %s\n", upi ? "UPI" : "Cash", upi ? ref : "");
    printf("------------------------------\n   Thank You! Visit Again\n==============================\n");
}

int main() {
    struct Item *it; char shop[40], file[30], addr[60] = "", ref[40] = "", ans;
    int n, type, ch, i, q, qty[MAX] = {0}, home = 0, upi = 0; float delivery = 0, price;

    printf("1. Grocery Store\n2. Restaurant\nChoose: ");
    scanf("%d", &type);
    if (type == 1) { it = grocery; n = 10; strcpy(shop, "MY GROCERY STORE"); strcpy(file, "sales_grocery.txt"); }
    else           { it = restaurant; n = 8; strcpy(shop, "MY RESTAURANT");   strcpy(file, "sales_restaurant.txt"); }

    do {                                          /* main menu loop */
        showMenu(it, n);
        printf("\n1.Add item  2.Edit price  3.Checkout  Choose: ");
        scanf("%d", &ch);
        if (ch == 1) {
            printf("Item no and quantity: "); scanf("%d %d", &i, &q);
            if (i >= 1 && i <= n && q <= it[i-1].stock) qty[i-1] += q;
            else printf("Invalid item or not enough stock!\n");
        } else if (ch == 2) {
            printf("Item no and new price: "); scanf("%d %f", &i, &price);
            if (i >= 1 && i <= n) it[i-1].price = price;
        }
    } while (ch != 3);

    printf("Home delivery? (y/n): "); scanf(" %c", &ans);
    if (ans == 'y') { home = 1; printf("Address: "); scanf(" %[^\n]", addr);
                      printf("Delivery charge: "); scanf("%f", &delivery); }
    printf("Payment 1.Cash 2.UPI: "); scanf("%d", &i);
    if (i == 2) { upi = 1; printf("UPI Id / Transaction Id: "); scanf("%s", ref); }

    printBill(shop, it, n, qty, home, addr, delivery, upi, ref);

    /* save today's sale to file */
    float sub = 0; for (i = 0; i < n; i++) sub += qty[i] * it[i].price;
    FILE *fp = fopen(file, "a");
    if (fp) { fprintf(fp, "%.2f\n", calcBill(sub, GST, delivery)); fclose(fp); }
    return 0;
}
