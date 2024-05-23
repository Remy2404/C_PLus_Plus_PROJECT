#ifndef QRCODEGEN_HPP
#define QRCODEGEN_HPP

#include "qrcodegen.hpp"

class QRCodeGen {
public:
    static void generateQRCode(const char* data, const char* filename, int border = 4) {
        const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(data, qrcodegen::QrCode::Ecc::LOW);
        printQRCode(qr, border);
        saveQRCodeToFile(qr, filename, border);
    }

private:
    static void printQRCode(const qrcodegen::QrCode& qr, int border) {
        for (int y = -border; y < qr.getSize() + border; y++) {
            for (int x = -border; x < qr.getSize() + border; x++) {
                cout << (qr.getModule(x, y) ? "\033[40m  \033[0m" : "\033[47m  \033[0m");
            }
            cout << endl;
        }
    }

    static void saveQRCodeToFile(const qrcodegen::QrCode& qr, const char* filename, int border) {
        ofstream outputFile(filename);
        for (int y = -border; y < qr.getSize() + border; y++) {
            for (int x = -border; x < qr.getSize() + border; x++) {
                outputFile << (qr.getModule(x, y) ? "1" : "0");
            }
            outputFile << endl;
        }
        outputFile.close();
    }
};

#endif // QRCODEGEN_HPP
