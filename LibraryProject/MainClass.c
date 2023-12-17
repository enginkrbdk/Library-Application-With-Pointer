#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_KITAP_SAYISI 100
#define MAX_UYE_SAYISI 50
#define MAX_ODUNC_VERILEN_SAYISI 50
#define MAX_RAFLAR 10
#define MAX_KITAP_RAFA 20

typedef struct {
    char ad[50];
    char yazar[50];
    int id;
} Kitap;

typedef struct {
    char ad[50];
    int uye_id;
} Uye;

typedef struct {
    int kitap_id;
    int uye_id;
} Odunc;

typedef struct {
    int raf_id;
    Kitap kitaplar[MAX_KITAP_RAFA];
    int kitapSayisi;
} KitapRafi;

void dosyadanOku(Kitap kitaplar[], Uye uyeler[], Odunc oduncVerilen[], KitapRafi raflar[], int* kitapSayisi, int* uyeSayisi, int* oduncSayisi, int* rafSayisi);
void dosyayaYaz(Kitap kitaplar[], Uye uyeler[], Odunc oduncVerilen[], KitapRafi raflar[], int kitapSayisi, int uyeSayisi, int oduncSayisi, int rafSayisi);
void menuGoster();
void kitapEkle(Kitap kitaplar[], int* kitapSayisi);
void uyeEkle(Uye uyeler[], int* uyeSayisi);
void oduncVer(Odunc oduncVerilen[], int* oduncSayisi, Kitap kitaplar[], Uye uyeler[], int kitapSayisi, int uyeSayisi);
void kitapListele(Kitap kitaplar[], int kitapSayisi);
void uyeListele(Uye uyeler[], int uyeSayisi);
void oduncListele(Odunc oduncVerilen[], int oduncSayisi, Kitap kitaplar[], Uye uyeler[]);
void kitapIade(Odunc oduncVerilen[], int* oduncSayisi, Kitap kitaplar[], Uye uyeler[], int kitapSayisi, int uyeSayisi);
void rafEkle(KitapRafi raflar[], int* rafSayisi);
void kitabiRafaEkle(KitapRafi raflar[], int rafSayisi, Kitap kitaplar[], int kitapSayisi);
void rafListele(KitapRafi raflar[], int rafSayisi, Kitap kitaplar[], int kitapSayisi);

int main() {
    Kitap kitaplar[MAX_KITAP_SAYISI];
    Uye uyeler[MAX_UYE_SAYISI];
    Odunc oduncVerilen[MAX_ODUNC_VERILEN_SAYISI];
    KitapRafi raflar[MAX_RAFLAR];

    int kitapSayisi = 0, uyeSayisi = 0, oduncSayisi = 0, rafSayisi = 0;

    dosyadanOku(kitaplar, uyeler, oduncVerilen, raflar, &kitapSayisi, &uyeSayisi, &oduncSayisi, &rafSayisi);

    int secim;
    do {
        menuGoster();
        printf("Seciminizi yapiniz: ");
        scanf("%d", &secim);

        switch (secim) {
        case 1:
            kitapEkle(kitaplar, &kitapSayisi); 
            break;
        case 2:
            uyeEkle(uyeler, &uyeSayisi);
            break;
        case 3:
            kitapListele(kitaplar, kitapSayisi);
            oduncVer(oduncVerilen, &oduncSayisi, kitaplar, uyeler, kitapSayisi, uyeSayisi);
            break;
        case 4:
            kitapListele(kitaplar, kitapSayisi);
            break;
        case 5:
            uyeListele(uyeler, uyeSayisi);
            break;
        case 6:
            oduncListele(oduncVerilen, oduncSayisi, kitaplar, uyeler);
            break;
        case 7:
            kitapIade(oduncVerilen, &oduncSayisi, kitaplar, uyeler, kitapSayisi, uyeSayisi);
            break;
        case 8:
            rafEkle(raflar, &rafSayisi);
            break;
        case 9:
            kitabiRafaEkle(raflar, rafSayisi, kitaplar, kitapSayisi);
            break;
        case 10:
            rafListele(raflar, rafSayisi, kitaplar, kitapSayisi);
            break;
        case 0:
            dosyayaYaz(kitaplar, uyeler, oduncVerilen, raflar, kitapSayisi, uyeSayisi, oduncSayisi, rafSayisi);
            printf("Programdan cikiliyor.\n");
            break;
        default:
            printf("Gecersiz secim! Lutfen tekrar deneyin.\n");
        }
    } while (secim != 0);

    return 0;
}

