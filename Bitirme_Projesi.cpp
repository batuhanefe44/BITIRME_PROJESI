#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char isim[50];
    int hesapNo;
    double bakiye;
} Hesap;

void yeniHesapOlustur() {
    Hesap hesap;
    printf("Isim: ");
    scanf("%s", hesap.isim);
    printf("Hesap Numarasi: ");
    scanf("%d", &hesap.hesapNo);
    printf("Baslangic Bakiyesi: ");
    scanf("%lf", &hesap.bakiye);

    FILE *dosya = fopen("hesaplar.txt", "a");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    fprintf(dosya, "%s %d %.2lf\n", hesap.isim, hesap.hesapNo, hesap.bakiye);
    fclose(dosya);

    printf("Yeni hesap olusturuldu.\n");
}

void hesapGuncelle() {
    int hedefHesapNo;
    printf("Guncellenecek hesap numarasini girin: ");
    scanf("%d", &hedefHesapNo);

    FILE *dosya = fopen("hesaplar.txt", "r+");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    Hesap hesap;
    int bulundu = 0;

    while (fscanf(dosya, "%s %d %lf", hesap.isim, &hesap.hesapNo, &hesap.bakiye) != EOF) {
        if (hesap.hesapNo == hedefHesapNo) {
            bulundu = 1;
            printf("Yeni bakiye: ");
            scanf("%lf", &hesap.bakiye);
            fseek(dosya, -sizeof(Hesap), SEEK_CUR);
            fprintf(dosya, "%s %d %.2lf\n", hesap.isim, hesap.hesapNo, hesap.bakiye);
            break;
        }
    }

    fclose(dosya);

    if (bulundu) {
        printf("Hesap guncellendi.\n");
    } else {
        printf("Hesap bulunamadi.\n");
    }
}

void hesapSil() {
    int hedefHesapNo;
    printf("Silinecek hesap numarasini girin: ");
    scanf("%d", &hedefHesapNo);

    FILE *dosya = fopen("hesaplar.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    FILE *geciciDosya = fopen("gecici.txt", "w");
    if (geciciDosya == NULL) {
        printf("Gecici dosya olusturulamadi.\n");
        fclose(dosya);
        return;
    }

    Hesap hesap;
    int bulundu = 0;

    while (fscanf(dosya, "%s %d %lf", hesap.isim, &hesap.hesapNo, &hesap.bakiye) != EOF) {
        if (hesap.hesapNo != hedefHesapNo) {
            fprintf(geciciDosya, "%s %d %.2lf\n", hesap.isim, hesap.hesapNo, hesap.bakiye);
        } else {
            bulundu = 1;
        }
    }

    fclose(dosya);
    fclose(geciciDosya);

    remove("hesaplar.txt");
    rename("gecici.txt", "hesaplar.txt");

    if (bulundu) {
        printf("Hesap silindi.\n");
    } else {
        printf("Hesap bulunamadi.\n");
    }
}

void hesapBilgileriniGoruntule() {
    FILE *dosya = fopen("hesaplar.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    Hesap hesap;

    while (fscanf(dosya, "%s %d %lf", hesap.isim, &hesap.hesapNo, &hesap.bakiye) != EOF) {
        printf("Isim: %s\nHesap Numarasi: %d\nBakiye: %.2lf\n\n", hesap.isim, hesap.hesapNo, hesap.bakiye);
    }

    fclose(dosya);
}

int main() {
    int secim;

    while (1) {
        printf("Banka Hesap Yonetim Sistemi\n");
        printf("---------------------------\n");
        printf("1. Yeni Hesap Olustur\n");
        printf("2. Hesap Guncelle\n");
        printf("3. Hesap Sil\n");
        printf("4. Hesap Bilgilerini Goruntule\n");
        printf("5. Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                yeniHesapOlustur();
                break;
            case 2:
                hesapGuncelle();
                break;
            case 3:
                hesapSil();
                break;
            case 4:
                hesapBilgileriniGoruntule();
                break;
            case 5:
                printf("Programdan cikiliyor...\n");
                exit(0);
            default:
                printf("Gecersiz secim. Tekrar deneyin.\n");
        }

        printf("\n");
    }

    return 0;
}
