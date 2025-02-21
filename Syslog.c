#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Günlük kaydı için düğüm yapısı
typedef struct LogNode {
    char zaman_damgasi[50];
    char gunluk_seviyesi[20];
    char mesaj[MAX_LINE_LENGTH];
    struct LogNode* sonraki;
} LogNode;

// Bağlı listeye düğüm ekleme fonksiyonu
void gunlukEkle(LogNode** bas, const char* zaman_damgasi, const char* gunluk_seviyesi, const char* mesaj) {
    LogNode* yeniDugum = (LogNode*)malloc(sizeof(LogNode));
    if (!yeniDugum) {
        printf("Bellek tahsis hatası!\n");
        return;
    }
    strcpy(yeniDugum->zaman_damgasi, zaman_damgasi);
    strcpy(yeniDugum->gunluk_seviyesi, gunluk_seviyesi);
    strcpy(yeniDugum->mesaj, mesaj);
    yeniDugum->sonraki = *bas;
    *bas = yeniDugum;
}

// Günlükleri filtreleyerek yazdırma fonksiyonu
void filtreliGunlukleriYazdir(LogNode* bas, const char* filtre_seviyesi) {
    LogNode* mevcut = bas;
    while (mevcut) {
        if (strstr(mevcut->gunluk_seviyesi, filtre_seviyesi)) {
            printf("%s [%s] %s\n", mevcut->zaman_damgasi, mevcut->gunluk_seviyesi, mevcut->mesaj);
        }
        mevcut = mevcut->sonraki;
    }
}

// Bağlı listeyi serbest bırakma fonksiyonu
void gunlukListesiniSerbestBirak(LogNode* bas) {
    LogNode* temp;
    while (bas) {
        temp = bas;
        bas = bas->sonraki;
        free(temp);
    }
}

int main() {
    FILE* dosya = fopen("/var/log/syslog", "r");
    if (!dosya) {
        printf("Syslog dosyası açılamadı!\n");
        return 1;
    }

    LogNode* gunlukListesi = NULL;
    char satir[MAX_LINE_LENGTH];

    // Syslog dosyasını satır satır oku
    while (fgets(satir, sizeof(satir), dosya)) {
        char zaman_damgasi[50], gunluk_seviyesi[20], mesaj[MAX_LINE_LENGTH];
        sscanf(satir, "%49s %19s %[^\n]", zaman_damgasi, gunluk_seviyesi, mesaj);
        gunlukEkle(&gunlukListesi, zaman_damgasi, gunluk_seviyesi, mesaj);
    }
    fclose(dosya);

    printf("ERROR logları:\n");
    filtreliGunlukleriYazdir(gunlukListesi, "ERROR");

    gunlukListesiniSerbestBirak(gunlukListesi);
    return 0;
}