void dosyadanOku(Kitap kitaplar[], Uye uyeler[], Odunc oduncVerilen[], KitapRafi raflar[], int* kitapSayisi, int* uyeSayisi, int* oduncSayisi, int* rafSayisi) {
    FILE* dosya = fopen("kutuphane.txt", "r");

    if (dosya == NULL) {
        printf("Dosya acilamadi veya bulunamadi.\n");
        return;
    }

    fscanf(dosya, "%d", kitapSayisi);
    for (int i = 0; i < *kitapSayisi; i++) {
        fscanf(dosya, "%d %s %s", &kitaplar[i].id, kitaplar[i].ad, kitaplar[i].yazar);
    }

    fscanf(dosya, "%d", uyeSayisi);
    for (int i = 0; i < *uyeSayisi; i++) {
        fscanf(dosya, "%d %s", &uyeler[i].uye_id, uyeler[i].ad);
    }

    fscanf(dosya, "%d", oduncSayisi);
    for (int i = 0; i < *oduncSayisi; i++) {
        fscanf(dosya, "%d %d", &oduncVerilen[i].kitap_id, &oduncVerilen[i].uye_id);
    }

    fscanf(dosya, "%d", rafSayisi);
    for (int i = 0; i < *rafSayisi; i++) {
        fscanf(dosya, "%d", &raflar[i].raf_id);
        fscanf(dosya, "%d", &raflar[i].kitapSayisi);
        for (int j = 0; j < raflar[i].kitapSayisi; j++) {
            fscanf(dosya, "%d %s %s", &raflar[i].kitaplar[j].id, raflar[i].kitaplar[j].ad, raflar[i].kitaplar[j].yazar);
        }
    }

    fclose(dosya);
}

void dosyayaYaz(Kitap kitaplar[], Uye uyeler[], Odunc oduncVerilen[], KitapRafi raflar[], int kitapSayisi, int uyeSayisi, int oduncSayisi, int rafSayisi) {
    FILE* dosya = fopen("kutuphane.txt", "w");

    if (dosya == NULL) {
        printf("Dosya acilamadi veya bulunamadi.\n");
        return;
    }

    fprintf(dosya, "%d\n", kitapSayisi);
    for (int i = 0; i < kitapSayisi; i++) {
        fprintf(dosya, "%d %s %s\n", kitaplar[i].id, kitaplar[i].ad, kitaplar[i].yazar);
    }

    fprintf(dosya, "%d\n", uyeSayisi);
    for (int i = 0; i < uyeSayisi; i++) {
        fprintf(dosya, "%d %s\n", uyeler[i].uye_id, uyeler[i].ad);
    }

    fprintf(dosya, "%d\n", oduncSayisi);
    for (int i = 0; i < oduncSayisi; i++) {
        fprintf(dosya, "%d %d\n", oduncVerilen[i].kitap_id, oduncVerilen[i].uye_id);
    }

    fprintf(dosya, "%d\n", rafSayisi);
    for (int i = 0; i < rafSayisi; i++) {
        fprintf(dosya, "%d\n", raflar[i].raf_id);
        fprintf(dosya, "%d\n", raflar[i].kitapSayisi);
        for (int j = 0; j < raflar[i].kitapSayisi; j++) {
            fprintf(dosya, "%d %s %s\n", raflar[i].kitaplar[j].id, raflar[i].kitaplar[j].ad, raflar[i].kitaplar[j].yazar);
        }
    }

    fclose(dosya);
}

void menuGoster() {
    printf("\n--- KUTUPHANE OTOMASYONU ---\n");
    printf("1. Kitap Ekle\n");
    printf("2. Uye Ekle\n");
    printf("3. Odunc Ver\n");
    printf("4. Kitap Listele\n");
    printf("5. Uye Listele\n");
    printf("6. Odunc Listele\n");
    printf("7. Kitap �ade\n");
    printf("8. Raf Ekle\n");
    printf("9. Kitabi Rafa Ekle\n");
    printf("10. Raf Listele\n");
    printf("0. Cikis\n");
}

