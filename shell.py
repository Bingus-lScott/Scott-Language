import basic

while True:
    text = input('N/A > ')
    result, error = basic.run('No file currently', text)

    if error: print(error.as_string())
    else: print(result)