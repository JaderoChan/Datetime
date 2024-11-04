import re

def literals_to_utf8(s : str, prefix : str = '\\x', isUpper : bool = True) -> str:
    bytes = s.encode('utf-8')
    rslt = ''
    for i in bytes:
        rslt += prefix + hex(i)[2:].upper() if isUpper else hex(i)[2:]
    return rslt

def replace_literal_to_utf8(match) -> str:
    return 'u8"' + literals_to_utf8(match.group(1)) + '"'

def quotes_literal_to_utf8(s : str) -> str:
    return re.sub('(?:u8")(.*)(?:")', replace_literal_to_utf8, s)

path = input("Enter the path of the file: ")
file = open(path, 'r', encoding='utf-8')
s = quotes_literal_to_utf8(file.read())
file.close()
file = open(path, 'w')
file.write(s)
file.close()
