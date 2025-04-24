import re

with open("pid.708.dmp", "rb") as f:
    data = f.read()

pattern = re.compile(b'\x64.{6,8}\x40\x06.{18}\x5a\x0c\x00\x00')
matches = pattern.finditer(data)

for match in matches:
    offset = match.start()
    after = data[match.end() : match.end() + 64]
    matched = match.group()

    total_bytes = matched + after

    decoded_text = ''.join(
        chr(b) if 0x20 <= b <= 0x7E else '.' for b in total_bytes
    )


    hex_pairs = [total_bytes[j:j+2].hex() for j in range(0, len(total_bytes), 2)]
    

    spaced_output = ' '.join(hex_pairs)


    print(f"[+] Offset: {match.start():#x}")
    print(spaced_output)
    print(f"\n{decoded_text}")

