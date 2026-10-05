#include <stdio.h>

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;
    float ratedPowerKW;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main() {
    struct SmartDevice device;
    struct EnergySensor sensor;
    float operatingHours;

    printf("=== NHAP THONG TIN THIET BI ===\n");
    printf("Nhap ma thiet bi: ");
    scanf("%d", &device.deviceID);
    printf("Nhap ten thiet bi: ");
    scanf(" %[^\n]", device.deviceName);
    printf("Nhap trang thai (1-Bat, 0-Tat): ");
    scanf("%d", &device.status);
    printf("Nhap cong suat dinh muc (kW): ");
    scanf("%f", &device.ratedPowerKW);

    printf("\n=== NHAP THONG TIN CAM BIEN ===\n");
    printf("Nhap dien ap (V): ");
    scanf("%f", &sensor.voltageVolts);
    printf("Nhap dong dien (A): ");
    scanf("%f", &sensor.currentAmperes);
    printf("Nhap thoi gian vang nguoi (phut): ");
    scanf("%d", &sensor.unoccupancyMinutes);

    printf("\n=== NHAP THOI GIAN VAN HANH ===\n");
    printf("Nhap so gio hoat dong trong thang: ");
    scanf("%f", &operatingHours);

    if (sensor.voltageVolts < 0 || sensor.currentAmperes < 0 || sensor.unoccupancyMinutes < 0) {
        printf("\nLOI: Thong so cam bien khong hop le (bi am). Huy thao tac!\n");
        return 1;
    }

    if (operatingHours <= 0 || operatingHours > 744) {
        printf("\nLOI: So gio van hanh khong hop le (phai trong khoang 1 - 744 gio). Huy thao tac!\n");
        return 1;
    }

    int is_overloaded = 0;
    int is_auto_off = 0;

    if (sensor.currentAmperes > 30.0f) {
        device.status = 0;
        is_overloaded = 1;
    }

    if (device.status == 1 && sensor.unoccupancyMinutes >= 15) {
        device.status = 0;
        is_auto_off = 1;
    }

    float total_kwh = device.ratedPowerKW * operatingHours;
    double total_cost = 0.0;
    float kwh_rem = total_kwh;

    if (kwh_rem > 0) {
        float b1 = (kwh_rem > 50) ? 50 : kwh_rem;
        total_cost += b1 * 1806;
        kwh_rem -= b1;
    }
    if (kwh_rem > 0) {
        float b2 = (kwh_rem > 50) ? 50 : kwh_rem;
        total_cost += b2 * 1866;
        kwh_rem -= b2;
    }
    if (kwh_rem > 0) {
        float b3 = (kwh_rem > 100) ? 100 : kwh_rem;
        total_cost += b3 * 2167;
        kwh_rem -= b3;
    }
    if (kwh_rem > 0) {
        total_cost += kwh_rem * 2729;
    }

    printf("\n================ BCTK SMART HOME GATEWAY ================\n");
    printf("Thiet bi: %s (ID: %d)\n", device.deviceName, device.deviceID);
    printf("Trang thai hien tai: %s\n", device.status ? "BAT" : "TAT");
    
    if (is_overloaded) {
        printf("CANH BAO: DONG DIEN VUOT NGUNG (>30A) - DA NGAT KHAN CAP PHONG CHAY NO!\n");
    } else if (is_auto_off) {
        printf("THONG BAO: KHONG CO NGUOI TRONG 15 PHUT - DA TU DONG TAT THIET BI TIET KIEM DIEN!\n");
    }

    printf("Tong dien nang tieu thu trong thang: %.2f kWh\n", total_kwh);
    printf("Tong tien dien du kien (chua VAT): %.0f VNĐ\n", total_cost);
    printf("==========================================================\n");

    return 0;
}