void kitapEkle(Kitap kitaplar[], int* kitapSayisi) {
    // Kitap ekleme islemleri
    if (*kitapSayisi < MAX_KITAP_SAYISI) {
        printf("Kitap Adi: ");
        scanf("%s", kitaplar[*kitapSayisi].ad);
        printf("Yazar: ");
        scanf("%s", kitaplar[*kitapSayisi].yazar);
        kitaplar[*kitapSayisi].id = *kitapSayisi + 1;
        (*kitapSayisi)++;
        printf("Kitap basariyla eklendi.\n");
    }
    else {
        printf("Kutuphane maksimum kapasiteye ulasti. Yeni kitap eklenemez.\n");
    }
}

void uyeEkle(Uye uyeler[], int* uyeSayisi) {
    // uye ekleme islemleri
    if (*uyeSayisi < MAX_UYE_SAYISI) {
        printf("Uye Adi: ");
        scanf("%s", uyeler[*uyeSayisi].ad);
        uyeler[*uyeSayisi].uye_id = *uyeSayisi + 1;
        (*uyeSayisi)++;
        printf("Uye basariyla eklendi.\n");
    }
    else {
        printf("Uye sayisi maksimum kapasiteye ulasti. Yeni uye eklenemez.\n");
    }
}

void oduncVer(Odunc oduncVerilen[], int* oduncSayisi, Kitap kitaplar[], Uye uyeler[], int kitapSayisi, int uyeSayisi) {
    // odunc verme islemleri
    if (*oduncSayisi < MAX_ODUNC_VERILEN_SAYISI) {
        int kitapID, uyeID;
        printf("Kitap ID: ");
        scanf("%d", &kitapID);

        // Kitap ID kontrol
        if (kitapID <= 0 || kitapID > kitapSayisi) {
            printf("Gecersiz kitap ID'si. Lutfen tekrar deneyin.\n");
            return;
        }
        uyeListele(uyeler,uyeSayisi);
        printf("Uye ID: ");
        scanf("%d", &uyeID);

        // Uye ID kontrol
        if (uyeID <= 0 || uyeID > uyeSayisi) {
            printf("Gecersiz uye ID'si. Lutfen tekrar deneyin.\n");
            return;
        }

        // Odunc verilen kitap kontrol
        for (int i = 0; i < *oduncSayisi; i++) {
            if (oduncVerilen[i].kitap_id == kitapID) {
                printf("Bu kitap zaten odunc verilmis. Lutfen baska bir kitap secin.\n");
                kitapListele(kitaplar, kitapSayisi);
                printf("Kitap ID: ");
                scanf("%d", &kitapID);
                //return;
            }
        }

        // Odunc verilen kitap ve uye bilgilerini kaydet
        oduncVerilen[*oduncSayisi].kitap_id = kitapID;
        oduncVerilen[*oduncSayisi].uye_id = uyeID;
        (*oduncSayisi)++;

        printf("Odunc verme islemi basariyla gerceklesti.\n");
    }
    else {
        printf("Odunc verme limitine ulasildi. Daha fazla odunc verilemez.\n");
    }
}
void kitapListele(Kitap kitaplar[], int kitapSayisi) {
    printf("\n--- KITAP LISTESI ---\n");
    for (int i = 0; i < kitapSayisi; i++) {
        printf("ID: %d, Ad: %s, Yazar: %s\n", kitaplar[i].id, kitaplar[i].ad, kitaplar[i].yazar);
    }
}

void uyeListele(Uye uyeler[], int uyeSayisi) {
    printf("\n--- UYE LISTESI ---\n");
    for (int i = 0; i < uyeSayisi; i++) {
        printf("ID: %d, Ad: %s\n", uyeler[i].uye_id, uyeler[i].ad);
    }
}

