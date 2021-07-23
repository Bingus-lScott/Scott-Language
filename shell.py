import basic

while True:
    text = input('N/A > ')
    result, error = basic.run('(File Name Not Found)', text)

    if error: print(error.as_string())
    else: print(result)