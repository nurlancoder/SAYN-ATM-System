/*
 * ███████╗ █████╗ ██╗   ██╗███╗   ██╗
 * ██╔════╝██╔══██╗╚██╗ ██╔╝████╗  ██║
 * ███████╗███████║ ╚████╔╝ ██╔██╗ ██║
 * ╚════██║██╔══██║  ╚██╔╝  ██║╚██╗██║
 * ███████║██║  ██║   ██║   ██║ ╚████║
 * ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═══╝
 * 
 * SAYN ATM System v2.0
 * Advanced Electronic Banking System
 * 
 * Developer: M.Nurlan
 * LinkedIn: https://www.linkedin.com/in/nurlan-m%C9%99mm%C9%99dli-b6a55b308/
 * Email: nurlanmammadli2@gmail.com
 * 
 * Features:
 * ✓ Multi-language support (Azerbaijani/English)
 * ✓ Cross-platform compatibility
 * ✓ Enhanced security protocols
 * ✓ Transaction history system
 * ✓ Daily withdrawal limits
 * ✓ PIN change functionality
 * ✓ Colorful terminal interface
 * ✓ Input validation & error handling
 * 
 * Version: 2.0
 * Last Updated: August 2025
 * License: MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
    #define PAUSE_COMMAND "pause"
#else
    #include <unistd.h>
    #include <termios.h>
    #define CLEAR_SCREEN "clear"
    #define PAUSE_COMMAND "read -p 'Press Enter to continue...' dummy"
#endif

#define MAX_ATTEMPTS 3
#define MIN_WITHDRAWAL 10.0
#define MAX_WITHDRAWAL 2000.0
#define DAILY_LIMIT 5000.0
#define MAX_TRANSACTIONS 100
#define PIN_LENGTH 4

typedef enum {
    WITHDRAWAL = 1,
    DEPOSIT = 2,
    BALANCE_CHECK = 3,
    TRANSACTION_HISTORY = 4,
    PIN_CHANGE = 5,
    EXIT = 6
} TransactionType;

typedef struct {
    int id;
    TransactionType type;
    double amount;
    double balance_after;
    char timestamp[20];
    char description[50];
} Transaction;

double balans = 750.63;
int PIN = 1234;
double daily_withdrawn = 0.0;
Transaction transactions[MAX_TRANSACTIONS];
int transaction_count = 0;
int session_active = 0;

void initialize_system(void);
void display_header(void);
void display_menu(void);
void display_footer(void);
void clear_screen(void);
void pause_system(void);
void get_timestamp(char* timestamp);
void add_transaction(TransactionType type, double amount, double balance_after, const char* description);
void display_transactions(void);
int authenticate_user(void);
void nagdlashdirma(void);
void mebleg_elave_et(void);
void balans_goster(void);
void pin_deyish(void);
void exit_system(void);
void clear_input_buffer(void);
void set_console_color(const char* color);
void display_welcome_animation(void);
int validate_pin(int pin);
double get_valid_amount(const char* prompt);

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void set_console_color(const char* color) {
    #ifdef _WIN32
        system(color);
    #endif
}

int validate_pin(int pin) {
    return (pin >= 1000 && pin <= 9999);
}

double get_valid_amount(const char* prompt) {
    double amount;
    printf("%s", prompt);
    while (scanf("%lf", &amount) != 1 || amount < 0) {
        printf("Yanlis format! Musbet reqem daxil edin: ");
        clear_input_buffer();
    }
    clear_input_buffer();
    return amount;
}

int main() {
    initialize_system();
    display_welcome_animation();
    
    if (!authenticate_user()) {
        set_console_color("color 4f");
        printf("\n+==============================================+\n");
        printf("|        SISTEME DAXIL OLMA UGURSUZLUGU        |\n");
        printf("+==============================================+\n");
        printf("| X Maksimum cehd sayina catdiniz!            |\n");
        printf("| # Kartiniz tehlukesizlik sebebiyle bloklandi |\n");
        printf("| @ Zehmet olmasa bankla elaqe saxlayin       |\n");
        printf("+==============================================+\n");
        pause_system();
        return 1;
    }
    
    session_active = 1;
    set_console_color("color a0");
    printf("\n+==============================================+\n");
    printf("|         SISTEME UGURLA DAXIL OLDUNUZ         |\n");
    printf("+==============================================+\n");
    printf("| * Tebrikler! Giris ugurlu oldu              |\n");
    printf("| @ SAYN Bank sistemine xos gelmiisiniz       |\n");
    printf("| $ Butun emeliyyatlar heyata kecirile biler  |\n");
    printf("+==============================================+\n");
    pause_system();
    
    int choose;
    do {
        clear_screen();
        display_header();
        display_menu();
        
        printf("-> Seciminizi daxil edin (1-6): ");
        if (scanf("%d", &choose) != 1) {
            set_console_color("color c0");
            printf("X Yanlis format! Zehmet olmasa 1-6 arasi reqem secin.\n");
            clear_input_buffer();
            pause_system();
            continue;
        }
        clear_input_buffer();
        
        switch(choose) {
            case WITHDRAWAL:
                nagdlashdirma();
                break;
            case DEPOSIT:
                mebleg_elave_et();
                break;
            case BALANCE_CHECK:
                balans_goster();
                break;
            case TRANSACTION_HISTORY:
                display_transactions();
                break;
            case PIN_CHANGE:
                pin_deyish();
                break;
            case EXIT:
                exit_system();
                break;
            default:
                set_console_color("color c0");
                printf("\n+==============================================+\n");
                printf("|              YANLIS SECIM!                  |\n");
                printf("+==============================================+\n");
                printf("| !  Zehmet olmasa 1-6 arasi reqem secin     |\n");
                printf("+==============================================+\n");
                pause_system();
        }
    } while(choose != EXIT && session_active);
    
    return 0;
}

void initialize_system(void) {
    #ifdef _WIN32
        SetConsoleOutputCP(65001); 
        system("color 0f");
    #endif
    
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    
    add_transaction(BALANCE_CHECK, 0, balans, "System basladildi");
}

void display_welcome_animation(void) {
    clear_screen();
    set_console_color("color b0");
    
    printf("\n");
    printf("        +===================================+\n");
    printf("        |     SAYN BANK SISTEMI YUKLENIR   |\n");
    printf("        +===================================+\n");
    printf("\n");
    
    printf("        Yuklenir: [");
    for (int i = 0; i < 20; i++) {
        printf("#");
        fflush(stdout);
        #ifdef _WIN32
            Sleep(100);
        #else
            usleep(100000);
        #endif
    }
    printf("] 100%%\n\n");
    
    printf("        * Sistem hazir!\n");
    printf("        # Tehlukesizlik protokollari aktiv\n");
    printf("        $ ATM sistemi ise hazir\n\n");
    
    pause_system();
}

void display_header(void) {
    clear_screen();
    set_console_color("color b0");
    
    printf("\n");
    printf("  ███████╗ █████╗ ██╗   ██╗███╗   ██╗\n");
    printf("  ██╔════╝██╔══██╗╚██╗ ██╔╝████╗  ██║\n");
    printf("  ███████╗███████║ ╚████╔╝ ██╔██╗ ██║\n");
    printf("  ╚════██║██╔══██║  ╚██╔╝  ██║╚██╗██║\n");
    printf("  ███████║██║  ██║   ██║   ██║ ╚████║\n");
    printf("  ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═══╝\n");
    printf("\n");
    printf("+==============================================+\n");
    printf("|       SAYN BANKI - ATM SISTEMI v2.0          |\n");
    printf("|    Gelecein Elektron Bankcilik Sistemi      |\n");
    printf("+==============================================+\n");
    printf("| * Powered by M.Nurlan                       |\n");
    printf("| @ nurlanmammadli2@gmail.com                 |\n");
    printf("+==============================================+\n");
}

void display_menu(void) {
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    
    printf("\n");
    printf("+----------------------------------------------+\n");
    printf("|                @ ESAS MENYU                 |\n");
    printf("+----------------------------------------------+\n");
    printf("|  $ 1 -> Neqdlesdirme (Pul Cixarma)          |\n");
    printf("|  $ 2 -> Hesaba Mebleg Elave Etmek           |\n");
    printf("|  @ 3 -> Cari Balansi Goster                 |\n");
    printf("|  # 4 -> Emeliyyat Tarixcesi                 |\n");
    printf("|  * 5 -> PIN Kod Deyisdir                    |\n");
    printf("|  X 6 -> Sistemden Cixis                     |\n");
    printf("+----------------------------------------------+\n");
    printf("| Cari Balans: %.2f AZN | Tarix: %02d/%02d/%d |\n", 
           balans, ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
    printf("+----------------------------------------------+\n");
}

void clear_screen(void) {
    system(CLEAR_SCREEN);
}

void pause_system(void) {
    #ifdef _WIN32
        system("pause");
    #else
        printf("Davam etmek ucun Enter basin...");
        getchar();
    #endif
}

void get_timestamp(char* timestamp) {
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    sprintf(timestamp, "%02d/%02d/%d %02d:%02d", 
            ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900,
            ltm->tm_hour, ltm->tm_min);
}

void add_transaction(TransactionType type, double amount, double balance_after, const char* description) {
    if (transaction_count >= MAX_TRANSACTIONS) {
        for (int i = 0; i < MAX_TRANSACTIONS - 1; i++) {
            transactions[i] = transactions[i + 1];
        }
        transaction_count = MAX_TRANSACTIONS - 1;
    }
    
    transactions[transaction_count].id = transaction_count + 1;
    transactions[transaction_count].type = type;
    transactions[transaction_count].amount = amount;
    transactions[transaction_count].balance_after = balance_after;
    strcpy(transactions[transaction_count].description, description);
    get_timestamp(transactions[transaction_count].timestamp);
    transaction_count++;
}

int authenticate_user(void) {
    int attempts = 0;
    int pin;
    
    while (attempts < MAX_ATTEMPTS) {
        clear_screen();
        set_console_color("color 60");
        
        printf("\n");
        printf("+==============================================+\n");
        printf("|              * TEHLUKESIZLIK YOXLAMASI      |\n");
        printf("+==============================================+\n");
        printf("|  * PIN kodunuzu daxil edin                  |\n");
        printf("|  !  Qalan cehd: %d                          |\n", MAX_ATTEMPTS - attempts);
        printf("+==============================================+\n");
        printf("\n-> PIN: ");
        
        if (scanf("%d", &pin) != 1) {
            printf("X Yanlis format! 4 reqemli PIN daxil edin.\n");
            clear_input_buffer();
            attempts++;
            pause_system();
            continue;
        }
        clear_input_buffer();
        
        if (pin == PIN) {
            set_console_color("color a0");
            printf("\n* Autentifikasiya ugurlu!\n");
            return 1;
        } else {
            attempts++;
            set_console_color("color c0");
            printf("\n+==============================================+\n");
            printf("|                X YANLIS PIN KOD!           |\n");
            printf("+==============================================+\n");
            if (attempts < MAX_ATTEMPTS) {
                printf("|  # Qalan cehd sayi: %d                     |\n", MAX_ATTEMPTS - attempts);
                printf("|  * Yeniden cehd edin                       |\n");
            } else {
                printf("|  X Maksimum cehd sayi asildi!              |\n");
                printf("|  # Kartiniz bloklanacaq                    |\n");
            }
            printf("+==============================================+\n");
            pause_system();
        }
    }
    return 0;
}

void nagdlashdirma(void) {
    set_console_color("color e0");
    printf("\n+==============================================+\n");
    printf("|            $ NEQDLESDIRME EMELIYYATI        |\n");
    printf("+==============================================+\n");
    printf("| $ Cari balans: %.2f AZN                   |\n", balans);
    printf("| @ Gunluk qalan limit: %.2f AZN            |\n", DAILY_LIMIT - daily_withdrawn);
    printf("| -> Minimum: %.2f AZN | Maksimum: %.2f AZN |\n", MIN_WITHDRAWAL, MAX_WITHDRAWAL);
    printf("+==============================================+\n");
    
    double cb = get_valid_amount("$ Cixarmaq istediyiniz meblegeni daxil edin: ");
    
    if (cb < MIN_WITHDRAWAL) {
        set_console_color("color c0");
        printf("\nX Minimum cixarma meblegi %.2f AZN-dir!\n", MIN_WITHDRAWAL);
    } else if (cb > MAX_WITHDRAWAL) {
        set_console_color("color c0");
        printf("\nX Maksimum cixarma meblegi %.2f AZN-dir!\n", MAX_WITHDRAWAL);
    } else if (cb + daily_withdrawn > DAILY_LIMIT) {
        set_console_color("color c0");
        printf("\nX Gunluk limit asilir! Qalan limit: %.2f AZN\n", DAILY_LIMIT - daily_withdrawn);
    } else if (cb > balans) {
        set_console_color("color c0");
        printf("\n+==============================================+\n");
        printf("|             X YETERSIZ BALANS!              |\n");
        printf("+==============================================+\n");
        printf("| $ Cari balans: %.2f AZN                   |\n", balans);
        printf("| $ Teleb olunan: %.2f AZN                  |\n", cb);
        printf("+==============================================+\n");
    } else {
        balans -= cb;
        daily_withdrawn += cb;
        char desc[50];
        sprintf(desc, "ATM-den %.2f AZN cixarildi", cb);
        add_transaction(WITHDRAWAL, cb, balans, desc);
        
        set_console_color("color a0");
        printf("\n+==============================================+\n");
        printf("|         * EMELIYYAT UGURLA TAMAMLANDI!      |\n");
        printf("+==============================================+\n");
        printf("| $ Cixarilan mebleg: %.2f AZN              |\n", cb);
        printf("| $ Yeni balans: %.2f AZN                   |\n", balans);
        printf("| @ Qebzi saxlayin ve pulunu goturun        |\n");
        printf("+==============================================+\n");
    }
    pause_system();
}

void mebleg_elave_et(void) {
    set_console_color("color d0");
    printf("\n+==============================================+\n");
    printf("|            $ MEBLEG ELAVE ETME             |\n");
    printf("+==============================================+\n");
    printf("| $ Cari balans: %.2f AZN                   |\n", balans);
    printf("+==============================================+\n");
    
    double db = get_valid_amount("$ Elave etmek istediyiniz meblegeni daxil edin: ");
    
    if (db <= 0) {
        set_console_color("color c0");
        printf("\nX Mebleg sifirdan boyuk olmalidir!\n");
    } else {
        balans += db;
        char desc[50];
        sprintf(desc, "Hesaba %.2f AZN elave edildi", db);
        add_transaction(DEPOSIT, db, balans, desc);
        
        set_console_color("color a0");
        printf("\n+==============================================+\n");
        printf("|         * EMELIYYAT UGURLA TAMAMLANDI!      |\n");
        printf("+==============================================+\n");
        printf("| $ Elave olunan mebleg: %.2f AZN           |\n", db);
        printf("| $ Yeni balans: %.2f AZN                   |\n", balans);
        printf("+==============================================+\n");
    }
    pause_system();
}

void balans_goster(void) {
    set_console_color("color 90");
    printf("\n+==============================================+\n");
    printf("|            @ HESAB MELUMATLARI              |\n");
    printf("+==============================================+\n");
    printf("| $ Cari balans: %.2f AZN                   |\n", balans);
    printf("| @ Gunluk cixarilan: %.2f AZN              |\n", daily_withdrawn);
    printf("| * Qalan gunluk limit: %.2f AZN            |\n", DAILY_LIMIT - daily_withdrawn);
    
    char timestamp[20];
    get_timestamp(timestamp);
    printf("| # Yoxlama tarixi: %s                    |\n", timestamp);
    printf("+==============================================+\n");
    
    add_transaction(BALANCE_CHECK, 0, balans, "Balans sorgusu");
    pause_system();
}

void display_transactions(void) {
    set_console_color("color 30");
    printf("\n+==============================================+\n");
    printf("|            # EMELIYYAT TARIXCESI           |\n");
    printf("+==============================================+\n");
    
    if (transaction_count == 0) {
        printf("| X Hec bir emeliyyat tapilmadi               |\n");
    } else {
        printf("\n@ Son %d emeliyyat gosterilir:\n\n", (transaction_count > 10) ? 10 : transaction_count);
        
        for (int i = transaction_count - 1; i >= 0 && i >= transaction_count - 10; i--) {
            printf("+---------------------------------------------+\n");
            printf("| ID: %03d | @ %s                   |\n", transactions[i].id, transactions[i].timestamp);
            
            switch (transactions[i].type) {
                case WITHDRAWAL:
                    printf("| $ Neqdlesdirme: -%.2f AZN                |\n", transactions[i].amount);
                    break;
                case DEPOSIT:
                    printf("| $ Depozit: +%.2f AZN                     |\n", transactions[i].amount);
                    break;
                case BALANCE_CHECK:
                    printf("| @ Balans yoxlamasi                        |\n");
                    break;
                case PIN_CHANGE:
                    printf("| * PIN deyisdirildi                       |\n");
                    break;
            }
            printf("| $ Balans: %.2f AZN                       |\n", transactions[i].balance_after);
            printf("| # %s                                      |\n", transactions[i].description);
            printf("+---------------------------------------------+\n\n");
        }
    }
    pause_system();
}

void pin_deyish(void) {
    set_console_color("color 60");
    printf("\n+==============================================+\n");
    printf("|            * PIN KOD DEYISDIRME            |\n");
    printf("+==============================================+\n");
    
    int current_pin, new_pin, confirm_pin;
    
    printf("* Cari PIN kodunu daxil edin: ");
    if (scanf("%d", &current_pin) != 1 || !validate_pin(current_pin)) {
        printf("X Yanlis format! 4 reqemli PIN daxil edin.\n");
        clear_input_buffer();
        pause_system();
        return;
    }
    clear_input_buffer();
    
    if (current_pin != PIN) {
        set_console_color("color c0");
        printf("\nX Cari PIN kod yanlisdir!\n");
        pause_system();
        return;
    }
    
    printf("+ Yeni PIN kodu daxil edin (4 reqem): ");
    if (scanf("%d", &new_pin) != 1 || !validate_pin(new_pin)) {
        printf("X PIN kod 4 reqemli olmalidir (1000-9999)!\n");
        clear_input_buffer();
        pause_system();
        return;
    }
    clear_input_buffer();
    
    printf("* Yeni PIN kodu tesdiq edin: ");
    if (scanf("%d", &confirm_pin) != 1) {
        printf("X Yanlis format!\n");
        clear_input_buffer();
        pause_system();
        return;
    }
    clear_input_buffer();
    
    if (new_pin != confirm_pin) {
        set_console_color("color c0");
        printf("\nX PIN kodlar uygun gelmier!\n");
        pause_system();
        return;
    }
    
    PIN = new_pin;
    add_transaction(PIN_CHANGE, 0, balans, "PIN kod deyisdirildi");
    
    set_console_color("color a0");
    printf("\n+==============================================+\n");
    printf("|         * PIN KOD UGURLA DEYISDIRILDI!      |\n");
    printf("+==============================================+\n");
    printf("| * Yeni PIN kod teyin edildi                 |\n");
    printf("| * Yeni PIN kodu yadda saxlayin             |\n");
    printf("| ! PIN kodu basqalari ile bolsmeyin        |\n");
    printf("+==============================================+\n");
    pause_system();
}

void exit_system(void) {
    session_active = 0;
    set_console_color("color f0");
    printf("\n+==============================================+\n");
    printf("|           X SISTEMDEN CIXIS                |\n");
    printf("+==============================================+\n");
    printf("| @ SAYN Bankini secdiyiniz ucun tesekkur!    |\n");
    printf("| $ Kartinizi goturun                        |\n");
    printf("| # Qebzlerinizi saxlayin                    |\n");
    printf("+==============================================+\n");
    printf("| $ Son balans: %.2f AZN                    |\n", balans);
    
    char timestamp[20];
    get_timestamp(timestamp);
    printf("| # Cixis tarixi: %s                      |\n", timestamp);
    printf("+==============================================+\n");
    
    display_footer();
    
    printf("\n+==============================================+\n");
    printf("|              #  TEHLUKESIZLIK XATIRLATMASI  |\n");
    printf("+==============================================+\n");
    printf("| $ Kartinizi yaninizda aparin               |\n");
    printf("| @ Qebzlerinizi tehlukesiz yerde saxlayin   |\n");
    printf("| * PIN kodunuzu hec kimle bolusmmeyin        |\n");
    printf("+==============================================+\n");
    
    add_transaction(EXIT, 0, balans, "Sistemden cixis");
    pause_system();
}

void display_footer(void) {
    printf("\n");
    printf("+==============================================+\n");
    printf("|                 @ DEVELOPER INFO            |\n");
    printf("+==============================================+\n");
    printf("| @ Developer: M.Nurlan                       |\n");
    printf("| # LinkedIn: /in/nurlan-memmedli-b6a55b308   |\n");
    printf("| @ Email: nurlanmammadli2@gmail.com          |\n");
    printf("| # Location: Sumqayit, Azerbaijan            |\n");
    printf("+==============================================+\n");
    printf("| (c) 2025 SAYN Banking System v2.0              |\n");
    printf("| @ License: MIT | All rights reserved        |\n");
    printf("+==============================================+\n");
}