void oduncListele(Odunc oduncVerilen[], int oduncSayisi, Kitap kitaplar[], Uye uyeler[]) {
    printf("\n--- ODUNC KITAP LISTESI ---\n");
    for (int i = 0; i < oduncSayisi; i++) {
        int kitapID = oduncVerilen[i].kitap_id;
        int uyeID = oduncVerilen[i].uye_id;

        printf("Kitap ID: %d, Ad: %s, Yazar: %s, Uye ID: %d, Uye Ad: %s\n",
            kitapID, kitaplar[kitapID - 1].ad, kitaplar[kitapID - 1].yazar,
            uyeID, uyeler[uyeID - 1].ad);
    }
}

void kitapIade(Odunc oduncVerilen[], int* oduncSayisi, Kitap kitaplar[], Uye uyeler[], int kitapSayisi, int uyeSayisi) {
    int kitapID, uyeID;

    printf("Kitap ID: ");
    scanf("%d", &kitapID);

    // Kitap ID kontrol
    if (kitapID <= 0 || kitapID > kitapSayisi) {
        printf("Gecersiz kitap ID'si. Lutfen tekrar deneyin.\n");
        return;
    }

    printf("Uye ID: ");
    scanf("%d", &uyeID);

    // Uye ID kontrol
    if (uyeID <= 0 || uyeID > uyeSayisi) {
        printf("Gecersiz uye ID'si. Lutfen tekrar deneyin.\n");
        return;
    }

    // Kitap iade kontrol
    int i;
    for (i = 0; i < *oduncSayisi; i++) {
        if (oduncVerilen[i].kitap_id == kitapID && oduncVerilen[i].uye_id == uyeID) {
            printf("Kitap iade edildi.\n");
            break;
        }
    }

    if (i == *oduncSayisi) {
        printf("Bu kitap uye tarafindan odunc alinmamis veya uygun uye bulunamadi.\n");
    }
    else {
        // Kitap iade edildilinde, listeden cıkkar
        for (int j = i; j < *oduncSayisi - 1; j++) {
            oduncVerilen[j] = oduncVerilen[j + 1];
        }
        (*oduncSayisi)--;
    }
}

void rafEkle(KitapRafi raflar[], int* rafSayisi) {
    if (*rafSayisi < MAX_RAFLAR) {
        raflar[*rafSayisi].raf_id = *rafSayisi + 1;
        raflar[*rafSayisi].kitapSayisi = 0;
        (*rafSayisi)++;
        printf("Raf basariyla eklendi.\n");
    }
    else {
        printf("Raf sayisi maksimum kapasiteye ulasti. Yeni raf eklenemez.\n");
    }
}

void kitabiRafaEkle(KitapRafi raflar[], int rafSayisi, Kitap kitaplar[], int kitapSayisi) {
    int rafID, kitapID;
    printf("Raf ID: ");
    scanf("%d", &rafID);

    // Raf ID kontrol
    if (rafID <= 0 || rafID > rafSayisi) {
        printf("Gecersiz raf ID'si. Lutfen tekrar deneyin.\n");
        return;
    }

    printf("Kitap ID: ");
    scanf("%d", &kitapID);

    // Kitap ID kontrol
    if (kitapID <= 0 || kitapID > kitapSayisi) {
        printf("Gecersiz kitap ID'si. Lutfen tekrar deneyin.\n");
        return;
    }

    KitapRafi* raf = &raflar[rafID - 1];
    if (raf->kitapSayisi < MAX_KITAP_RAFA) {
        raf->kitaplar[raf->kitapSayisi] = kitaplar[kitapID - 1];
        (raf->kitapSayisi)++;
        printf("Kitap rafa basariyla eklendi.\n");
    }
    else {
        printf("Raf maksimum kapasiteye ulasti. Yeni kitap eklenemez.\n");
    }
}

void rafListele(KitapRafi raflar[], int rafSayisi, Kitap kitaplar[], int kitapSayisi) {
    printf("\n--- RAF LISTESI ---\n");
    for (int i = 0; i < rafSayisi; i++) {
        printf("Raf ID: %d\n", raflar[i].raf_id);
        printf("Kitaplar:\n");
        for (int j = 0; j < raflar[i].kitapSayisi; j++) {
            printf("  - ID: %d, Ad: %s, Yazar: %s\n",
                raflar[i].kitaplar[j].id, raflar[i].kitaplar[j].ad, raflar[i].kitaplar[j].yazar);
        }
        printf("\n");
    }
}
