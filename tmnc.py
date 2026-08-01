import random
numeros = list(range(1, 20001))
random.shuffle(numeros)
with open('numeros.txt', 'w') as f:
    f.write('\n'.join(map(str, numeros)))
