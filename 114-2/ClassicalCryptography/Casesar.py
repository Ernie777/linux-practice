def caesar_encrypt(p: str, k: int) -> str:
    result = []
    for char in p:
        if char.isalpha():
            start = ord('A') if char.isupper() else ord('a')
            shifted_char = chr((ord(char) - start + k) % 26 + start)
            result.append(shifted_char)
        else:
            result.append(char)
    return "".join(result)

plaintext = input()

for k in range(1,27):
    shift_letter = chr(ord('a') + k - 1)
    ciphertext = caesar_encrypt(plaintext, k)
    print(f"{shift_letter}: {ciphertext}")


