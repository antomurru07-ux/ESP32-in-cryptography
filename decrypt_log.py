
import sys
from Crypto.Cipher import AES

#  Same key as the firmware
AES_KEY = bytes([
    0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
    0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C
])


def remove_pkcs7(data: bytes) -> bytes:
    pad_len = data[-1]
    if pad_len == 0 or pad_len > 16:
        raise ValueError(f"Padding not valid: {pad_len}")
    return data[:-pad_len]


def decrypt_line(hex_line: str) -> str:
    raw = bytes.fromhex(hex_line.strip())
    if len(raw) < 32:
        raise ValueError("Row too short")

    iv         = raw[:16]   # first 16 byte = IV
    ciphertext = raw[16:]   # rest = enrypted data

    cipher    = AES.new(AES_KEY, AES.MODE_CBC, iv)
    plaintext = remove_pkcs7(cipher.decrypt(ciphertext))
    return plaintext.decode("utf-8")


def decrypt_file(path: str):
    print(f"File: {path}\n")
    print(f"{'#':>4}  {'Result'}")
    print("-" * 50)

    with open(path, "r") as f:
        for i, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue
            try:
                result = decrypt_line(line)
                print(f"{i:>4}  {result}")
            except Exception as e:
                print(f"{i:>4}  [ERROR: {e}]")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Use: python decrypt_log.py <file.txt>")
        sys.exit(1)

    decrypt_file("datiCriptati.txt")