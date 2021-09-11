from os import close
import runit

sloutdata = open("sloutdata.txt", 'w')
while True:
    file = input('File Path > ')
    text = open(file, 'r')
    result, error = runit.run(text.name, text.read())
    
    text.close()

    if error: print(error.as_string())
    else: print(result)
    sloutdata.write(f'{result}')
    sloutdata.close()